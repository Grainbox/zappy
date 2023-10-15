/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Look
*/

#include "Client.hpp"

// Command "Look", demandant au serveur ce que voit le client devant lui.
void Client::look(void)
{
    std::string sendStr = "Look\n";

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Look"));
    parseLook(wait_recv("[ "));

    // // debug
    // int count = 0;
    // for (auto it : _sight)  {
    //     printf("tile %d: ", count);
    //     for (auto it2 : it)
    //         printf("%s ", it2.c_str());
    //     printf("\n");
    //     count++;
    // }
    // //
}

// Parsing de la string envoyée par le serveur en réponse à la commande "Look"
// Les infos sont rangées dans un vecteur de vecteur de string "_sight".
void Client::parseLook(const std::string &input)
{
    std::string temp;
    std::vector<std::string> innerVector;
    int count = 0;

    _sight.clear();
    for (auto it : input) {
        if (count <= 1) {
            count++;
            continue;
        }
        if (it == ']') {
            if (innerVector.empty())
                temp = "nothing";
            innerVector.push_back(temp);
            temp.clear();
            _sight.push_back(innerVector);
            innerVector.clear();
            break;
        }
        if (it == ' ' && !temp.empty()) {
            innerVector.push_back(temp);
            temp.clear();
        } else if (it == ',') {
            if (temp.empty())
                temp = "nothing";
            innerVector.push_back(temp);
            temp.clear();
            _sight.push_back(innerVector);
            innerVector.clear();
        } else
            if (it != ' ')
                temp += it;
    }
}

// Analyse du vecteur _sight a la recherche de nourriture, stock la premiere
// case en contenant dans la variable 'closestFood'.
bool Client::isSeeingFood(void)
{
    int count = 0;

    for (auto it : _sight) {
        for (auto it2 : it)
            if (it2 == "food") {
                _closestFood = count;
                return true;
            }
        count++;
    }
    _closestFood = -1;
    return false;
}

// Analyse du vecteur _sight a la recherche des pierres requises pour la
// prochaine elevation (prends thystame dans tout les cas car tres rare).
bool Client::isSeeingStone(void)
{
    int count = 0;

    for (auto it : _sight) {
        for (auto it2 : it)
            if (isStoneNeeded(it2) || it2 == "thystame") {
                _closestStone = count;
                return true;
            }
        count++;
    }
    return false;
}

// Renvoie True si l'objet mis en argument est une pierre. False sinon.
bool Client::isAStone(std::string input) const
{
    if (input == "linemate" || input == "deraumere" || input == "sibur" ||
        input == "mendiane" || input == "phiras" || input == "thystame")
        return true;
    return false;
}

int Client::seePlayer(void)
{
    int tile = 0;

    look();
    for (auto it : _sight) {
        for (auto it2 : it) {
            if (it2 == "player") {
                printf("I SEE A PLAYER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                return tile;
            }
        }
        tile++;
    }
    return -1;
}
