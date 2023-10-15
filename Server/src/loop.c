/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void update_fds(server_t *srv)
{
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    FD_ZERO(&srv->read_fds);
    FD_SET(srv->sc, &srv->read_fds);
    srv->max_fd = srv->sc;

    for (client_t *curr = srv->clients; curr != NULL; curr = curr->next) {
        FD_SET(curr->fd, &srv->read_fds);
        if (curr->fd > srv->max_fd)
            srv->max_fd = curr->fd;
    }

    if (select(srv->max_fd + 1, &srv->read_fds, NULL, NULL, &timeout) < 0)
        exit(84);
}

static size_t elapsed_time(struct timeval tv_start)
{
    struct timeval tv_end;

    gettimeofday(&tv_end, NULL);
    return (1000000 * tv_end.tv_sec + tv_end.tv_usec
        - (1000000 * tv_start.tv_sec + tv_start.tv_usec));
}

int server_loop(server_t *srv)
{
    struct timeval tv_start, tv_t;
    gettimeofday(&tv_start, NULL);
    gettimeofday(&tv_t, NULL);
    while (1) {
        update_fds(srv);
        size_t utv = elapsed_time(tv_start);
        if ((utv) < TICK_DURATION_MS * 1000) {
            usleep((TICK_DURATION_MS * 1000 - utv) / 4);
            continue;
        }
        srv->ticks = elapsed_time(tv_t) * srv->settings->freq / CLOCKS_PER_SEC;
        if (FD_ISSET(srv->sc, &srv->read_fds)) {
            handle_new_client(srv);
            update_fds(srv);
        }
        handle_clients(srv);
        process_tick(srv);
        gettimeofday(&tv_start, NULL);
    }
    return 0;
}
