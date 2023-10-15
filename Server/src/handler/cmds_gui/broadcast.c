/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** broadcast
*/

#include "server.h"

/**
 * @brief Tell the GUI that a player broadcast a message
 * @param srv Server Object
 * @param cli Player who broadcast
 * @param message The massage sent by the player
*/
int gui_broadcast(server_t *srv, client_t *cli, char *message)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pbc %d %s\n", cli->fd, message);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the GUI that the server sent a message
 * @param srv Server Object
 * @param message The message sent
*/
int gui_message_from_server(server_t *srv, char *message)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "smg %s\n", message);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
