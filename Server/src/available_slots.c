/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int get_available_slots(server_t *srv, int team_id)
{
    int available_slots = srv->settings->user_per_team -
    ++srv->teams[team_id]->nb_clients;
    available_slots += get_layed_egg(srv, team_id);
    return available_slots;
}
