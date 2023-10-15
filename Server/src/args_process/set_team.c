/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** set_team
*/

#include "server.h"

/**
 * @brief Get the number of team to be added
*/
static int team_nb(int argc, char **argv, int i)
{
    int count = 0;

    for (; i != argc; i++) {
        if (argv[i][0] == '-')
            break;
        count++;
    }
    if ((count + 1) <= 2)
        count++;
    return count + 1;
}

/**
 * @brief Check if a team name appears multiple times
 * @param settings setting object
 * @param k team index 1
 * @param j team index 2
*/
static void multiple_team(settings_t *settings, int k, int j)
{
    if (j != k && strcmp(settings->teams_name[j],
        settings->teams_name[k]) == 0) {
        fprintf(stderr, "Team name must be unique\n");
        exit(84);
    }
}

/**
 * @brief set the teams in the settings
 * @param i The current argument
 * @param settings The setting object
*/
void set_team(int *i, settings_t *settings, int argc, char **argv)
{
    if (*i + 1 >= argc)
        display_help(84);
    *i += 1;
    settings->teams_name = realloc(settings->teams_name, sizeof(char *) *
        team_nb(argc, argv, *i));
    for (int j = 0; *i != argc; j++, *i += 1) {
        settings->teams_name[j] = realloc(settings->teams_name[j],
            sizeof(char) * (strlen(argv[*i]) + 1));
        strcpy(settings->teams_name[j], argv[*i]);
        if (*i + 1 != argc && argv[*i + 1][0] == '-')
            break;
    }
    for (int j = 0; settings->teams_name[j] != NULL; j++)
        for (int k = 0; settings->teams_name[k] != NULL; k++)
            multiple_team(settings, k, j);
    *i -= 1;
}
