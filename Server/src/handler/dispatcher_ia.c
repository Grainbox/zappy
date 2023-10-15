/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

static command_t commands[] = {
        {"Forward", ONE_STEP_CMD, 7, &forward},
        {"Right", ONE_STEP_CMD, 7, &right},
        {"Left", ONE_STEP_CMD, 7, &left},
        {"Look", ONE_STEP_CMD, 7, &look},
        {"Inventory", ONE_STEP_CMD, 1, &inventory},
        {"Broadcast", ONE_STEP_CMD, 7, &broadcast},
        {"Connect_nbr", ONE_STEP_CMD, 1, &connect_nbr},
        {"Fork", MULTIPLE_STEP_CMD, 42, &fork_ia},
        {"Eject", ONE_STEP_CMD, 7, &eject},
        {"Take", ONE_STEP_CMD, 7, &take_obj},
        {"Set", ONE_STEP_CMD, 7, &set_obj},
        {"Incantation", MULTIPLE_STEP_CMD, 300, &incantation},
        {"__ERROR__\n", ONE_STEP_CMD, 0, &request_error},
    };

int request_error(server_t *srv, client_t *cli, char **args)
{
    (void)srv;
    (void)args;
    (void)cli;

    return (-1);
}

int undefined(server_t *srv, client_t *cli, char **args)
{
    (void)srv;
    (void)args;

    dprintf(cli->fd, "ko undefined\n");
    return (0);
}

void manage_request(server_t *srv, client_t *cli, char **args, int cmd_index)
{
    command_t *cmd = &commands[cmd_index];

    add_request(cli, args, cmd, srv->ticks);
}

int dispatcher_ia(server_t *srv, client_t *cli, char *buff)
{
    int cmd_index = 0;
    char **args = split(buff, ' ');

    for (int i = 0; args && args[0] && commands[i].command != NULL; i++) {
        if (strcmp("__ERROR__\n", commands[i].command) == 0)
            break;
        if (strcmp(args[0], commands[i].command) == 0) {
            manage_request(srv, cli, args, i);
            return 0;
        }
        cmd_index++;
    }
    manage_request(srv, cli, args, cmd_index);
    return (0);
}
