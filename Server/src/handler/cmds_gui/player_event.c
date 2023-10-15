/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** player_event
*/

#include "server.h"

/**
 * @brief Tell the GUI that a player died
 * @param srv Server Object
 * @param cli The player that died
*/
int gui_death_of_player(server_t *srv, client_t *cli)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pdi %d\n", cli->fd);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
