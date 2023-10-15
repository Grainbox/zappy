/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

/**
 * @brief Check if player can eat and eat if he can
 *
 * @param cli The player to eat
 * @param srv Server Object
 * @return int 0 if player eat, -1 if he can't
 */
int player_eat(client_t *cli, server_t *srv)
{
    if (cli->player->inventory->food > 0) {
        cli->player->inventory->food--;
        if (cli->player->dead_ticks == 0)
            cli->player->dead_ticks = srv->ticks + 126;
        else
            cli->player->dead_ticks += 126;
        if (cli->player->dead_ticks < srv->ticks)
            player_eat(cli, srv);
        return 0;
    }
    return -1;
}

/**
 * @brief Kill player and send dead message to GUI
 *
 * @param srv Server Object
 * @param cli The player to kill
 *
 */
void kill_player(server_t *srv, client_t *cli)
{
    dprintf(cli->fd, "dead\n");
    disconnect_client(cli, srv);
}

/**
 * @brief Check if player need to eat and kill him if he need and can't
 *
 * @param srv Server Object
 *
 */
void process_player_death(server_t *srv)
{
    for (client_t *tmp = srv->clients, *next; tmp; tmp = next) {
        next = tmp->next;
        if (tmp->type != IA)
            continue;
        if (tmp->player->dead_ticks > srv->ticks)
            continue;
        if (player_eat(tmp, srv) == -1)
            kill_player(srv, tmp);
    }
}
