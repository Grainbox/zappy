/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

/**
 * @brief Set the IA's default values
 * @param srv Server Object
 * @param cli Client Object
*/
static void setup_stats(server_t *srv, client_t *cli)
{
    cli->player = calloc(1, sizeof(player_t));
    cli->player->inventory = calloc(1, sizeof(tile_t));
    cli->player->inventory->food = 10;
    cli->player->dir = rand() % 4;
    cli->player->level = 1;
    cli->player->pos.x = rand() % srv->settings->width;
    cli->player->pos.y = rand() % srv->settings->height;
    cli->player->requests = NULL;
    cli->player->last_action = srv->ticks;
    player_eat(cli, srv);
}

/**
 * @brief Set the client type to IA and assign default values
 * @param srv Server Object
 * @param cli Client Object
 * @param buff Command Sent
*/
static int setup_ia(server_t *srv, client_t *cli, char *buff)
{
    int team_id = -1;
    for (int i = 0; srv->settings->teams_name[i] != NULL; i++) {
        if (strcmp(buff, srv->settings->teams_name[i]) == 0)
            team_id = i;
    }
    if (team_id == -1)
        return -1;
    int slots_remaining = get_available_slots(srv, team_id);
    if (slots_remaining < 0)
        return -1;
    else {
        cli->type = IA;
        cli->team_id = team_id;
        dprintf(cli->fd, "%d\n", slots_remaining);
        dprintf(cli->fd, "%d %d\n", srv->settings->width,
            srv->settings->height);
        setup_stats(srv, cli);
        new_player_connection(srv, cli);
    }
    return 0;
}

/**
 * @brief Assign a type to an Undefined client
 * @param srv Serer Object
 * @param cli Client Object
 * @param buff Command sent
*/
static void set_type(server_t *srv, client_t *cli, char *buff)
{
    if (strcmp(buff, "GRAPHIC") == 0) {
        char **args = split(buff, ' ');
        cli->type = GUI;
        get_map_size(srv, cli, args);
        get_time_unit(srv, cli, args);
        content_of_map(srv, cli, args);
        get_teams_name(srv, cli, args);
    } else {
        if (setup_ia(srv, cli, buff) == -1)
            dprintf(cli->fd, "ko\n");
    }
}

/**
 * @brief Route the command to the correspondant factory
 * @param srv Server Object
 * @param cli Client Object
 * @param buff Command Sent
*/
int handle_request(server_t *srv, client_t *cli)
{
    char *ptr = strchr(cli->buff, '\n');
    if (ptr != NULL)
        *ptr = '\0';
    else
        return 0;
    if (cli->type == IA)
        dispatcher_ia(srv, cli, cli->buff);
    else if (cli->type == GUI)
        dispatcher_gui(srv, cli, cli->buff);
    else
        set_type(srv, cli, cli->buff);
    memmove(cli->buff, ptr + 1, strlen(ptr + 1) + 1);
    return 0;
}
