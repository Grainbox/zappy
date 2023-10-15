/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** get_settings
*/

#include <server.h>

/**
 * @brief List all the valid args
*/
const char *valid_args[] = {
    "-p",
    "-x",
    "-y",
    "-n",
    "-c",
    "-f",
    NULL
};

/**
 * @brief Check if an argument is valid
*/
static bool check_arg(int i, char **argv)
{
    bool valid = false;

    if (argv[i][0] != '-')
        return true;
    for (int j = 0; valid_args[j] != NULL; j++)
        if (strcmp(argv[i], valid_args[j]) == 0)
            valid = true;
    if (!valid)
        return false;
    return true;
}

/**
 * @brief Init the default values
*/
static settings_t *init_settings(void)
{
    settings_t *settings = malloc(sizeof(settings_t));

    settings->port = PORT;
    settings->width = WIDTH;
    settings->height = HEIGHT;
    settings->user_per_team = USER_PER_TEAM;
    settings->freq = FREQ;
    settings->teams_name = malloc(sizeof(char *) * 3);
    settings->teams_name[0] = malloc(sizeof(char) * (strlen(TEAM1) + 1));
    settings->teams_name[1] = malloc(sizeof(char) * (strlen(TEAM2) + 1));
    settings->teams_name[2] = NULL;
    strcpy(settings->teams_name[0], TEAM1);
    strcpy(settings->teams_name[1], TEAM2);
    return settings;
}

/**
 * @brief Check the params to add the values in the settings
*/
struct settings_s *get_settings(int argc, char **argv)
{
    settings_t *settings = init_settings();
    if (argc == 2 && strcmp(argv[1], "-help") == 0)
        display_help(0);
    for (int i = 0; i < argc; i++) {
        if (!check_arg(i, argv))
            display_help(84);
        if (argv[i][0] == '-' && strcmp(argv[i], "-p") == 0)
            set_port(&i, settings, argc, argv);
        if (argv[i][0] == '-' && strcmp(argv[i], "-x") == 0)
            set_width(&i, settings, argc, argv);
        if (argv[i][0] == '-' && strcmp(argv[i], "-y") == 0)
            set_height(&i, settings, argc, argv);
        if (argv[i][0] == '-' && strcmp(argv[i], "-n") == 0)
            set_team(&i, settings, argc, argv);
        if (argv[i][0] == '-' && strcmp(argv[i], "-c") == 0)
            set_client_nb(&i, settings, argc, argv);
        if (argv[i][0] == '-' && strcmp(argv[i], "-f") == 0)
            set_freq(&i, settings, argc, argv);
    }
    return settings;
}
