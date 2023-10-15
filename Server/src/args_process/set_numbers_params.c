/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** set_numbers_params
*/

#include "server.h"

/**
 * @brief set the port of the server in the settings
*/
void set_port(int *i, settings_t *settings, int argc, char **argv)
{
    if (*i + 1 == argc)
        display_help(84);
    *i += 1;
    if (!is_num(argv[*i])) {
        fprintf(stderr, "The port must be a valid positive number.\n");
        exit(84);
    }
    if (argv[*i][0] == '0') {
        fprintf(stderr, "The port cannot start with '0'\n");
        exit(84);
    }
    if (*i + 1 != argc && argv[*i + 1][0] != '-') {
        fprintf(stderr, "The port must be a unique value\n");
        exit(84);
    }
    settings->port = atoi(argv[*i]);
    if (settings->port < PORT_MIN || settings->port > PORT_MAX) {
        fprintf(stderr, "The port must be between 0 and 65535\n");
        exit(84);
    }
}

/**
 * @brief set the width of the map in the settings
*/
void set_width(int *i, settings_t *settings, int argc, char **argv)
{
    if (*i + 1 == argc)
        display_help(84);
    *i += 1;
    if (!is_num(argv[*i])) {
        fprintf(stderr, "The width must be a valid positive number.\n");
        exit(84);
    }
    if (argv[*i][0] == '0') {
        fprintf(stderr, "The width cannot start with '0'\n");
        exit(84);
    }
    if (*i + 1 != argc && argv[*i + 1][0] != '-') {
        fprintf(stderr, "The width must be a unique value\n");
        exit(84);
    }
    settings->width = atoi(argv[*i]);
    if (settings->width < MIN_WIDTH || settings->width > MAX_WIDTH) {
        fprintf(stderr, "The width must be between 10 and 30\n");
        exit(84);
    }
}

/**
 * @brief set the height of the map in the settings
*/
void set_height(int *i, settings_t *settings, int argc, char **argv)
{
    if (*i + 1 == argc)
        display_help(84);
    *i += 1;
    if (!is_num(argv[*i])) {
        fprintf(stderr, "The height must be a valid positive number.\n");
        exit(84);
    }
    if (argv[*i][0] == '0') {
        fprintf(stderr, "The height cannot start with '0'\n");
        exit(84);
    }
    if (*i + 1 != argc && argv[*i + 1][0] != '-') {
        fprintf(stderr, "The height must be a unique value\n");
        exit(84);
    }
    settings->height = atoi(argv[*i]);
    if (settings->height < MIN_HEIGHT || settings->height > MAX_HEIGHT) {
        fprintf(stderr, "The height must be between 10 and 30\n");
        exit(84);
    }
}

/**
 * @brief set the client nb per team in the settings
*/
void set_client_nb(int *i, settings_t *settings, int argc, char **argv)
{
    if (*i + 1 == argc)
        display_help(84);
    *i += 1;
    if (!is_num(argv[*i])) {
        fprintf(stderr, "The client number per team must > 1.\n");
        exit(84);
    }
    if (*i + 1 != argc && argv[*i + 1][0] != '-') {
        fprintf(stderr, "The height must be a unique value\n");
        exit(84);
    }
    settings->user_per_team = atoi(argv[*i]);
    if (settings->user_per_team < MIN_USER_PER_TEAM) {
        fprintf(stderr, "The client number per team must be at least 1\n");
        exit(84);
    }
}

/**
 * @brief set the frequence in the settings
*/
void set_freq(int *i, settings_t *settings, int argc, char **argv)
{
    int j = 0;
    if (*i + 1 == argc)
        display_help(84);
    *i += 1;
    if (argv[*i][j] == '-')
        j++;
    if (!is_num(argv[*i] + j)) {
        fprintf(stderr, "The frequence must be a valid positive number.\n");
        exit(84);
    }
    if (*i + 1 != argc && argv[*i + 1][0] != '-') {
        fprintf(stderr, "The height must be a unique value\n");
        exit(84);
    }
    settings->freq = atoi(argv[*i]);
    if (settings->freq < MIN_FREQ || settings->freq > MAX_FREQ) {
        fprintf(stderr, "The frequence must be between 2 and 10000\n");
        exit(84);
    }
}
