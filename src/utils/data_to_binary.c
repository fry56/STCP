/*
** EPITECH PROJECT, 2023
** data_to_binary.c
** File description:
** desc
*/

#include <t_string.h>
#include <t_math.h>

char *data_to_binary(void *data, tsize_t size)
{
    char *value = "";
    u8 *temp = (u8 *)data;
    while (size) {
        value = tstr_concat(value, int_to_base(*temp++, 2, 8));
        size--;
    }
    return value;
}
