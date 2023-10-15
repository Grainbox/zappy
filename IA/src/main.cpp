/*
** EPITECH PROJECT, 2023
** Projet
** File description:
** main
*/

#include "ErrorHandling.hpp"
#include "Client.hpp"

// Display des information d'aide pour l'utilisation du binaire.
static void disp_help(void)
{
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl <<
    "\tport\tis the port number" << std::endl <<
    "\tname\tis the name of the team" << std::endl <<
    "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

// Vérification des arguments, pour l'instant vérifie juste le "-help" et throw
// une erreur si trop peu d'arg (2).
static void check_error(int ac, char **av)
{
    if (ac == 2) {
        std::string arg = av[1];
        if (arg == "-help") {
            disp_help();
            throw (HelpDisplay());
        } else
            throw (ArgNumberError());
    }
}

// main du binaire, vérifie les argument puis lance la création du client.
int main(int ac, char **av)
{
    try {
        check_error(ac, av);
        Client client(ac, av);
    } catch (HelpDisplay &e) {
        return 0;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    return 0;
}
