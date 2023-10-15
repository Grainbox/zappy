/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Communication
*/

#include "Client.hpp"

void Client::elevationCall(void)
{
    std::string assembleCall = "Elevation request: " + std::to_string(_level);

    _waitingCanal = startDiscussion(assembleCall);
    printf("ELEVATION CALL SEND\n");
    _waitIncant = true;
    _assembleOwner = true;
}

void Client::lookForCall(void)
{
    std::string assembleUp = "I'm up.";
    std::string cmp = "Elevation request:";
    std::string str1;
    std::string str2;
    int lvlAsked = 0;

    for (auto it : _broadcasts)
        for (auto it2 : it.second)
            if (cmp.compare(0, cmp.size(), it2.second.message, 0, cmp.size()) == 0 &&
                !AssembleIsFull(it.second.size())) {
                std::istringstream iss(it2.second.message);
                iss >> str1 >> str2 >> lvlAsked;
                if (lvlAsked == _level) {
                    anwserDiscussion(it.first, assembleUp);
                    _waitingCanal = it.first;
                    _waitIncant = true;
                    _assembleOwner = false;
                }
            }
}

void Client::readCallGo(void)
{
    std::string assembleGo = "Ok come.";

    for (auto it : _broadcasts)
        if (it.first == _waitingCanal)
            for (auto it2 : it.second)
                if (it2.second.message == assembleGo)
                    _goAssemble = true;
}

void Client::readCallAnswers(void)
{
    int responses = 0;
    std::string assembleUp = "I'm up.";
    std::string assembleGo = "Ok come.";
    std::string askLocation = "Where ?";
    std::string shareLocation = "I'm here.";

    // for (auto it : _broadcasts[_waitingCanal])
    //     printf("msg: %s\n", it.second.message.c_str());

    printf("LAST: %s\n", _broadcasts[_waitingCanal].rbegin()->second.message.c_str());

    if (_broadcasts[_waitingCanal].rbegin()->second.message == askLocation)
        anwserDiscussion(_waitingCanal, shareLocation);
    if (!_shareLocation) {
        for (auto it : _broadcasts[_waitingCanal])
            if (it.second.message == assembleUp)
                responses++;
        if (responses == 0)
            return;
        if (((_level % 2 == 0) && responses == _level - 1) ||
            ((_level % 2 != 0) && responses == _level - 2)) {
            anwserDiscussion(_waitingCanal, assembleGo);
            anwserDiscussion(_waitingCanal, shareLocation);
            _shareLocation = true;
        }
    }
}

void Client::shareLocation(void)
{
    int arrived = 0;
    std::string locationSharing = "I'm here.";
    std::string IAarrived = "I arrived.";
    std::string askLocation = "Where ?";

    if (_broadcasts[_waitingCanal].rbegin()->second.message == askLocation) {
        anwserDiscussion(_waitingCanal, locationSharing);
        return;
    } else if (_broadcasts[_waitingCanal].rbegin()->second.message == IAarrived) {
        for (auto it : _broadcasts[_waitingCanal])
            if (it.second.message == IAarrived)
                arrived++;
        if (((_level == 2 || _level == 3) && arrived == 1) ||
            ((_level == 4 || _level == 5) && arrived == 3) ||
            ((_level == 6 || _level == 7) && arrived == 5)) {
            setupIncantation();
            startIncantation();
            _waitIncant = false;
            _assembleOwner = false;
            _waitingCanal = -1;
        }
    }
}

void Client::joinAssemble(void)
{
    std::string assembleGo = "Ok come.";
    std::string locationSharing = "I'm here.";
    std::string IAarrived = "I arrived.";
    std::string askLocation = "Where ?";

    printf("joinAssemble\n");

    // for (auto it : _broadcasts[_waitingCanal])
    //     printf("msg: %s\n", it.second.message.c_str());
    // if (_broadcasts.find(_waitingCanal))
    //     printf("found\n");
    // printf("last msg: %s\n", _broadcasts[_waitingCanal].rbegin()->second.message.c_str());
    printf("LAST: %s\n", _broadcasts[_waitingCanal].rbegin()->second.message.c_str());
    if (_broadcasts[_waitingCanal].rbegin()->second.message == assembleGo ||
        _broadcasts[_waitingCanal].rbegin()->second.message == locationSharing) {
        printf("in\n");
        if (_broadcasts[_waitingCanal].rbegin()->first != _assembleMsgID) {
            _assembleMsgID = _broadcasts[_waitingCanal].rbegin()->first;
            _assembleDirection = _broadcasts[_waitingCanal].rbegin()->second.come_from;
        }
        // if (_broadcasts[_waitingCanal].rbegin()->second.come_from != _assembleDirection)
        //     _assembleDirection = _broadcasts[_waitingCanal].rbegin()->second.come_from;
        // else {
        //     anwserDiscussion(_waitingCanal, askLocation);
        //     return;
        // }
    } else
        return;
    printf("Direction: %d\n", _assembleDirection);
    if (_assembleDirection == 0) {
        anwserDiscussion(_waitingCanal, IAarrived);
        printf("ARRIVED--------------------------------------------------------\n");
        wait_recv("Elevation underway", "ko");
        _waitIncant = false;
        _goAssemble = false;
        return;
    }
    assembleOrient();
    int otherPlayerTile = seePlayer();
    if (otherPlayerTile != -1)
        goTile(otherPlayerTile);
    else
        for (int i = 0; i != _level; i++)
            goForward();
    anwserDiscussion(_waitingCanal, askLocation);
}
