/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** expulsion
*/

#include "server.h"

/**
 * @brief Tell the GUI that a client expulsed someone
 * @param srv Server Object
 * @param cli Client Object
*/
int gui_expulsion(server_t *srv, client_t *cli)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pex %d\n", cli->fd);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
