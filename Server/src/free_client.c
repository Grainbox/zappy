/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void free_ia(client_t *cli)
{
    remove_all_requests(cli);
    free(cli->player->inventory);
    free(cli->player);
}

void free_client(server_t *srv, client_t *cli)
{
    if (cli == NULL)
        return;
    if (cli->buff)
        free(cli->buff);
    if (cli->type == IA)
        free_ia(cli);
    for (client_t *tmp = srv->clients; tmp; tmp = tmp->next) {
        if (tmp->next == cli) {
            tmp->next = cli->next;
            break;
        }
        if (tmp == cli) {
            srv->clients = cli->next;
            break;
        }
    }
    free(cli);
}
