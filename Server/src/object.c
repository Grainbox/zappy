/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

static struct_map_t object[] = {
        {"food", offsetof(tile_t, food)},
        {"linemate", offsetof(tile_t, linemate)},
        {"deraumere", offsetof(tile_t, deraumere)},
        {"sibur", offsetof(tile_t, sibur)},
        {"mendiane", offsetof(tile_t, mendiane)},
        {"phiras", offsetof(tile_t, phiras)},
        {"thystame", offsetof(tile_t, thystame)},
        {NULL, sizeof(tile_t) + 1}
    };

int *get_obj_key_ptr(tile_t *tile, char *obj_key)
{
    size_t offset = 0;
    for (int i = 0; object[i].key != NULL; i++) {
        if (strcmp(object[i].key, obj_key) == 0) {
            offset = object[i].offset;
            break;
        }
    }

    if (offset == sizeof(tile_t) + 1) {
        return NULL;
    }
    int *obj_count_ptr = (int *)((char *)tile + offset);
    return obj_count_ptr;
}
