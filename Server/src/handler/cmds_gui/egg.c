/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** egg
*/

#include "server.h"

/**
 * @brief Tell the GUI that a player is laying an egg
 * @param srv Server Object
 * @param cli The client that is laying an egg
*/
int gui_egg_laying(server_t *srv, client_t *cli)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "pfk %d\n", cli->fd);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the GUI that an egg was laid
 * @param srv Server Object
 * @param cli The Player that laid the egg
 * @param egg_id The id of the egg laid
 * @param pos The position where the egg was laid
*/
int gui_egg_laid(server_t *srv, client_t *cli, int egg_id, position_t pos)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "enw %d %d %d %d\n",
                egg_id, cli->fd, pos.x, pos.y);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the gui that a player connected for an egg
 * @param srv Server Object
 * @param egg_id The id of the egg
*/
int gui_player_con_for_egg(server_t *srv, int egg_id)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "ebo %d\n", egg_id);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the GUI tha an egg died
 * @param srv Server Object
 * @param egg_id The id of the egg
*/
int gui_egg_death(server_t *srv, int egg_id)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI)
            dprintf(srv->clients->fd, "edi %d\n", egg_id);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
