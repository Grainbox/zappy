/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#pragma once

#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct client_s client_t;
typedef struct server_s server_t;
typedef struct request_s request_t;
typedef struct tile_s tile_t;

// IA waiting requests
typedef struct request_s {
    char **args;
    size_t trigger_ticks;
    int (*func)(server_t *, client_t *, char **);
    size_t curr_step;
    bool self_managed;
    void *data;
    struct request_s *next;
} request_t;

// IA direction
typedef enum direction_e {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
} direction_t;

// IA reverse direction
typedef enum reverse_direction_e {
    REVERSE_UP = 2,
    REVERSE_RIGHT = 3,
    REVERSE_DOWN = 0,
    REVERSE_LEFT = 1
} reverse_direction_t;


// IA player struct
typedef struct player_s {
    size_t last_action;
    request_t *requests;
    tile_t *inventory;
    position_t pos;
    direction_t dir;
    int level;
    bool incantation;
    size_t dead_ticks;
} player_t;
