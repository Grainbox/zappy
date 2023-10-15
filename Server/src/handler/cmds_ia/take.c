/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void inventory_add_obj(player_t *player, char *obj_key)
{
    int *obj_count_ptr = get_obj_key_ptr(player->inventory, obj_key);
    if (obj_count_ptr == NULL) {
        return;
    }
    *obj_count_ptr += 1;
}

int take_obj(server_t *srv, client_t *cli, char **args)
{
    tile_t *tile = srv->map[cli->player->pos.y][cli->player->pos.x];

    if (args_count(args) != 2) {
        return (-1);
    }
    char *obj_key = args[1];
    int *obj_count_ptr = get_obj_key_ptr(tile, obj_key);
    if (obj_count_ptr == NULL || *obj_count_ptr == 0) {
        return (-1);
    }
    *obj_count_ptr -= 1;
    inventory_add_obj(cli->player, obj_key);
    dprintf(cli->fd, "ok\n");
    return (0);
}
