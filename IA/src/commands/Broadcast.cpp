/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Broadcast
*/

#include "Client.hpp"

void Client::broadcast(std::string text)
{
    std::string sendStr = "Broadcast " + text + "\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Broadcast"));
    wait_recv("ok");
}
