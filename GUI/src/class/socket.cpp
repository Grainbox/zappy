/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** socket
*/

#include "../../includes/class/socket.hpp"
#include <cstring>

Socket::Socket (std::string serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort)
{
    this->socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketId == -1)
        exit(84);
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_port = htons(this->serverPort);
    this->serverAddress.sin_addr.s_addr = inet_addr(this->serverIP.c_str());

    if (connect(this->socketId, (struct sockaddr*)&this->serverAddress, sizeof(this->serverAddress)) == -1) {
        close(this->socketId);
        throw ConnectError(strerror(errno));
    }
    send_socket("GRAPHIC\n");
}

Socket::~Socket ()
{
    close(this->socketId);
}

int Socket::send_socket (std::string str)
{
    int bytesSent = send(this->socketId, str.c_str(), str.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Erreur lors de l'envoi des données." << std::endl;
        close(socketId);
        return 0;
    }
    return 1;
}

bool Socket::selectSocket()
{
    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = 1;

    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(socketId, &readFds);

    int selectResult = select(socketId + 1, &readFds, nullptr, nullptr, &timeout);
    if (selectResult == -1) {
        close(socketId);
        throw SelectError("Erreur lors de l'appel à select.");
    }
    if (FD_ISSET(socketId, &readFds) && selectResult != 0) {
        return true;
    }
    return false;
}

std::string Socket::listen_socket ()
{
    char buffer[32000];

    int bytesRead = recv(socketId, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Erreur lors de la réception des données." << std::endl;
        close(socketId);
    }
    buffer[bytesRead] = '\0';
    return (std::string) buffer;
}
