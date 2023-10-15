/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int get_player_nb(server_t *srv, int x, int y)
{
    int res = 0;
    client_t *cli = srv->clients;
    while (cli) {
        if (cli->type == IA && cli->player->pos.x == x
            && cli->player->pos.y == y)
            res++;
        cli = cli->next;
    }
    return res;
}
