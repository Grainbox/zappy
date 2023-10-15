/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** Look
*/

#include "Client.hpp"

void Client::baliseDiscussion(std::string message)
{
    std::ostringstream oss;
    oss << "hel" << 0 << "lo " << message;
    std::size_t id = _broadcasts[0].size();
    _broadcasts[0][(int)id] = {oss.str(), 0, std::chrono::system_clock::now()};
    broadcast(oss.str());
}

int Client::startDiscussion(std::string message)
{
    channelId++;

    std::ostringstream oss;
    oss << "hel" << channelId << "." << 0 << "." << channelId << "lo " << message;
    _broadcasts[channelId][0] = {oss.str(), 0, std::chrono::system_clock::now()};
    broadcast(oss.str());
    return channelId;
}

void Client::anwserDiscussion(int id, std::string message)
{
    auto channel = _broadcasts.find(id);
    int id_2 = 0;

    if (channel != _broadcasts.end()) {
        for (auto it : _broadcasts[id])
            id_2++;
        std::ostringstream oss;
        oss << "hel" << id << "." << id_2 << "." << channelId << "lo " << message;
        _broadcasts[id][id_2] = {oss.str(), 0, std::chrono::system_clock::now()};
        broadcast(oss.str());
    } else {
        std::cerr << "Invalid broadcast id" << std::endl;
    }
    if (id == 0 && message == "Got this") {
        startDiscussion("This is da wae");
    }
}
