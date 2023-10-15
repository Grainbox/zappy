/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void disconnect_client(client_t *cli, server_t *srv)
{
    if (cli == NULL || srv == NULL)
        return;
    if (cli->type == IA) {
        srv->teams[cli->team_id]->nb_clients--;
        gui_death_of_player(srv, cli);
    }
    FD_CLR(cli->fd, &srv->read_fds);
    close(cli->fd);
    free_client(srv, cli);
}
