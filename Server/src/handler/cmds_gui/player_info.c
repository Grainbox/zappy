/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** player_info
*/

#include "server.h"

/**
 * @brief Send new player infos to all GUIs
 * @param srv Server Object
 * @param cli Client Object
*/
int new_player_connection(server_t *srv, client_t *cli)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI) {
            dprintf(srv->clients->fd, "pnw %d %d %d %d %d %s\n",
                cli->fd, cli->player->pos.x, cli->player->pos.y,
                cli->player->dir, cli->player->level,
                srv->teams[cli->team_id]->name);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Send the player position to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int player_position(server_t *srv, client_t *cli, char **args)
{
    bool found = false;
    if (get_array_size(args) != 2) {
        incorrect_parameter(cli);
        return 0;
    }
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->fd == atoi(args[1]) && srv->clients->type == IA) {
            found = true;
            dprintf(cli->fd, "ppo %d %d %d %d\n", srv->clients->fd,
                srv->clients->player->pos.x, srv->clients->player->pos.y,
                srv->clients->player->dir);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    if (!found)
        incorrect_parameter(cli);
    return 0;
}

/**
 * @brief Send the player level to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int player_level(server_t *srv, client_t *cli, char **args)
{
    bool found = false;
    if (get_array_size(args) != 2) {
        incorrect_parameter(cli);
        return 0;
    }
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->fd == atoi(args[1]) && srv->clients->type == IA) {
            found = true;
            dprintf(cli->fd, "plv %d %d\n", srv->clients->fd,
                srv->clients->player->level);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    if (!found)
        incorrect_parameter(cli);
    return 0;
}

/**
 * @brief Send the player inventory to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
static void send_inventory(server_t *srv, client_t *cli)
{
    dprintf(cli->fd, "pin %d %d %d %d %d %d %d %d %d %d\n",
        srv->clients->fd, srv->clients->player->pos.x,
        srv->clients->player->pos.y,
        srv->clients->player->inventory->food,
        srv->clients->player->inventory->linemate,
        srv->clients->player->inventory->deraumere,
        srv->clients->player->inventory->sibur,
        srv->clients->player->inventory->mendiane,
        srv->clients->player->inventory->phiras,
        srv->clients->player->inventory->thystame);
}

/**
 * @brief Get the player inventory to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int player_inventory(server_t *srv, client_t *cli, char **args)
{
    bool found = false;
    if (get_array_size(args) != 2) {
        incorrect_parameter(cli);
        return 0;
    }
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->fd == atoi(args[1]) && srv->clients->type == IA) {
            found = true;
            send_inventory(srv, cli);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    if (!found)
        incorrect_parameter(cli);
    return 0;
}
