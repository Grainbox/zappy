/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Eject
*/

#include "Client.hpp"

void Client::eject(void)
{
    std::string sendStr = "Eject\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Eject"));
    wait_recv("ok", "ko");
}
