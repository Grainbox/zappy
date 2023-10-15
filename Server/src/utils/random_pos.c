/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

position_t random_pos(server_t *srv)
{
    position_t pos;
    pos.x = rand() % srv->settings->width;
    pos.y = rand() % srv->settings->height;
    return pos;
}
