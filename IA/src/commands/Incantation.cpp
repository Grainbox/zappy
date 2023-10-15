/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Incantation
*/

#include "Client.hpp"

// Analyse du niveau et de l'inventaire du client pour determiner si oui ou non
// il peut s'elever au niveau supérieur.
bool Client::haveAllReqStones(void) const
{
    if (_level == 1 && _inventory.linemate >= 1)
        return true;
    if (_level == 2 && _inventory.linemate >= 1 && _inventory.deraumere >= 1 &&
        _inventory.sibur >= 1)
        return true;
    if (_level == 3 && _inventory.linemate >= 2 && _inventory.sibur >= 1 &&
        _inventory.phiras >= 2)
        return true;
    if (_level == 4 && _inventory.linemate >= 1 && _inventory.deraumere >= 1 &&
        _inventory.sibur >= 2 && _inventory.phiras >= 1)
        return true;
    if (_level == 5 && _inventory.linemate >= 1 && _inventory.deraumere >= 2 &&
        _inventory.sibur >= 1 && _inventory.mendiane >= 3)
        return true;
    if (_level == 6 && _inventory.linemate >= 1 && _inventory.deraumere >= 2 &&
        _inventory.sibur >= 3 && _inventory.phiras >= 1)
        return true;
    if (_level == 7 && _inventory.linemate >= 2 && _inventory.deraumere >= 2 &&
        _inventory.sibur >= 2 && _inventory.mendiane >= 2 &&
        _inventory.phiras >= 2 && _inventory.thystame >= 1)
        return true;
    return false;
}

bool Client::isStoneNeeded(std::string stone)
{
    if (_level == 1 && stone == "linemate")
        return true;
    if (_level == 2 && (stone == "linemate" || stone == "deraumere" || stone == "sibur"))
        return true;
    if (_level == 3 && (stone == "linemate" || stone == "sibur" || stone == "phiras"))
        return true;
    if (_level == 4 && (stone == "linemate" || stone == "deraumere" || stone == "sibur" || stone == "phiras" || stone == "thystame"))
        return true;
    if (_level == 5 && (stone == "linemate" || stone == "deraumere" || stone == "sibur" || stone == "mendiane"))
        return true;
    if (_level == 6 && (stone == "linemate" || stone == "deraumere" || stone == "sibur" || stone == "phiras"))
        return true;
    if (_level == 7)
        return true;
    return false;
}

bool Client::tileReady(void) const
{
    return false;
}

void Client::clearTile(void)
{
    if (_sight.at(0).size() == 1)
        return;
    for (auto it : _sight.at(0))
        if (it != "player" && it != "egg")
            take(it);
    if (_sight.at(0).size() != 1)
        eject();
}

void Client::arrangeTile(std::string stone, int nb)
{
    int occ = 0;

    for (auto it : _sight.at(0))
        if (it == stone)
            occ++;
    if (occ < nb)
        for (; occ < nb; occ++)
            set(stone);
    else if (occ > nb)
        for (; occ > nb; occ++)
            take(stone);
}

// L'incantation échoue si des pierres non requises sont presentes, cette
// fonction sert a ramasser ces pierres pour permettre l'incantation.
void Client::setupIncantation(void)
{
    for (auto it : _sight.at(0))
        if (!isStoneNeeded(it))
            take(it);

    if (_level == 2) {
        arrangeTile("linemate", 1);
        arrangeTile("deraumere", 1);
        arrangeTile("sibur", 1);
    }
    if (_level == 3) {
        arrangeTile("linemate", 2);
        arrangeTile("sibur", 1);
        arrangeTile("phiras", 2);
    }
    if (_level == 4) {
        arrangeTile("linemate", 1);
        arrangeTile("deraumere", 1);
        arrangeTile("sibur", 2);
        arrangeTile("phiras", 1);
    }
    if (_level == 5) {
        arrangeTile("linemate", 1);
        arrangeTile("deraumere", 2);
        arrangeTile("sibur", 1);
        arrangeTile("mendiane", 3);
    }
    if (_level == 5) {
        arrangeTile("linemate", 1);
        arrangeTile("deraumere", 2);
        arrangeTile("sibur", 3);
        arrangeTile("phiras", 1);
    }
    if (_level == 6) {
        arrangeTile("linemate", 2);
        arrangeTile("deraumere", 2);
        arrangeTile("sibur", 2);
        arrangeTile("mendiane", 2);
        arrangeTile("phiras", 2);
        arrangeTile("thystame", 1);
    }    
}

// Cette fonction lance le processus d'elevation, la boucle while y permet
// d'empecher l'IA de faire une autre action avant que le serveur n'est validé
// l'elevation
void Client::startIncantation(void)
{
    std::string sendStr = "Incantation\n";
    std::string rcv;
    std::string str1;
    std::string str2;

    if (send(_socket, sendStr.c_str(), sendStr.size(), 0) == -1)
        throw(sendCommandError("Incantation"));
    rcv = wait_recv("Elevation underway", "ko");
    if (rcv == "ko")
        return;
    // debug
    printf("Incantating...\n");
    //
    rcv = wait_recv("Current level:", "ko");
    if (rcv != "ko") {
        std::istringstream iss(rcv);
        iss >> str1 >> str2 >> _level;
        printf("Elevation success\n");
    } else
        printf("Elevation fail\n");
}

void Client::askAssemble(void)
{
    std::string sendStr = "Need lvl " + _level;
    sendStr += " here.";

    broadcast(sendStr);
}
