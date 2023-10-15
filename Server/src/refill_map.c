/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** refill_map
*/

#include "server.h"

/**
 * @brief Ajust the tile content to be the same as the density
 * @param map The current map
 * @param settings The settings of the server
 * @param miss The tile with the missing content (ptr)
 * @info the min value of a tile is 0
*/
static void tile_ajustment(tile_t ***map, settings_t *settings, tile_t *m)
{
    for (int i = 0; i < settings->height; i++)
        for (int j = 0; j < settings->width; j++) {
            m->food = POS_OR_ZERO(m->food - map[i][j]->food);
            m->linemate = POS_OR_ZERO(m->linemate - map[i][j]->linemate);
            m->deraumere = POS_OR_ZERO(m->deraumere - map[i][j]->deraumere);
            m->sibur = POS_OR_ZERO(m->sibur - map[i][j]->sibur);
            m->mendiane = POS_OR_ZERO(m->mendiane - map[i][j]->mendiane);
            m->phiras = POS_OR_ZERO(m->phiras - map[i][j]->phiras);
            m->thystame = POS_OR_ZERO(m->thystame - map[i][j]->thystame);
        }
}

/**
 * @brief return the content of a tile using the settings and the density
 * @param settings The settings of the server
 * @return tile_t The content of the tile
*/
static tile_t get_tile_content(tile_t ***map, settings_t *settings)
{
    tile_t tile = {0};
    int height = settings->height, width = settings->width;
    tile.food = height * width * 0.5;
    tile.linemate = height * width * 0.3;
    tile.deraumere = height * width * 0.15;
    tile.sibur = height * width * 0.1;
    tile.mendiane = height * width * 0.1;
    tile.phiras = height * width * 0.08;
    tile.thystame = height * width * 0.05;

    tile_ajustment(map, settings, &tile);
    return (tile);
}

/**
 * @brief Refill the map
 * @param map The map to be refilled
 * @param settings The settings of the server
*/
void refill_map(tile_t ***map, settings_t *settings)
{
    tile_t tile = get_tile_content(map, settings);
    int height = settings->height;
    int width = settings->width;

    for (int i = 0; i < tile.food; i++)
        map[rand() % height][rand() % width]->food += 1;
    for (int i = 0; i < tile.linemate; i++)
        map[rand() % height][rand() % width]->linemate += 1;
    for (int i = 0; i < tile.deraumere; i++)
        map[rand() % height][rand() % width]->deraumere += 1;
    for (int i = 0; i < tile.sibur; i++)
        map[rand() % height][rand() % width]->sibur += 1;
    for (int i = 0; i < tile.mendiane; i++)
        map[rand() % height][rand() % width]->mendiane += 1;
    for (int i = 0; i < tile.phiras; i++)
        map[rand() % height][rand() % width]->phiras += 1;
    for (int i = 0; i < tile.thystame; i++)
        map[rand() % height][rand() % width]->thystame += 1;
}

void process_refill_map(server_t *srv)
{
    if (srv->last_refill + MAP_REFFILL_RATE <= srv->ticks) {
        refill_map(srv->map, srv->settings);
        srv->last_refill += MAP_REFFILL_RATE;
    }
}
