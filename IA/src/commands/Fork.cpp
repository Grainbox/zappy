/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Fork
*/

#include "Client.hpp"

// Envoie la commande 'Fork' au serveur pour pondre un oeuf sur la case 0.
void Client::layEgg(void)
{
    std::string sendStr = "Fork\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Fork"));
    wait_recv("ok");
    printf("Lay egg\n");
    look();
    for (auto it : _sight[0])
        printf("%s, ", it.c_str());
    printf("\n");
}
