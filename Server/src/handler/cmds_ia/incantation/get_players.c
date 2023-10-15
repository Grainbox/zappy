/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

/**
 * @brief check if the player is eligible for the incantation
 * (same level, same position)
 * @param client (client to check)
 * @param leader (client who called the incantation)
 * @return true (if eligible else false)
 */
static bool player_is_eligible(client_t *client, client_t *leader)
{
    if (!client || !leader || !client->player || !leader->player)
        return (false);
    if (client->player->level != leader->player->level)
        return (false);
    if (client->player->pos.x != leader->player->pos.x)
        return (false);
    if (client->player->pos.y != leader->player->pos.y)
        return (false);
    return (true);
}

/**
 * @brief Get the next client by fd object
 *
 * @param list (clients list)
 * @param min_fd (min fd to check)
 * @return client_t* (client with the next fd (closest to min_fd))
 */
static client_t *get_nxt_cli_by_fd(client_t *list, int min_fd, client_t *lead)
{
    client_t *tmp = list;
    client_t *res = NULL;

    while (tmp) {
        if (tmp->fd > min_fd && (!res || tmp->fd < res->fd))
            res = tmp;
        tmp = tmp->next;
    }
    if (res && res->fd == lead->fd)
        return (NULL);
    return res;
}

/**
 * @brief Get all clients eligible object (sorted by priority)
 *
 * @param server
 * @param leader (client who called the incantation)
 * @return new list of clients eligible for the incantation (sorted by priority)
 */
client_t **get_clients_eligible(server_t *srv, client_t *leader)
{
    client_t *tmp = NULL;
    client_t **eligible = NULL;
    int selected = 1, min_fd = 0, size = 0;

    eligible = add_client(eligible, leader, &size);
    while ((tmp = get_nxt_cli_by_fd(srv->clients, min_fd, leader)) != NULL) {
        min_fd = tmp->fd;
        if (player_is_eligible(tmp, leader)) {
            eligible = add_client(eligible, tmp, &size);
            selected++;
        }
    }
    if (!selected || !eligible)
        return (NULL);
    eligible = realloc(eligible, sizeof(client_t *) * (selected + 1));
    eligible[selected] = NULL;
    return (eligible);
}
