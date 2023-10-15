import os
import glob
import subprocess
import argparse
from typing import List

def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Run tests with Docker.')
    parser.add_argument('--json_path', default=None, help='Optional .json file path for the tests.')
    parser.add_argument('--logs', action='store_true', help='For display additional logs.')
    return parser.parse_args()

def get_json_files(json_path: str = None) -> List[str]:
    return [json_path] if json_path else glob.glob('tests/*.json')

def build_docker_image(dockerfile_path: str, image_name: str):
    subprocess.check_output(["docker", "build", "-t", image_name, "-f", dockerfile_path, "."])

def is_docker_container_running(container_name: str) -> bool:
    output = subprocess.check_output(["docker", "ps", "-a", "--filter", f"name={container_name}", "--format", "{{.Names}}"]).decode().strip()
    return output == container_name

def stop_docker_container(container_name: str):
    subprocess.run(["docker", "kill", container_name])

def run_docker_container(json_files: List[str], image_name: str, log_flag: bool):
    container_name = "ctn-zappy_tests"
    if is_docker_container_running(container_name):
        print(f"Stopping running container {container_name}")
        stop_docker_container(container_name)
    error = 0
    for json_file in json_files:
        try:
            docker_command = ["docker", "run", "-t", "--rm", "--name", container_name, "-v", f"{os.getcwd()}:/host", image_name, "python3", "/app/tests/tester.py", "./zappy_server", json_file]
            if log_flag:
                docker_command.append('-l')
            p = subprocess.Popen(docker_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            for line in p.stdout:
                print(line.decode(), end='')
            p.stdout.close()
            p.wait()
            if p.returncode != 0:
                error += p.returncode
        except subprocess.CalledProcessError as e:
            print(f"Error running Docker container for test file '{json_file}':\n{e.output.decode()}")
            exit(1 if error == 0 else error)
    exit(error)
def main():
    args = parse_arguments()
    json_files = get_json_files(args.json_path)
    dockerfile_path = "tests/Dockerfile"
    image_name = "img-zappy_tests"
    subprocess.check_output(["cp", "../tests/zappy_server", "./tests/"])
    build_docker_image(dockerfile_path, image_name)

    try:
        run_docker_container(json_files, image_name, args.logs)
    except KeyboardInterrupt:
        print("\nInterrupted. Killing container...")
        stop_docker_container("ctn-zappy_tests")
    subprocess.check_output(["rm", "./tests/zappy_server"])
if __name__ == '__main__':
    main()
