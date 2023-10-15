/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Inventory
*/

#include "Client.hpp"

void Client::setInventory(std::string buffer)
{
    std::sscanf(buffer.c_str(), "[ food %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d ]\n",
        &_inventory.food, &_inventory.linemate, &_inventory.deraumere,
        &_inventory.sibur, &_inventory.mendiane, &_inventory.phiras,
        &_inventory.thystame);
}

// Cette fonction envoie au serveur la commande "Inventory" et stock la reponse
// dans la classe Client.
void Client::askInventory(void)
{
    std::string sendStr = "Inventory\n";
    std::string rcv;

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Inventory"));
    setInventory(wait_recv("[ "));
}
