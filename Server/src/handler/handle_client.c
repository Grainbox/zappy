/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

static ssize_t read_client(client_t *cli)
{
    char buffer[1024] = {0};
    ssize_t read_result = read(cli->fd, buffer, 1024);

    if (read_result <= 0)
        return (read_result);
    if (cli->buff == NULL) {
        cli->buff = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(cli->buff, buffer);
    } else {
        cli->buff = realloc(cli->buff, strlen(cli->buff) + strlen(buffer) + 1);
        strcat(cli->buff, buffer);
    }
    if (read_result == 1024)
        read_result += read_client(cli);
    return (read_result);
}

static int handle_client(server_t *srv, client_t **cli_ptr)
{
    client_t *client = *cli_ptr;
    ssize_t read_result = read_client(client);

    if (read_result <= 0) {
        disconnect_client(client, srv);
        *cli_ptr = srv->clients;
        return (read_result == 0 ? 0 : 84);
    }

    int error = handle_request(srv, client);
    return (error);
}

void handle_new_client(server_t *srv)
{
    client_t *new_client = malloc(sizeof(client_t));
    if (new_client == NULL)
        return;
    socklen_t addrlen = sizeof(srv->addr);
    int ns = accept(srv->sc, (struct sockaddr *)&srv->addr, &addrlen);
    if (ns < 0) {
        free(new_client);
        return;
    }
    new_client->fd = ns;
    new_client->type = UNDEFINED;
    new_client->team_id = -1;
    new_client->next = srv->clients;
    new_client->player = NULL;
    new_client->buff = NULL;
    srv->clients = new_client;
    FD_SET(ns, &srv->read_fds);
    if (ns > srv->max_fd)
        srv->max_fd = ns;
    dprintf(new_client->fd, "WELCOME\n");
}

int handle_clients(server_t *srv)
{
    int error = 0;
    for (client_t *curr = srv->clients; curr != NULL; curr = curr->next) {
        if (FD_ISSET(curr->fd, &srv->read_fds)) {
            error += handle_client(srv, &curr);
        }
        if (curr == NULL)
            break;
    }
    return (error);
}
