/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <iostream>
    #include <unistd.h>
    #include <sys/types.h>

    class SelectError : public std::exception {
        private:
            std::string message_;

        public:
            SelectError(const std::string& message) : message_(message) {}

            const char* what() const noexcept override {
                return message_.c_str();
            }
    };

    class ConnectError : public std::exception {
        private:
            std::string message_;

        public:
            ConnectError(const std::string& message) : message_(message) {}

            const char* what() const noexcept override {
                return message_.c_str();
            }
    };

    class Socket {
        public:
            Socket (std::string serverIP = "127.0.0.1", int serverPort = 4242);
            ~Socket ();
            bool selectSocket();
            int send_socket (std::string str);
            std::string listen_socket ();
        private:
            int socketId = 0;
            std::string serverIP;
            int serverPort;
            sockaddr_in serverAddress {};
    };


#endif /* !SOCKET_HPP_ */
