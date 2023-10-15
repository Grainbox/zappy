/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

position_t get_pos_in_map(server_t *srv, int x, int y)
{
    position_t pos = {0, 0};

    while (x < 0)
        x += srv->settings->width;
    while (y < 0)
        y += srv->settings->height;
    while (x >= srv->settings->width)
        x -= srv->settings->width;
    while (y >= srv->settings->height)
        y -= srv->settings->height;
    pos.x = x;
    pos.y = y;
    return pos;
}
