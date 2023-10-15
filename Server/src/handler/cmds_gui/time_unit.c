/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** time_unit
*/

#include "server.h"

/**
 * @brief Send the time unit to the GUI who asked
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int get_time_unit(server_t *srv, client_t *cli, char **args)
{
    if (get_array_size(args) != 1) {
        incorrect_parameter(cli);
        return 0;
    }
    dprintf(cli->fd, "sgt %d\n", srv->settings->freq);
    return 0;
}

/**
 * @brief Set the time unit
 * @param srv Server Object
 * @param cli Client Object
 * @param args Command sent as char **
*/
int set_time_unit(server_t *srv, client_t *cli, char **args)
{
    if (get_array_size(args) != 2) {
        incorrect_parameter(cli);
        return 0;
    }
    int time_unit = atoi(args[1]);
    srv->settings->freq = time_unit;
    dprintf(cli->fd, "sst %d\n", time_unit);
    return 0;
}
