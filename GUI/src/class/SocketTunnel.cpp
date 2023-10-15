/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** SocketTunnel
*/

#include "../../includes/class/socketTunel.hpp"
#include <iostream>

SocketTunnel::SocketTunnel (Socket *_socketId, Content *_content) : _socketId(_socketId), _content(_content)
{
}

SocketTunnel::~SocketTunnel ()
{
}

void SocketTunnel::Routine ()
{
    if (_socketId->selectSocket()) {
        tunelFactory(Parse(this->_socketId->listen_socket()));
    }
    restart();
}

void SocketTunnel::restart ()
{
    std::string str = "mct\n";
    if (_content->getPlayerList().size() > 0) {
        for (auto it : _content->getPlayerList()) {
            if (!it.isAlive)
                continue;
            std::string playerID = std::to_string(it.getId());
            str += "ppo " + playerID + "\n";
            str += "plv " + playerID + "\n";
            str += "pin " + playerID + "\n";
        }
    }
    _socketId->send_socket(str);
}

std::vector<std::string> SocketTunnel::Parse (std::string str)
{
    std::vector<std::string> lines;
    std::stringstream ss(str);
    std::string line;
    while (std::getline(ss, line))
        lines.push_back(line);
    return lines;
}

std::vector<std::string> SocketTunnel::Parse_lign (std::string str)
{
    std::vector<std::string> lines;
    std::stringstream iss(str);
    std::string line;
    while (iss >> line)
        lines.push_back(line);
    return lines;
}

void SocketTunnel::tunelFactory(std::vector<std::string> vectorParsed)
{
    for (auto it : vectorParsed) {
        std::vector<std::string> tmp_line = Parse_lign(it);
        if (tmp_line.empty()) {
            std::cerr << "Parse Error" << std::endl;
            continue;
        }
        if (tmp_line.front() == "WELCOME") {
            continue;
        }
        if (tmp_line.front() == "msz") {
            _content->setMapSize(tmp_line);
            continue;
        }
        if (tmp_line.front() == "bct") {
            _content->bct(tmp_line);
            continue;
        }
        if (tmp_line.front() == "tna") {
            _content->tna(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pnw") {
            _content->pnw(tmp_line);
            continue;
        }
        if (tmp_line.front() == "ppo") {
            _content->ppo(tmp_line);
            continue;
        }
        if (tmp_line.front() == "plv") {
            _content->plv(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pin") {
            _content->pin(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pex") {
            _content->pex(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pbc") {
            _content->pbc(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pic") {
            _content->pic(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pie") {
            _content->pie(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pfk") {
            _content->pfk(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pdr") {
            _content->pdr(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pgt") {
            _content->pgt(tmp_line);
            continue;
        }
        if (tmp_line.front() == "pdi") {
            _content->pdi(tmp_line);
            continue;
        }
        if (tmp_line.front() == "enw") {
            _content->enw(tmp_line);
            continue;
        }
        if (tmp_line.front() == "ebo") {
            _content->ebo(tmp_line);
            continue;
        }
        if (tmp_line.front() == "edi") {
            _content->edi(tmp_line);
            continue;
        }
        if (tmp_line.front() == "sgt") {
            _content->sgt(tmp_line);
            continue;
        }
        if (tmp_line.front() == "sst") {
            _content->sst(tmp_line);
            continue;
        }
        if (tmp_line.front() == "seg") {
            _content->seg(tmp_line);
            continue;
        }
        if (tmp_line.front() == "smg") {
            _content->smg(tmp_line);
            continue;
        }
        if (tmp_line.front() == "suc") {
            _content->suc(tmp_line);
            continue;
        }
        if (tmp_line.front() == "sbp") {
            _content->sbp(tmp_line);
            continue;
        }
    }
}
