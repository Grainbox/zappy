/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

vector_t shortest_torus_vector(position_t p1, position_t p2, vector_t max)
{
    vector_t v;
    v.x = p2.x - p1.x;
    v.y = p2.y - p1.y;

    if (fabs(v.x) > max.x / 2) {
        v.x = v.x > 0 ? v.x - max.x : v.x + max.x;
    }

    if (fabs(v.y) > max.y / 2) {
        v.y = v.y > 0 ? v.y - max.y : v.y + max.y;
    }
    if (v.x != 0)
        v.x /= fabs(v.x);
    if (v.y != 0)
        v.y /= fabs(v.y);

    return v;
}

int vector_to_direction(vector_t vf)
{
    int x = (int)ceil(vf.x), y = (int)ceil(vf.y);
    if (x == 0 && y == 0)
        return 0;
    if (x == 0 && y == 1)
        return 1;
    if (x == 1 && y == 1)
        return 2;
    if (x == 1 && y == 0)
        return 3;
    if (x == 1 && y == -1)
        return 4;
    if (x == 0 && y == -1)
        return 5;
    if (x == -1 && y == -1)
        return 6;
    if (x == -1 && y == 0)
        return 7;
    if (x == -1 && y == 1)
        return 8;
    return 0;
}
