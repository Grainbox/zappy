/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>
#include <string.h>

int count_words(char *str, char delim)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] == delim)
            count++;
        i++;
    }
    return count + 1;
}

char **split(char *str, char delim)
{
    char delimiter[2] = {delim, '\0'};
    char **tab = malloc(sizeof(char *) * (count_words(str, delim) + 1));
    char *token = strtok(str, delimiter);
    int i = 0;

    while (token != NULL) {
        tab[i] = token;
        if (tab[i][strlen(tab[i]) - 1] == '\n')
            tab[i][strlen(tab[i]) - 1] = '\0';
        token = strtok(NULL, delimiter);
        i++;
    }
    tab[i] = NULL;
    return tab;
}
