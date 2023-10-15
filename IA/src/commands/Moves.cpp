/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Moves
*/

#include "Client.hpp"

// envoie de la commande 'Forward' pour faire avancer l'IA d'une case dans
// la direction qu'elle regarde.
void Client::goForward(void)
{
    std::string sendStr = "Forward\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Forward"));
    wait_recv("ok");
    // printf("go forward\n");
}

// envoie de la commande 'Right' pour tourner l'IA de 90° vers la droite
void Client::turnRight(void)
{
    std::string sendStr = "Right\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Right"));
    wait_recv("ok");
    // printf("turn right\n");
}

// envoie de la commande 'Left' pour tourner l'IA de 90° vers la gauche
void Client::turnLeft(void)
{
    std::string sendStr = "Left\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Left"));
    wait_recv("ok");
    // printf("turn left\n");
}

void Client::goTile(int tile)
{
    if (tile == 0)
        return;
    int forwards1 = (int) sqrt(tile);
    int forwards2 = 0;
    float fract = tile / forwards1;

    for (int i = 0; i != forwards1; i++)
        goForward();
    if (fract < forwards1 + 1) {
        turnLeft();
        forwards2 = forwards1 * (forwards1 + 1) - tile;
        for (int i = 0; i != forwards2; i++)
            goForward();
    } else if (fract > forwards1 + 1) {
        turnRight();
        forwards2 = tile - forwards1 * (forwards1 + 1);
        for (int i = 0; i != forwards2; i++)
            goForward();
    } else
        return;
}

void Client::goDirection(int direction)
{
    printf("going direction: %d\n", direction);
    if (direction == 1 || direction == 2 || direction == 8)
        goForward();
    if (direction == 2 || direction == 3) {
        turnLeft();
        goForward();
    }
    if (direction == 7 || direction == 8) {
        turnRight();
        goForward();   
    }
    if (direction == 4 || direction == 5 || direction == 6) {
        turnRight();
        turnRight();
        goForward();
    }
    if (direction == 4) {
        turnRight();
        goForward();
    }
    if (direction == 6) {
        turnLeft();
        goForward();
    }
}

void Client::assembleOrient(void)
{
    if (_assembleDirection == 2 || _assembleDirection == 3 ||
        _assembleDirection == 4)
        turnLeft();
    if (_assembleDirection == 5) {
        turnLeft();
        turnLeft();
    }
    if (_assembleDirection == 6 || _assembleDirection == 7 ||
        _assembleDirection == 8)
        turnRight();
}
