/*
** EPITECH PROJECT, 2023
** Projet
** File description:
** main
*/

#include "my.hpp"

void help ()
{
    std::cout << "USAGE: ./zappy_ai -p port -h machine" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    exit(0);
}

int main (int argc, char **argv)
{
    if (argc == 2 && (std::string) argv[1] == "-help")
        help();
    if (argc < 3)
        exit(84);
    try {
        std::shared_ptr<arg> _arg = std::make_shared<arg>(argc, argv);
        GUI gui(_arg);
        gui.process();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
