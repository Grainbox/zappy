/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** team_names
*/

#include "server.h"

/**
 * @brief Send the teams name to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int get_teams_name(server_t *srv, client_t *cli, char **args)
{
    if (get_array_size(args) != 1) {
        incorrect_parameter(cli);
        return 0;
    }
    for (int i = 0; srv->teams[i] != NULL; i++)
        dprintf(cli->fd, "tna %s\n", srv->teams[i]->name);
    return 0;
}
