/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

char *args_to_str(char **args)
{
    char *str = NULL;
    for (size_t i = 1; args[i] != NULL; i++) {
        str = append(str, args[i]);
        str = append(str, " ");
    }
    return str;
}

void send_message_to_all_players(server_t *srv, client_t *cli, char *msg)
{
    client_t *tmp = srv->clients;
    vector_t max = (vector_t){srv->settings->width, srv->settings->height};
    while (srv->clients != NULL) {
        if (srv->clients->type == IA && srv->clients != cli) {
            vector_t v = shortest_torus_vector(cli->player->pos,
                srv->clients->player->pos, max);
            int dir = vector_to_direction(v);
            dir += srv->clients->player->dir - 1;
            dir = dir % 8 + 1;
            dprintf(srv->clients->fd, "message %d, %s\n", dir, msg);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
}

int broadcast(server_t *srv, client_t *cli, char **args)
{
    if (args_count(args) < 2) {
        return (-1);
    }
    char *msg = args_to_str(args);
    dprintf(cli->fd, "ok\n");
    gui_broadcast(srv, cli, msg);
    send_message_to_all_players(srv, cli, msg);
    free(msg);
    return (0);
}
