/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Take & Set
*/

#include "Client.hpp"

void Client::take(std::string object)
{
    std::string sendStr = "Take " + object + "\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Take"));
    wait_recv("ok", "ko");
}

void Client::set(std::string object)
{
    std::string sendStr = "Set " + object + "\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Set"));
    if (wait_recv("ok", "ko") == "ok")
        printf("set object OK\n");
    else
        printf("set object fail\n");
}
