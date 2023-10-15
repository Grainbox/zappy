/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int incantation_failed(server_t *server, client_t *client)
{
    request_t *curr = client->player->requests;
    client_t **to_elevate = curr->data;

    for (int i = 0; to_elevate[i]; i++) {
        dprintf(to_elevate[i]->fd, "ko\n");
        to_elevate[i]->player->incantation = false;
    }

    gui_end_incant(server, client->player->pos, -1);
    curr->self_managed = false;
    return (0);
}
