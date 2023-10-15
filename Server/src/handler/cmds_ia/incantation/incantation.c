/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

static bool tile_already_in_incantation(server_t *srv, position_t pos)
{
    for (client_t *tmp = srv->clients; tmp; tmp = tmp->next) {
        if (tmp->type == IA && tmp->player->incantation &&
        tmp->player->pos.x == pos.x && tmp->player->pos.y == pos.y)
            return true;
    }
    return false;
}

static bool has_enough_players(client_t **to_elevate)
{
    int nb_players = 0;

    for (int i = 0; to_elevate[i]; i++)
        nb_players++;
    if (nb_players < 1)
        return false;
    if (nb_players_for_incantation(to_elevate[0]->player->level) < nb_players)
        return false;
    return true;
}

static int first_step(server_t *srv, client_t *cli)
{
    request_t *curr = cli->player->requests;

    if (tile_already_in_incantation(srv, cli->player->pos))
        return -1;
    if (!tile_has_resources(srv, cli->player->pos, cli->player->level))
        return -1;
    client_t **to_elevate = get_clients_eligible(srv, cli);
    if (!to_elevate || !has_enough_players(to_elevate))
        return -1;
    curr->data = (void *)to_elevate;

    for (int i = 0; to_elevate[i]; i++) {
        to_elevate[i]->player->incantation = true;
        dprintf(to_elevate[i]->fd, "Elevation underway\n");
    }
    curr->trigger_ticks += 300;
    return (0);
}

static int second_step(server_t *srv, client_t *cli)
{
    request_t *curr = cli->player->requests;
    client_t **to_elevate = curr->data;

    for (int i = 0; to_elevate[i]; i++) {
        if (client_is_online(srv, to_elevate[i]) == false)
            return incantation_failed(srv, cli);
    }
    if (!tile_use_resources(srv, cli->player->pos, cli->player->level))
        incantation_failed(srv, cli);
    for (int i = 0; to_elevate[i]; i++) {
        to_elevate[i]->player->incantation = false;
        to_elevate[i]->player->level++;
        dprintf(to_elevate[i]->fd, "Current level: %d\n",
        to_elevate[i]->player->level);
    }
    gui_end_incant(srv, cli->player->pos, cli->player->level);
    return (0);
}

int incantation(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    request_t *curr = cli->player->requests;

    if (curr->curr_step == 0) {
        int tmp = first_step(srv, cli);
        return tmp;
    }
    if (curr->curr_step == 1) {
        int tmp = second_step(srv, cli);
        curr->self_managed = false;
        return tmp;
    }
    return (-1);
}
