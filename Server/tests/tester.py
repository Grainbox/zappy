import json
import subprocess
import sys
import time
import socket
import select
from difflib import ndiff, unified_diff
from termcolor import colored
from typing import Dict, List, Tuple, Optional, Union
from threading import Thread, Lock
from termcolor import colored

lock = Lock()

def fd_has_data(client: socket.socket, timeout: Union[float, int] = 1.0) -> List[socket.socket]:
    ready = select.select([client], [], [], timeout)
    return ready[0]

def socket_ready_to_send(client: socket.socket, timeout: Union[float, int] = 1.0) -> List[socket.socket]:
    ready = select.select([], [client], [], timeout)
    return ready[1]

def wait_for_server(port: int, max_tries: int = 10):
    for i in range(max_tries):
        try:
            with socket.create_connection(('localhost', port)):
                return
        except (socket.error, ConnectionRefusedError):
            time.sleep(0.5)
    raise Exception(f"Server did not start (timeout after {max_tries} tries)")

def check_results(ref_output: List[List[str]], test_output: List[List[str]]) -> List[List[str]]:
    all_differences = []
    for ref, test in zip(ref_output, test_output):
        differences = []
        diff = ndiff(ref, test)
        changes = [l for l in diff if l.startswith("- ") or l.startswith("+ ")]
        if changes:
            differences.extend(changes)
        all_differences.append(differences)
    return all_differences

def client_run(client_test: Dict[str, Union[str, List[str]]], ref_port: int, test_port: int, results: List[Tuple[List[str], List[str], List[str]]]) -> None:
    with socket.create_connection(('localhost', ref_port)) as ref_client, \
         socket.create_connection(('localhost', test_port)) as test_client:
        sended_client = ['__CLIENT_CONNECTION__']
        ref_client_recv: List[str] = []
        test_client_recv: List[str] = []
        if client_test.get('team'):
            sended_client.append(client_test.get('team'))
            ref_client.sendall(client_test.get('team').encode() + b'\n')
            test_client.sendall(client_test.get('team').encode() + b'\n')
        else:
            raise ValueError('You must specify a team name for the test.')
        while len(ref_client_recv) == 0 or fd_has_data(ref_client):
            time.sleep(0.1)
            ref_client_recv += ref_client.recv(1024).decode('utf-8').splitlines()
        while len(test_client_recv) == 0 or fd_has_data(test_client):
            time.sleep(0.1)
            test_client_recv += test_client.recv(1024).decode('utf-8').splitlines()
        for input_str in client_test.get('inputs', []):
            sended_client.append(input_str)
            ref_client.sendall(input_str.encode() + b'\n')
            test_client.sendall(input_str.encode() + b'\n')
        while fd_has_data(ref_client):
            ref_client_recv += ref_client.recv(1024).decode('utf-8').splitlines()
        while fd_has_data(test_client):
            test_client_recv += test_client.recv(1024).decode('utf-8').splitlines()

    with lock:
        results.append((sended_client, ref_client_recv, test_client_recv))

def run_test(test: Dict[str, Union[str, List[str]]], test_binary: str, reference_binary: str, server_args: str) -> Tuple[List[str], Optional[bool], List[str], List[str]]:
    test_port : int = 4243
    ref_port : int = 4242
    with subprocess.Popen([reference_binary] + server_args.join(f' -p {ref_port}').split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE) as ref_server:
        with subprocess.Popen([test_binary] + server_args.join(f' -p {test_port}').split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE) as test_server:
            try:
                wait_for_server(ref_port)
                wait_for_server(test_port)
            except Exception as e:
                print(f"Error: {e}")
                if ref_server.poll() is None:
                    ref_server.terminate()
                if test_server.poll() is None:
                    test_server.terminate()
                ref_server.wait()
                test_server.wait()
                raise e

            if "client" in test:
                client_tests = test["client"]
            else:
                client_tests = [test]

            threads = []
            results = []

            for client_test in client_tests:
                thread = Thread(target=client_run, args=(client_test, ref_port, test_port, results))
                threads.append(thread)
                thread.start()

            for thread in threads:
                thread.join()

            sended = []
            ref_client_recvs = []
            test_client_recvs = []

            for result in results:
                sended.append(result[0])
                ref_client_recvs.append(result[1])
                test_client_recvs.append(result[2])
            if ref_server.poll() is None:
                ref_server.terminate()
            if test_server.poll() is None:
                test_server.terminate()
            ref_server.wait()
            test_server.wait()
    return sended, check_results(ref_client_recvs, test_client_recvs), ref_client_recvs, test_client_recvs

