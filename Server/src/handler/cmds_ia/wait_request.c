/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

size_t waiting_requests_len(client_t *client)
{
    size_t len = 0;
    request_t *tmp = client->player->requests;

    while (tmp) {
        len++;
        tmp = tmp->next;
    }
    return (len);
}

size_t get_request_trigger_ticks(client_t *cli, command_t *cmd, size_t c_tick)
{
    request_t *tmp = cli->player->requests;

    if (waiting_requests_len(cli) == 0) {
        if (cmd->self_managed)
            return (c_tick);
        else
            return (c_tick + cmd->execution_time);
        }
    while (tmp->next)
        tmp = tmp->next;
    if (cmd->self_managed)
        return (tmp->trigger_ticks);
    return (tmp->trigger_ticks + cmd->execution_time);
}

bool add_request(client_t *client, char **args, command_t *cmd, size_t c_tick)
{
    if (waiting_requests_len(client) >= MAX_WAITING_REQUESTS)
        return (false);
    request_t *new_request = calloc(1, sizeof(request_t));
    new_request->args = args;
    new_request->func = cmd->func;
    new_request->self_managed = cmd->self_managed;
    new_request->trigger_ticks = get_request_trigger_ticks(client, cmd, c_tick);
    if (!client->player->requests) {
        client->player->requests = new_request;
        return (true);
    }
    request_t *tmp = client->player->requests;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_request;
    return (true);
}

void remove_request(client_t *client, request_t *request)
{
    request_t *tmp = client->player->requests, *prev = NULL;
    while (tmp && tmp != request) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp != request)
        return;
    if (prev)
        prev->next = tmp->next;
    else
        client->player->requests = tmp->next;
    if (tmp->data)
        free(tmp->data);
    if (tmp->args) {
        free(tmp->args);
    }
    free(tmp);
}

void remove_all_requests(client_t *client)
{
    while (client->player->requests)
        remove_request(client, client->player->requests);
}
