/*
** EPITECH PROJECT, 2023
** stcp_packet_drop.c
** File description:
** desc
*/

#include <stcp_struct.h>
#include <stcp_functions.h>
#include <t_mem.h>

extern stcp *stcp_datas;

bool stcp_packet_drop()
{
    if (stcp_datas->temp_received == NULL)
        return false;
    stcp_destroy_packet(stcp_datas->temp_received);
    stcp_datas->temp_received = NULL;
    stcp_datas->bits_received = 0;
    stcp_datas->datas_entering = false;
    tmemset(stcp_datas->buffer, 1, 4048);
    return true;
}
