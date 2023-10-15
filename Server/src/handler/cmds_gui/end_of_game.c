/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** end_of_game
*/

#include "server.h"

/**
 * @brief Tell the GUI that a team ended the game
 * @param srv Server Object
 * @param team_name The team that ended the game
*/
int gui_end_of_game(server_t *srv, char *team_name)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "seg %s\n", team_name);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
