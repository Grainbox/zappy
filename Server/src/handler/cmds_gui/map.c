/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** map
*/

#include "server.h"

/**
 * @brief Send the content of a tile to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int content_of_tile(server_t *srv, client_t *cli, char **args)
{
    if (get_array_size(args) != 3) {
        incorrect_parameter(cli);
        return 0;
    }
    int x = atoi(args[1]);
    int y = atoi(args[2]);

    if ((x < 0 || y < 0) ||
        (x >= srv->settings->width || y >= srv->settings->height)) {
        incorrect_parameter(cli);
        return 0;
    }
    dprintf(cli->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        srv->map[y][x]->food,
        srv->map[y][x]->linemate, srv->map[y][x]->deraumere,
        srv->map[y][x]->sibur, srv->map[y][x]->mendiane,
        srv->map[y][x]->phiras, srv->map[y][x]->thystame);
    return 0;
}

/**
 * @brief Send all the map content to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int content_of_map(server_t *srv, client_t *cli, char **args)
{
    if (get_array_size(args) != 1) {
        incorrect_parameter(cli);
        return 0;
    }
    for (int y = 0; srv->map[y] != NULL; y++) {
        for (int x = 0; srv->map[y][x] != NULL; x++) {
            char str_x[16];
            char str_y[16];
            sprintf(str_x, "%d", x);
            sprintf(str_y, "%d", y);
            char *tile[] = {"bct", str_x, str_y, NULL};
            content_of_tile(srv, cli, tile);
        }
    }
    return 0;
}

/**
 * @brief Send the map size to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int get_map_size(server_t *srv, client_t *cli, char **args)
{
    (void)args;

    dprintf(cli->fd, "msz %d %d\n",
        srv->settings->width, srv->settings->height);
    return 0;
}
