/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>

char *append(char *str, const char *to_append)
{
    if (str == NULL) {
        str = malloc(sizeof(char) * (strlen(to_append) + 1));
        strcpy(str, to_append);
        return str;
    }

    size_t str_len = strlen(str);
    size_t append_len = strlen(to_append);
    char *new_str = realloc(str, str_len + append_len + 1);
    if (new_str == NULL) {
        free(str);
        return NULL;
    }
    strncat(new_str, to_append, append_len);
    return new_str;
}

void append_n_times(char **res, const char *str, int n)
{
    for (int i = 0; i < n; i++) {
        char *new_str = append(*res, str);
        if (new_str == NULL)
            return;
        *res = new_str;
    }
}
