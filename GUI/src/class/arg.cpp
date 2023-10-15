/*
** EPITECH PROJECT, 2023
** GUI
** File description:
** arg
*/

#include "../../includes/class/gui.hpp"
#include <sstream>
#include <string>

arg::arg (int argc, char **argv)
{
    std::string port_tmp = "-1";

    if (argc > 5)
        throw ArgError("too many arguments");
    for (int i = 1; i <= argc; i++) {
        if ((std::string) argv[i - 1] == "-p") {
            port_tmp = argv[i];
        }
        if ((std::string) argv[i - 1] == "-h") {
            if ((std::string) argv[i] != "localhost")
                this->name = argv[i];
        }
    }
    if (port_tmp == "-1")
        throw ArgError("bad port number");
    for (int i = 0; i < (int) port_tmp.size(); i++) {
        if (port_tmp[i] < '0' || port_tmp[i] > '9')
            throw ArgError("bad port number");
    }
    std::stringstream(port_tmp) >> this->port;
    if (this->port < 0 || this->port > 65535)
        throw ArgError("bad port number");
}
