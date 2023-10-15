/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** create_content
*/

#include "server.h"

/**
 * @brief Create the map array
 * @param settings Where the map size is located
*/
tile_t ***create_map(settings_t *settings)
{
    int i = 0;
    tile_t ***map = malloc(sizeof(tile_t **) * (settings->height + 1));

    for (; i < settings->height; i++) {
        map[i] = malloc(sizeof(tile_t *) * (settings->width + 1));
        for (int j = 0; j < settings->width; j++) {
            map[i][j] = malloc(sizeof(tile_t));
            map[i][j]->food = 0;
            map[i][j]->deraumere = 0;
            map[i][j]->linemate = 0;
            map[i][j]->mendiane = 0;
            map[i][j]->phiras = 0;
            map[i][j]->sibur = 0;
            map[i][j]->thystame = 0;
            map[i][j + 1] = NULL;
        }
    }
    map[settings->height] = NULL;
    refill_map(map, settings);
    return map;
}

/**
 * @brief Create the teams structures and add it to the server objec
 * @param srv Server Object
*/
void create_teams(server_t *srv)
{
    int nb_team = 0;

    for (; srv->settings->teams_name[nb_team] != NULL; nb_team++);
    srv->teams = malloc(sizeof(teams_t *) * (nb_team + 1));
    srv->teams[nb_team] = NULL;
    for (int i = 0; srv->settings->teams_name[i] != NULL; i++) {
        srv->teams[i] = malloc(sizeof(teams_t));
        srv->teams[i]->id = i;
        srv->teams[i]->nb_clients = 0;
        srv->teams[i]->name = srv->settings->teams_name[i];
    }
}
