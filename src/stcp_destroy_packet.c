/*
** EPITECH PROJECT, 2023
** stcp_destroy_packet.c
** File description:
** desc
*/

#include <stcp_functions.h>
#include <stcp_struct.h>
#include <stdlib.h>
#include <stdio.h>

stcp *stcp_datas;

void stcp_destroy_packet()
{
    if (stcp_datas->packet == NULL)
        return;
    free(stcp_datas->packet->body);
    free(stcp_datas->packet);
}
