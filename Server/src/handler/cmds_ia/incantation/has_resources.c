/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

/**
 * @brief Define the resources needed for the incantation
 * 1st index: number of players required
 * 2nd index: number of linemate required
 * 3rd index: number of deraumere required
 * 4th index: number of sibur required
 * 5th index: number of mendiane required
 * 6th index: number of phiras required
 * 7th index: number of thystame required
 */
static resources_t resources[] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 2, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1},
};

/**
 * @brief Check if the tile has the resources needed for the incantation
 *
 * @param server
 * @param pos (position of the elevation)
 * @param lvl (current player lvl)
 * @return true (if the tile has the resources else false)
 */
bool tile_has_resources(server_t *srv, position_t pos, int lvl)
{
    tile_t *tile = srv->map[pos.y][pos.x];

    if (!tile || lvl < 1 || lvl > 7)
        return (false);
    if (tile->linemate < resources[lvl - 1][1])
        return (false);
    if (tile->deraumere < resources[lvl - 1][2])
        return (false);
    if (tile->sibur < resources[lvl - 1][3])
        return (false);
    if (tile->mendiane < resources[lvl - 1][4])
        return (false);
    if (tile->phiras < resources[lvl - 1][5])
        return (false);
    if (tile->thystame < resources[lvl - 1][6])
        return (false);
    return (true);
}

bool tile_use_resources(server_t *srv, position_t pos, int lvl)
{
    tile_t *tile = srv->map[pos.y][pos.x];

    if (tile_has_resources(srv, pos, lvl) == false)
        return (false);
    tile->linemate -= resources[lvl - 1][1];
    tile->deraumere -= resources[lvl - 1][2];
    tile->sibur -= resources[lvl - 1][3];
    tile->mendiane -= resources[lvl - 1][4];
    tile->phiras -= resources[lvl - 1][5];
    tile->thystame -= resources[lvl - 1][6];
    return (true);
}

/**
 * @brief Get the number of players required for the incantation
 * (based on the current level)
 * @param lvl (current player lvl)
 * @return int (number of players required for the incantation)
 */
int nb_players_for_incantation(int lvl)
{
    if (lvl < 1 || lvl > 7)
        return (-1);
    return (resources[lvl - 1][0]);
}
