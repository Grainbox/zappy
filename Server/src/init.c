/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>
#include <stdlib.h>

static void set_server_addr(server_t *srv, int port)
{
    srv->addr.sin_family = AF_INET;
    srv->addr.sin_addr.s_addr = INADDR_ANY;
    srv->addr.sin_port = htons(port);
}

static server_t *init_server(settings_t *settings)
{
    server_t *srv = calloc(1, sizeof(server_t));

    srv->settings = settings;
    get_server_ptr(srv);
    atexit((void (*)(void))destroy_server);
    if ((srv->sc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            exit(84);
    if (setsockopt(srv->sc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, 4UL) < 0)
        exit(84);
    set_server_addr(srv, settings->port);
    if (bind(srv->sc, (struct sockaddr *)&srv->addr, 16UL) < 0) {
        perror("bind failed");
        exit(84);
    }
    if (listen(srv->sc, 3) < 0)
        exit(84);
    srv->max_fd = srv->sc;
    return (srv);
}

server_t *get_server_ptr(server_t *ptr)
{
    static server_t *ret = NULL;

    if (ptr != NULL)
        ret = ptr;
    return ret;
}

int server(settings_t *settings)
{
    int error = 0;
    srand(time(NULL));
    server_t *srv = init_server(settings);
    srv->map = create_map(settings);
    srv->settings = settings;
    create_teams(srv);

    if (srv == NULL)
        return (84);

    if (srv == NULL)
        return (84);
    signal(SIGINT, handle_sigint);
    error += server_loop(srv);

    return (error);
}
