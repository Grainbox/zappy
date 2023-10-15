/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** resource
*/

#include "server.h"

/**
 * @brief Tell the GUI that a player dropped some resources
 * @param srv Server Object
 * @param cli The client that is dropping resources
 * @param nb_resource Nb of resources dropped
*/
int gui_resource_dropping(server_t *srv, client_t *cli, int nb_resource)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pdr %d %d\n", cli->fd, nb_resource);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the GUI that a player collected resources
 * @param srv Server Object
 * @param cli The client that dropped resources
 * @param nb_resource Nb of dropped resources
*/
int gui_collect_resource(server_t *srv, client_t *cli, int nb_resource)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pgt %d %d\n", cli->fd, nb_resource);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
