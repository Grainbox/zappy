/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void move_direction(server_t *srv, client_t *cli, int x, int y)
{
    int new_x = cli->player->pos.x + x;
    int new_y = cli->player->pos.y + y;

    if (new_x < 0)
        new_x = srv->settings->width - 1;
    if (new_x >= srv->settings->width)
        new_x = 0;
    if (new_y < 0)
        new_y = srv->settings->height - 1;
    if (new_y >= srv->settings->height)
        new_y = 0;
    cli->player->pos.x = new_x;
    cli->player->pos.y = new_y;
}
