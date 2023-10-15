/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

egg_t *create_egg(server_t *srv, client_t *cli)
{
    egg_t *egg = malloc(sizeof(egg_t));
    egg->id = srv->egg_id++;
    egg->pos = random_pos(srv);
    printf("Create eggs for team: %d\n", cli->team_id);
    egg->team_id = cli->team_id;
    egg->next = srv->eggs;
    srv->eggs = egg;
    return egg;
}

int destroy_eggs(server_t *srv, int x, int y)
{
    egg_t *tmp = srv->eggs, *prev = NULL;
    int destroyed = 0;
    while (tmp) {
        if (tmp->pos.x != x || tmp->pos.y != y) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        if (prev)
            prev->next = tmp->next;
        else
            srv->eggs = tmp->next;
        gui_egg_death(srv, tmp->id);
        free(tmp);
        destroyed++;
        prev = tmp;
        tmp = tmp->next;
    }
    return destroyed;
}

int get_layed_egg(server_t *srv, int team_id)
{
    printf("Searching for eggs in team %d\n", team_id);
    egg_t *tmp = srv->eggs;
    int laid = 0;
    while (tmp) {
        printf("Egg team id: %d\n", tmp->team_id);
        if (tmp->team_id == team_id && tmp->laid)
            laid++;
        tmp = tmp->next;
    }
    printf("laid: %d\n", laid);
    return laid;
}
