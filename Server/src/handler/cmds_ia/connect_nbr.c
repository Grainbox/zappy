/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int connect_nbr(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    int av_slots = 0;
    if (cli->team_id == -1)
        return 0;
    teams_t *team = srv->teams[cli->team_id];
    av_slots = srv->settings->user_per_team - team->nb_clients;
    av_slots += get_layed_egg(srv, cli->team_id);
    return dprintf(cli->fd, "%d\n", av_slots);
}
