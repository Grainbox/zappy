/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void process_tick(server_t *srv)
{
    process_waiting_requests(srv);
    process_refill_map(srv);
    process_player_death(srv);
}
