/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void free_clients(void)
{
    client_t *tmp = get_server_ptr(NULL)->clients;
    int count = 0;
    if (tmp == NULL) {
        printf("0 clients to free\n");
        return;
    }
    while (tmp) {
        client_t *next = tmp->next;
        close(tmp->fd);
        free_client(get_server_ptr(NULL), tmp);
        tmp = next;
        count++;
    }
    printf("%d clients freed\n", count);
}

static void free_map(server_t *srv)
{
    if (!srv->map)
        return;
    int width = srv->settings->width;
    int height = srv->settings->height;

    for (int i = 0; i < height && srv->map[i]; i++) {
        for (int j = 0; j < width && srv->map[i][j]; j++)
            free(srv->map[i][j]);
        free(srv->map[i]);
    }
    free(srv->map);
    printf("Map freed\n");
}

static void free_teams(server_t *srv)
{
    if (!srv->teams)
        return;
    for (int i = 0; srv->teams[i] != NULL; i++)
        free(srv->teams[i]);
    for (int i = 0; srv->settings->teams_name[i] != NULL; i++)
        free(srv->settings->teams_name[i]);
    free(srv->teams);
    free(srv->settings->teams_name);
    printf("Teams freed\n");
}

void destroy_server(void)
{
    server_t *srv = get_server_ptr(NULL);
    if (srv == NULL)
        return;
    free_clients();
    if (!srv->settings && !srv->settings->teams_name) {
        for (int i = 0; srv->settings->teams_name[i] && i < 1; i++)
            free(srv->settings->teams_name[i]);
        free(srv->settings->teams_name);
    }
    free_map(srv);
    free_teams(srv);
    close(srv->sc);
    if (srv->settings)
        free(srv->settings);
    free(srv);
    printf("Server freed\n");
    printf("Memory freed\n");
}
