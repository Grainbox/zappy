##
## EPITECH PROJECT, 2023
## zappy_server
## File description:
## Makefile for zappy_server
##

NAME 		=  	zappy_server

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	COMPILER 	= 	clang -std=c++17
else ifeq ($(UNAME_S),Linux)
    COMPILER	=	gcc
else
    $(error "Système d'exploitation non supporté")
endif

SRC 		=	src/main.c										\
				src/utils/split.c								\
				src/utils/movement.c							\
				src/utils/free_args.c							\
				src/utils/pos_map.c								\
				src/utils/append.c								\
				src/utils/get_player_nb_at.c					\
				src/utils/is_num.c								\
				src/utils/args_count.c							\
				src/utils/toroidal_short_path.c					\
				src/utils/random_pos.c							\
				src/utils/client_is_online.c					\
				src/init.c										\
				src/destroy.c									\
				src/loop.c										\
				src/process_tick.c								\
				src/player_eat.c								\
				src/object.c									\
				src/free_client.c								\
				src/disconnect.c								\
				src/available_slots.c							\
				src/egg.c										\
				src/handler/request.c							\
				src/handler/handle_client.c						\
				src/handler/dispatcher_gui.c					\
				src/handler/dispatcher_ia.c						\
				src/handler/cmds_ia/wait_request.c				\
				src/handler/process_requests.c					\
				src/handler/cmds_ia/forward.c					\
				src/handler/cmds_ia/right.c						\
				src/handler/cmds_ia/left.c						\
				src/handler/cmds_ia/inventory.c					\
				src/handler/cmds_ia/look.c						\
				src/handler/cmds_ia/connect_nbr.c				\
				src/handler/cmds_ia/take.c						\
				src/handler/cmds_ia/set.c						\
				src/handler/cmds_ia/broadcast.c					\
				src/handler/cmds_ia/fork.c						\
				src/handler/cmds_ia/eject.c						\
				src/handler/cmds_ia/incantation/add_client.c	\
				src/handler/cmds_ia/incantation/get_player_nb_at_lvl.c	\
				src/handler/cmds_ia/incantation/get_players.c	\
				src/handler/cmds_ia/incantation/has_resources.c	\
				src/handler/cmds_ia/incantation/incantation.c	\
				src/handler/cmds_ia/incantation/failed.c		\
				src/args_process/get_settings.c					\
				src/args_process/set_numbers_params.c			\
				src/args_process/set_team.c						\
				src/display_help.c								\
				src/refill_map.c								\
       			src/create_content.c							\
				src/handler/cmds_gui/map.c						\
				src/handler/cmds_gui/error_command.c			\
				src/handler/cmds_gui/team_names.c				\
				src/utils/get_array_size.c						\
				src/handler/cmds_gui/player_info.c				\
				src/handler/cmds_gui/time_unit.c				\
				src/handler/cmds_gui/broadcast.c				\
				src/handler/cmds_gui/egg.c						\
				src/handler/cmds_gui/resource.c					\
				src/handler/cmds_gui/incantation.c				\
				src/handler/cmds_gui/player_event.c				\
				src/handler/cmds_gui/end_of_game.c				\
				src/handler/cmds_gui/expulsion.c				\

OBJ			=	$(SRC:.c=.o)

INCLUDE		=	-I ./includes/

CXX_FLAGS 	= 	-Wall -Wextra -std=c17

LDFLAGS		=	-lm

all:		$(NAME)

CLEAN_TEXT:
		@printf "$(PBOLD) $(PBLUEC) CLEANING 🧹\n"

COMPLETE_TEXT:
		@printf "$(PBOLD) $(PGREEN) BUILD COMPLETED 🏗️\n"


DEBUG_TEXT:
		@printf "$(PBOLD) $(PORANGE) DEBUG MODE ⚠\n"

%.o: %.c
			$(eval counter=$(shell echo $$(($(counter)+1))))
			$(eval percentage=$(shell echo $$((($(counter) * 100) /\
			$(TOTAL_FILES)))))
			@printf "$(PYELLOW)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)" "\
$(subst $(shell pwd)/,,$<)"
			@$(COMPILER) $(INCLUDE) -c $(CXX_FLAGS) $< -o $@
			@printf "\r$(PGREEN)$(PBOLD)↦🔹[%s] ($(percentage)%%)$(PRESET)\n" "\
$(subst $(shell pwd)/,,$<)"

$(NAME): 	$(OBJ)
			@$(COMPILER) $(INCLUDE) -o $(NAME) $(OBJ) $(CXX_FLAGS) $(LDFLAGS)
			@make COMPLETE_TEXT


clean:
			@make CLEAN_TEXT
			@rm -f $(OBJ)

fclean:		clean
			@rm -f $(NAME)

re:			fclean	all

debug:		CXX_FLAGS += -g
debug:		re
			@printf "$(PYELLOW)$(PBOLD) ⚠ Debug mode ON$(PRESET)\n"
			@printf "\033[1m\033[37mflags: $(CXX_FLAGS)\033[0m\n\n"

.SILENT: CLEAN_TEXT COMPLETE_TEXT BUILD_FAIL
.PHONY: all clean fclean re debug

# Counters
TOTAL_FILES	= $(words $(SRC))
counter		= 0

# Color definitions
PGREEN	= \033[32m
PRED	= \033[31m
PORANGE	= \033[38;5;208m
PYELLOW	= \033[33m
PBLUE	= \033[34m
PBLUEC	= \033[36m
PRESET	= \033[0m
PBOLD	= \033[1m
