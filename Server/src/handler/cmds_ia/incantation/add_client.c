/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** B-YEP-400-REN-4-1-zappy
*/

#include <server.h>


/**
 * @brief Add a client to the list
 *
 * @param list (list of clients)
 * @param new (client to add)
 * @return new list of clients
 */
client_t **add_client(client_t **list, client_t *new, int *size)
{
    if (!list) {
        list = calloc(2, sizeof(client_t *));
        if (!list)
            return NULL;
        list[0] = new, list[1] = NULL;
        *size = 1;
        return list;
    }
    client_t **temp = realloc(list, (*size + 2) * sizeof(client_t *));
    if (!temp)
        return list;
    list = temp;
    list[*size] = new, list[*size + 1] = NULL;
    (*size)++;
    return list;
}
