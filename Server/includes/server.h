/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#pragma once

#include <arpa/inet.h>
#include <ia.h>
#include <math.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <utils.h>

// Server utils defines
#define BUFFER_SIZE 2048
#define TPS 120
#define TICK_DURATION_MS (1000 / TPS)
#define MAX_WAITING_REQUESTS 10
#define MAP_REFFILL_RATE 20
#define ONE_STEP_CMD false
#define MULTIPLE_STEP_CMD true

// Server default settings
#define PORT 4242
#define WIDTH 10
#define HEIGHT 10
#define USER_PER_TEAM 3
#define FREQ 100
#define TEAM1 "Team1"
#define TEAM2 "Team2"

// Server defines

#define MIN_WIDTH 10
#define MAX_WIDTH 30
#define MIN_HEIGHT 10
#define MAX_HEIGHT 30
#define MIN_USER_PER_TEAM 1
#define MIN_FREQ 2
#define MAX_FREQ 10000
#define PORT_MIN 0
#define PORT_MAX 65535

// Resources for incantation
typedef int resources_t[7];

// Client type
typedef enum client_type_e {
    IA,
    GUI,
    UNDEFINED
} client_type;

// Server settings
typedef struct settings_s {
    int width;
    int height;
    char **teams_name;
    int user_per_team;
    int freq;
    int port;
} settings_t;

// Server teams
typedef struct teams_s {
    int id;
    char *name;
    int nb_clients;
    int nb_eggs;
} teams_t;

// Team egg
typedef struct egg_s {
    int id;
    int team_id;
    position_t pos;
    bool laid;
    struct egg_s *next;
} egg_t;

// Server client
typedef struct client_s {
    client_type type;
    int team_id;
    int fd;
    char *buff;
    player_t *player;
    struct client_s *next;
} client_t;

// Map tile
typedef struct tile_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} tile_t;

// Object offset
typedef struct struct_map_s {
    char *key;
    size_t offset;
} struct_map_t;

// Server struct
typedef struct server_s {
    int port;
    int sc;
    struct sockaddr_in addr;
    int max_fd;
    fd_set read_fds;
    client_t *clients;
    teams_t **teams;
    settings_t *settings;
    tile_t ***map;
    size_t ticks;
    size_t last_refill;
    egg_t *eggs;
    int egg_id;
} server_t;

// Request struct
typedef struct command_s {
    const char *command;
    bool self_managed;
    size_t execution_time;
    int (*func)(server_t *, client_t *, char **);
} command_t;

// Look info struct
typedef struct look_info_s {
    position_t pos;
    direction_t dir;
    int curr_lvl;
    char *res;
} look_info_t;

// Vector struct for shortest path (toroidal map)
typedef struct vector_s {
    double x;
    double y;
} vector_t;

// Basic utils
int get_array_size(char **args);
position_t get_pos_in_map(server_t *srv, int x, int y);
char *append(char *str, const char *to_append);
void append_n_times(char **res, const char *str, int n);
int get_player_nb(server_t *srv, int x, int y);
bool is_num(char *str);
int *get_obj_key_ptr(tile_t *tile, char *obj_key);
size_t args_count(char **args);
bool client_is_online(server_t *srv, client_t *cli_ptr);

// Request functions typedef
typedef int (*request_func_t)(server_t *, client_t *, char **);

// Request utils functions
size_t waiting_requests_len(client_t *client);
bool add_request(client_t *client, char **args, command_t *cmd, size_t c_tick);
void remove_request(client_t *client, request_t *request);
void remove_all_requests(client_t *client);

// Teams utils
int get_available_slots(server_t *srv, int team_id);
int get_layed_egg(server_t *srv, int team_id);

