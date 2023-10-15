/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

void handle_sigint(int sig)
{
    (void)sig;
    printf("(CTRL-C) stopping server\n");
    exit(0);
}

int main (int argc, char **argv)
{
    settings_t *settings = get_settings(argc, argv);

    return (server(settings));
}
