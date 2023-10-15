/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-mathieu.rio
** File description:
** set_numbers_params
*/

#include <stdbool.h>

bool is_num(char *str)
{
    for (int j = 0; str[j] != '\0'; j++)
        if (str[j] < '0' || str[j] > '9')
            return false;
    return true;
}
