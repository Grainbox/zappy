/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** IAroutine
*/

#include "Client.hpp"

void Client::setObjectif(void)
{
    askInventory();
    // if (_inventory.food <= 10) {
    //     _objective = FOOD;
    //     return;
    // }
    if (!_shareLocation && _inventory.food <= 20) {
        _objective = FOOD;
        return;
    } else
        _objective = FARM;
    if (_level == 1) {
        _objective = FARM;
        if (_inventory.food <= 20)
            _objective = FOOD;
    }
    if (_amIBalise) {
        _objective = EGG;
        if (_inventory.food <= 50)
            _objective = FOOD;
    }
}

// Boucle qui va rythmer le comportement de l'IA une fois initialisée sur le
// serveur. Objectifs : ne pas mourir et monter au niveau maximum tout en aidant
// les autres membres de son équipe (pour l'instant ne fait que survivre).
void Client::IAstart(void)
{
    while (1) {
        setObjectif();
        if (_objective == EGG)
            layEgg();
        if (_objective == FOOD) {
            printf("look for food\n");
            lookForFood();
        } else if (_objective == FARM) {
            printf("tryna elevate\n");
            manageElevation();
        }
        askInventory();
        dispInfos();
    }
}

void Client::lookForFood(void)
{
    look();
    if (isSeeingFood()) {
        goTile(_closestFood);
        _turns = 0;
        for (auto it : _sight.at(0)) {
            if (_amIBalise && it == "food") {
                take(it);
            } else if (!_amIBalise && it != "player" && it != "egg")
                take(it);
        }
    } else if (_turns < 3) {
        turnRight();
        _turns++;
    } else {
        for (int count = 0; count != _level + 1; count++)
            goForward();
        _turns = 0;
    }
}

bool Client::enoughStone(std::string stone)
{
    if ((stone == "linemate" && _inventory.linemate >= 9) ||
        (stone == "deraumere" && _inventory.deraumere >= 8) ||
        (stone == "sibur" && _inventory.deraumere >= 10) ||
        (stone == "mendiane" && _inventory.deraumere >= 5) ||
        (stone == "thystame" && _inventory.deraumere >= 1))
        return true;
    return false;
}

void Client::lookForStone(void)
{
    look();
    if (isSeeingStone()) {
        goTile(_closestStone);
        _turns = 0;
        for (auto it : _sight.at(0))
            if (it != "nothing" && it != "player" && it != "egg")
                if (!enoughStone(it))
                    take(it);
    } else if (_turns < 3) {
        turnRight();
        _turns++;
    } else {
        goForward();
        _turns = 0;
    }
}

bool Client::enoughBuddies(void)
{
    int nb_buddies = 0;

    for (auto it : _sight.at(0))
        if (it == "player")
            nb_buddies++;
    printf("BUDDIES: %d\n", nb_buddies);
    if ((_level == 2 || _level == 3) && nb_buddies == 2)
        return true;
    if ((_level == 4 || _level == 5) && nb_buddies == 4)
        return true;
    if ((_level == 6 || _level == 7) && nb_buddies == 6)
        return true;
    return false;
}

bool Client::AssembleIsFull(int size)
{
    if (((_level == 2 || _level == 3) && size >= 2) ||
        ((_level == 4 || _level == 5) && size >= 4) ||
        ((_level == 6 || _level == 7) && size >= 6))
        return true;
    return false;
}

void Client::manageElevation(void)
{
    std::string assembleCall = "Elevation request: " + std::to_string(_level);
    std::string assembleUp = "I'm up.";
    std::string assembleGo = "Ok come.";
    std::string locationSharing = "I'm here.";
    std::string IAarrived = "I arrived.";
    std::string BaliseMark = "Got this";

    if (_level == 1) {
        if (haveAllReqStones()) {
            clearTile();
            set("linemate");
            startIncantation();
            if (_level == 2) {
                askInventory();
                bool found = false;
                for (auto it : _broadcasts[0])
                    if (it.second.message == BaliseMark)
                        found = true;
                if (!found) {
                    std::cout << "I am the balise" << std::endl;
                    _amIBalise = true;
                    anwserDiscussion(0, BaliseMark);
                }
            }
        }
    }
    if (_waitIncant) {
        printf("waiting incantation\n");
        if (_assembleOwner)
            printf("made a call\n");
    }
    if (_amIBalise || _level == 1)
        return;
    if (!_waitIncant)
        lookForCall();
    if (!_waitIncant && haveAllReqStones())
        elevationCall();
    if (_waitIncant && _assembleOwner) {
        readCallAnswers();
        if (_shareLocation) {
            shareLocation();
            return;
        }
    }
    if (_waitIncant && !_assembleOwner) {
        if (!_goAssemble)
            readCallGo();
        else
            joinAssemble();
    }

    // if (_waitIncant && _assembleOwner) {
    //     readCallAnswers();
    //     if (_shareLocation) {
    //         shareLocation();
    //         return;
    //     }
    // }
    // if (!_assembleOwner) {
    //     if (!_goAssemble)
    //         readCallGo();
    //     else
    //         joinAssemble();
    // }
    
}
