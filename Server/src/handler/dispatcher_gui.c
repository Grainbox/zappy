/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

/**
 * @brief List of functions corresponding to command
*/
static request_func_t commands[] = {
        &get_map_size,
        &content_of_tile,
        &content_of_map,
        &get_teams_name,
        &player_position,
        &player_level,
        &player_inventory,
        &get_time_unit,
        &set_time_unit,
        NULL
    };

/**
 * @brief List of commands names
*/
static char *names[] = {
        "msz",
        "bct",
        "mct",
        "tna",
        "ppo",
        "plv",
        "pin",
        "sgt",
        "sst",
        NULL
    };

/**
 * @brief Removes the '\n'
 * @param args The command as char **
*/
static void remove_useless_char(char **args)
{
    for (int i = 0; args[i] != NULL; i++) {
        int len = strlen(args[i]);
        if (len - 1 > 0 && args[i][len - 1] == '\n')
            args[i][len - 1] = '\0';
    }
}

/**
 * @brief Send the command to the according process
 * @param srv Server Object
 * @param cli Client Object
 * @param args The command sent as char **
*/
int dispatcher_gui(server_t *srv, client_t *cli, char *buff)
{
    int error = 0;
    char **args = split(buff, ' ');
    remove_useless_char(args);

    for (int i = 0; args && args[0] && names[i] != NULL; i++) {
        if (strcmp(args[0], names[i]) == 0) {
            error = commands[i](srv, cli, args);
            return error;
        }
    }
    unknown_command(cli);
    free(buff);
    return 0;
}
