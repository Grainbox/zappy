##
## EPITECH PROJECT, 2023
## raytracer
## File description:
## Makefile for raytracer
##

.PHONY: all clean fclean re

all: zappy_gui zappy_ai zappy_server

zappy_gui:
	@echo "Compilation GUI"
	@$(MAKE) -C GUI

zappy_ai:
	@echo "Compilation IA"
	@$(MAKE) -C IA

zappy_server:
	@echo "Compilation server"
	@$(MAKE) -C Server

clean:
	@echo "Nettoyage des fichiers objets"
	@$(MAKE) -C GUI clean
	@$(MAKE) -C IA clean
	@$(MAKE) -C Server clean

fclean:
	@echo "Nettoyage complet"
	@$(MAKE) -C GUI fclean
	@$(MAKE) -C IA fclean
	@$(MAKE) -C Server fclean

re: fclean all
