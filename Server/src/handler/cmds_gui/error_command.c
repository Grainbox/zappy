/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** error_command
*/

#include "server.h"

/**
 * @brief Called when an incorrect parameter is sent
 * @param cli Client Object
*/
void incorrect_parameter(client_t *cli)
{
    send(cli->fd, "sbp\n", 5, 0);
}

/**
 * @brief Called when the GUI try unknown command
 * @param cli Client Object
*/
void unknown_command(client_t *cli)
{
    send(cli->fd, "suc\n", 5, 0);
}
