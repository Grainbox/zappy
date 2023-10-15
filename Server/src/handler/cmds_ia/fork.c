/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int fork_first_step(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    request_t *curr = cli->player->requests;
    egg_t *new_egg = create_egg(srv, cli);
    curr->data = new_egg;
    gui_egg_laying(srv, cli);
    curr->trigger_ticks += 42;
    return 1;
}

egg_t *get_egg(request_t *request)
{
    if (request->data)
        return (egg_t *)request->data;
    return NULL;
}

int fork_ia(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    request_t *curr = cli->player->requests;

    if (curr->curr_step == 0)
        return fork_first_step(srv, cli, args);
    egg_t *new_egg = get_egg(curr);
    if (new_egg == NULL)
        return -1;
    new_egg->laid = true;
    gui_egg_laid(srv, cli, new_egg->id, new_egg->pos);
    curr->self_managed = false;
    curr->data = NULL;
    return dprintf(cli->fd, "ok\n");
}
