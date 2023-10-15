/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** incantation
*/

#include "server.h"

static void fill_buffer(char *buffer, int *other_ids)
{
    for (int i = 0; other_ids[i] != -1; i++) {
        int byte_written = sprintf(buffer, "%d ", other_ids[i]);
        buffer += byte_written;
    }
}

/**
 * @brief Tell the GUI that an IA started incantation
 * @param srv Server Object
 * @param cli Client who started incantation
 * @param other_id An array with the ids of the other players incantating with
 *                  -1 at the end
*/
int gui_start_incant(server_t *srv, client_t *cli, int *other_ids)
{
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char* buffer_ptr = buffer;
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI) {
            int byte_written = sprintf(buffer_ptr, "pic %d %d %d ",
                cli->player->pos.x, cli->player->pos.y, cli->fd);
            buffer_ptr += byte_written;
            fill_buffer(buffer_ptr, other_ids);
            buffer[strlen(buffer) - 1] = '\n';
            dprintf(srv->clients->fd, "%s", buffer);
        }
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}

/**
 * @brief Tell the GUI that an incantation is finished
 * @param srv Server Object
 * @param pos The incantation position
 * @param result The incantation result
*/
int gui_end_incant(server_t *srv, position_t pos, int result)
{
    client_t *tmp = srv->clients;
    while (srv->clients != NULL) {
        if (srv->clients->type == GUI && result != -1)
            dprintf(srv->clients->fd, "pie %d %d %d\n", pos.x, pos.y, result);
        if (srv->clients->type == GUI && result == -1)
            dprintf(srv->clients->fd, "pie %d %d ko\n", pos.x, pos.y);
        srv->clients = srv->clients->next;
    }
    srv->clients = tmp;
    return 0;
}