// IA commands
int request_error(server_t *srv, client_t *cli, char **args);
int forward(server_t *srv, client_t *cli, char **args);
int right(server_t *srv, client_t *cli, char **args);
int left(server_t *srv, client_t *cli, char **args);
int inventory(server_t *srv, client_t *cli, char **args);
int look(server_t *srv, client_t *cli, char **args);
int connect_nbr(server_t *srv, client_t *cli, char **args);
int take_obj(server_t *srv, client_t *cli, char **args);
int set_obj(server_t *srv, client_t *cli, char **args);
int broadcast(server_t *srv, client_t *cli, char **args);
int fork_ia(server_t *srv, client_t *cli, char **args);
int eject(server_t *srv, client_t *cli, char **args);
int incantation(server_t *srv, client_t *cli, char **args);
// Incantation utils
client_t **get_clients_eligible(server_t *srv, client_t *leader);
int get_player_nb_at_lvl(server_t *srv, int x, int y, int lvl);
bool tile_has_resources(server_t *srv, position_t pos, int level);
bool tile_use_resources(server_t *srv, position_t pos, int lvl);
int nb_players_for_incantation(int lvl);
client_t **add_client(client_t **list, client_t *new, int *size);
int incantation_failed(server_t *server, client_t *client);

// Player utils
int player_eat(client_t *cli, server_t *srv);

// GUI commands
int get_map_size(server_t *srv, client_t *cli, char **args);
int content_of_tile(server_t *srv, client_t *cli, char **args);
int content_of_map(server_t *srv, client_t *cli, char **args);
void incorrect_parameter(client_t *cli);
int get_teams_name(server_t *srv, client_t *cli, char **args);
int new_player_connection(server_t *srv, client_t *cli);
int player_position(server_t *srv, client_t *cli, char **args);
int player_level(server_t *srv, client_t *cli, char **args);
int player_inventory(server_t *srv, client_t *cli, char **args);
int get_time_unit(server_t *srv, client_t *cli, char **args);
int gui_broadcast(server_t *srv, client_t *cli, char *message);
int gui_egg_laying(server_t *srv, client_t *cli);
int gui_resource_dropping(server_t *srv, client_t *cli, int nb_resource);
int gui_collect_resource(server_t *srv, client_t *cli, int nb_resource);
int set_time_unit(server_t *srv, client_t *cli, char **args);
int gui_egg_laid(server_t *srv, client_t *cli, int egg_id, position_t pos);
int gui_player_con_for_egg(server_t *srv, int egg_id);
int gui_egg_death(server_t *srv, int egg_id);
int gui_death_of_player(server_t *srv, client_t *cli);
int gui_end_of_game(server_t *srv, char *team_name);
int gui_message_from_server(server_t *srv, char *message);
void unknown_command(client_t *cli);
int gui_start_incant(server_t *srv, client_t *cli, int *other_ids);
int gui_end_incant(server_t *srv, position_t pos, int result);
int gui_expulsion(server_t *srv, client_t *cli);

// Handle SIGINT
void handle_sigint(int sig);

// Server functions
int server(settings_t *settings);
int server_loop(server_t *srv);
void handle_new_client(server_t *srv);
int handle_clients(server_t *srv);
int handle_request(server_t *srv, client_t *cli);
server_t *get_server_ptr(server_t *ptr);
void destroy_server(void);
void disconnect_client(client_t *cli, server_t *srv);


// TICK EVENTS
void process_tick(server_t *srv);
void process_refill_map(server_t *srv);
void process_waiting_requests(server_t *srv);
void process_player_death(server_t *srv);


// Dispatcher for requests
int dispatcher_ia(server_t *srv, client_t *cli, char *buff);
int dispatcher_gui(server_t *srv, client_t *cli, char *buff);
int undefined(server_t *srv, client_t *cli, char **args);

// Retrieve arguments
struct settings_s *get_settings(int argc, char **argv);
void set_freq(int *i, settings_t *settings, int argc, char **argv);
void set_client_nb(int *i, settings_t *settings, int argc, char **argv);
void set_height(int *i, settings_t *settings, int argc, char **argv);
void set_width(int *i, settings_t *settings, int argc, char **argv);
void set_port(int *i, settings_t *settings, int argc, char **argv);
void set_team(int *i, settings_t *settings, int argc, char **argv);

// Display help
void display_help(int exit_code);

// Map utils functions
void refill_map(tile_t ***map, settings_t *settings);
void move_direction(server_t *srv, client_t *cli, int x, int y);
vector_t shortest_torus_vector(position_t p1, position_t p2, vector_t max);
int vector_to_direction(vector_t v);
position_t random_pos(server_t *srv);
egg_t *create_egg(server_t *srv, client_t *cli);
int destroy_eggs(server_t *srv, int x, int y);

// Create content
tile_t ***create_map(settings_t *settings);
void create_teams(server_t *srv);

// Destroy content
void free_client(server_t *srv, client_t *cli);
