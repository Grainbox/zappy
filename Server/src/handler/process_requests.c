/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

static void abort_request(client_t *cli, request_t *req)
{
    dprintf(cli->fd, "ko\n");
    remove_request(cli, req);
}

void process_request(server_t *srv, client_t *cli)
{
    char **args = NULL;
    int request_ret = 0;
    request_t *curr = cli->player->requests;

    if (!curr)
        return;
    args = curr->args;
    if (curr->func)
        request_ret = curr->func(srv, cli, args);
    else
        request_ret = -1;
    curr->curr_step++;
    if (request_ret == -1)
        return abort_request(cli, curr);
    if (!curr->self_managed)
        remove_request(cli, curr);
}

void process_waiting_requests(server_t *srv)
{
    for (client_t *curr = srv->clients; curr != NULL; curr = curr->next) {
        if (curr->type != IA || waiting_requests_len(curr) == 0)
            continue;
        if (curr->player->requests->trigger_ticks <= srv->ticks) {
            process_request(srv, curr);
        }
    }
}
