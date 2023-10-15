/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** gui
*/

#include "../../includes/class/gui.hpp"

GUI::GUI (std::shared_ptr<arg> argv) : _argv(argv)
{
    this->_socket = std::make_unique<Socket>(this->_argv->getName(), this->_argv->getPort());
    this->_content = std::make_unique<Content>();
    this->_window = std::make_unique<window>(this->_content.get(), this->_socket.get());
}

GUI::~GUI ()
{
}

void GUI::debug ()
{
    while (true) {
        std::cout << "map size x : " << _content->getMapSize().first << ", y : " << _content->getMapSize().second << std::endl;
        std::cout << "n° team : " << _content->getTeamList().size() << std::endl;
        for (auto it : _content->getTeamList())
            std::cout << "team name : " << it.getName() << std::endl;
        std::cout << "n° player : " << _content->getPlayerList().size() << std::endl;
        for (auto it : _content->getPlayerList())
            std::cout << "player n° : " << it.getId() << std::endl;
        for (auto it : _content->getPlayerList()) {
            std::cout << "\033[1;31m"; // Séquence d'échappement pour définir la couleur du texte en rouge
            std::cout << "player n° : " << it.getId() << " at " << it.getPos()->getX() << " " << it.getPos()->getY() << std::endl;
            std::cout << "\033[0m"; // Séquence d'échappement pour réinitialiser la couleur du texte à sa valeur par défaut

        }
        if (_content->getBcShow()) {
            std::cout << "broacast to player n° : " << _content->getBroadcastString() << std::endl;
            _content->setBcShow(false);
        }
        std::cout << std::endl;
        sleep(3);
    }
}

void GUI::process ()
{
    // debug();
    _window->run();
}
