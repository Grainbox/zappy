/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void process_direction(server_t *srv, client_t *cli)
{
    if (cli->player->dir == UP) {
        move_direction(srv, cli, 0, -1);
        dprintf(cli->fd, "eject: %d\n", REVERSE_UP);
    }
    if (cli->player->dir == DOWN) {
        move_direction(srv, cli, 0, 1);
        dprintf(cli->fd, "eject: %d\n", REVERSE_DOWN);
    }
    if (cli->player->dir == LEFT) {
        move_direction(srv, cli, -1, 0);
        dprintf(cli->fd, "eject: %d\n", REVERSE_LEFT);
    }
    if (cli->player->dir == RIGHT) {
        move_direction(srv, cli, 1, 0);
        dprintf(cli->fd, "eject: %d\n", REVERSE_RIGHT);
    }
}

static int eject_players(server_t *srv, client_t *cli, int x, int y)
{
    client_t *tmp = srv->clients;
    int ejected = 0;

    while (tmp) {
        if (tmp != cli && tmp->type == IA &&
        tmp->player->pos.x == x && tmp->player->pos.y == y) {
            process_direction(srv, tmp);
            ejected++;
        }
        tmp = tmp->next;
    }
    return ejected;
}

int eject(server_t *srv, client_t *cli, char **args)
{
    (void)srv;
    (void)args;
    int ejected = 0, destroyed = 0;

    ejected = eject_players(srv, cli, cli->player->pos.x, cli->player->pos.y);
    destroyed = destroy_eggs(srv, cli->player->pos.x, cli->player->pos.y);
    if (ejected > 0 || destroyed > 0)
        dprintf(cli->fd, "ok\n");
    else
        return (-1);
    return 0;
}