def display_diff(diff: Union[bool, List[List[str]]], colored_output: bool = True):
    for client_idx, client_diff in enumerate(diff):
        print(f'   ---client {client_idx} diff---')
        for i, s in enumerate(client_diff):
            print('   ', end='')
            if s[0] == ' ':
                print(colored(s, "light_grey") + " (ok)")
            elif s[0] == '-':
                print(colored(s, "red") + ' (your server have missing line)')
            elif s[0] == '+':
                print(colored(s, "light_red") + ' (your server have unexpected line)')
        print(f'   ---end client {client_idx} diff---\n')

def display_test_logs(test: Dict[str, Union[str, List[str]]], sended: List[List[str]], ref_output: List[List[str]], test_output: List[List[str]]):
    print('   ---test logs---')
    print('   Test name:', test['name'])
    print('   Test description:', test.get('description', 'No description for this test.'))
    print('   Test timeout: ', test.get('timeout', 'No timeout for this test, use default timeout'))
    print('   Test team:', test.get('team', 'No team specified for this test.'))
    print('   Test inputs:', test.get('inputs', ['No input specified for this test.']))

    for idx, (sended_client, ref_output_client, test_output_client) in enumerate(zip(sended, ref_output, test_output)):
        print(f'\n   ---client {idx} logs---')
        print('   Sended:\t', sended_client)
        print('   Ref replys:\t', ref_output_client)
        print('   Your replys:\t', test_output_client)
        print(f'   ---end client {idx} logs---\n')

    print('   ---end test logs---\n')

def main():
    passed = 0
    failed = 0
    ignored = 0
    if len(sys.argv) < 3:
        raise ValueError('You must provide the server to test path and test file path as arguments.')

    test_binary: str = sys.argv[1]
    test_file_path: str = sys.argv[2]
    verbose_log: bool = False
    if len(sys.argv) == 4 and sys.argv[3] == '-l':
        verbose_log = True

    with open(test_file_path, 'r') as f:
        tests = json.load(f)

    reference_binary = tests['reference_binary']
    server_args = tests.get('server_args', '')

    print(colored(f'Start tests \'{tests["name"] if "name" in tests else "No name specified for this tests."}\'', 'cyan'))

    for test in tests['tests']:
        if 'ignore' in test and test['ignore'] == True:
            print(colored('Test '+ test['name'] + ' is ignored\n', 'yellow'))
            ignored += 1
            continue
        print(colored('Running test ' + test['name'] + '...', 'cyan'))
        try:
            sended, diff, ref_output, test_output = run_test(test, test_binary, reference_binary, server_args)
            for i in range(len(diff)):
                if len(diff[i]) != 0:
                    display_diff(diff)
                    if verbose_log:
                        display_test_logs(test, sended, ref_output, test_output)
                    if test.get('ignore_failure', False):
                        print(colored('Test ' + test['name'] + ' failed. (ignored)\n', 'yellow'))
                        ignored += 1
                    else:
                        print(colored('Test ' + test['name'] + ' failed.\n', 'red'))
                        failed += 1
                    break
            else:
                if verbose_log:
                    display_test_logs(test, sended, ref_output, test_output)
                print(colored('Test ' + test['name'] + ' passed\n', 'green'))
                passed += 1
        except Exception as e:
            print(colored('Test ' + test['name'] + ' failed with error: ' + str(e), 'red'))
            failed += 1
            if verbose_log:
                display_test_logs(test, sended, ref_output, test_output)

    print('------\n')
    print('Result:', colored(str(passed), "green"), 'passed,', colored(str(failed), "red"), 'failed,', colored(str(ignored), "yellow"), 'ignored.')
    exit(failed)

if __name__ == '__main__':
    main()
