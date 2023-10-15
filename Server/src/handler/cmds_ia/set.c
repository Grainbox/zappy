/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

int inventory_remove_obj(player_t *player, char *obj_key)
{
    int *obj_count_ptr = get_obj_key_ptr(player->inventory, obj_key);
    if (obj_count_ptr == NULL) {
        return (-1);
    }
    if (*obj_count_ptr == 0) {
        return (-1);
    }
    *obj_count_ptr -= 1;
    return (0);
}

int set_obj(server_t *srv, client_t *cli, char **args)
{
    tile_t *tile = srv->map[cli->player->pos.y][cli->player->pos.x];

    if (args_count(args) != 2) {
        return (-1);
    }
    char *obj_key = args[1];
    int *obj_count_ptr = get_obj_key_ptr(tile, obj_key);
    if (obj_count_ptr == NULL) {
        return (-1);
    }
    if (inventory_remove_obj(cli->player, obj_key) == -1) {
        return (-1);
    }
    dprintf(cli->fd, "ok\n");
    *obj_count_ptr += 1;
    return (0);
}
