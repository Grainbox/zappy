/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

char *look_at(server_t *srv, int x, int y)
{
    char *res = NULL;
    tile_t *t = srv->map[y][x];
    append_n_times(&res, " player", get_player_nb(srv, x, y));
    append_n_times(&res, " deraumere", t->deraumere);
    append_n_times(&res, " linemate", t->linemate);
    append_n_times(&res, " mendiane", t->mendiane);
    append_n_times(&res, " phiras", t->phiras);
    append_n_times(&res, " sibur", t->sibur);
    append_n_times(&res, " thystame", t->thystame);
    append_n_times(&res, " food", t->food);
    append_n_times(&res, ",", 1);
    return res;
}

position_t handle_up_down(server_t *srv, look_info_t *info)
{
    int dist_y = info->curr_lvl + 1;
    int dist_x = -dist_y;
    position_t cpos;
    while (dist_x <= dist_y) {
        cpos.x = info->pos.x + dist_x;
        cpos.y = info->pos.y + (info->dir != DOWN ? -dist_y : dist_y);
        cpos = get_pos_in_map(srv, cpos.x, cpos.y);
        char *tmp = look_at(srv, cpos.x, cpos.y);
        info->res = append(info->res, tmp);
        free(tmp);
        dist_x++;
    }
    return cpos;
}

position_t handle_left_right(server_t *srv, look_info_t *info)
{
    int dist_x = info->curr_lvl + 1;
    int dist_y = -dist_x;
    position_t cpos;
    while (dist_y <= dist_x) {
        cpos.x = info->pos.x + (info->dir == LEFT ? -dist_x : dist_x);
        cpos.y = info->pos.y + dist_y;
        cpos = get_pos_in_map(srv, cpos.x, cpos.y);
        char *tmp = look_at(srv, cpos.x, cpos.y);
        info->res = append(info->res, tmp);
        free(tmp);
        dist_y++;
    }
    return cpos;
}

int look(server_t *srv, client_t *cli, char **args)
{
    (void)args;
    const direction_t dir = cli->player->dir;
    const position_t pos = cli->player->pos;
    look_info_t info = { .dir = dir, .pos = pos, .curr_lvl = 0, .res = NULL };
    int level = cli->player->level;
    info.curr_lvl = cli->player->level;
    char *tmp = look_at(srv, pos.x, pos.y);
    info.res = append(NULL, tmp);
    free(tmp);
    for (int i = 0; i < level; i++) {
        info.curr_lvl = i;
        if (dir == UP || dir == DOWN) {
            handle_up_down(srv, &info);
        } else {
            handle_left_right(srv, &info);
        }
    }
    dprintf(cli->fd, "[%s ]\n", info.res);
    free(info.res);
    return 0;
}
