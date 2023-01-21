/*
** EPITECH PROJECT, 2023
** stcp_time_out.c
** File description:
** desc
*/

#include <stcp_struct.h>

extern stcp *stcp_datas;

bool stcp_time_out()
{
    if (stcp_datas->time_out == 0) {
        stcp_datas->linked_puid = -1;
        stcp_datas->status = STATUS_WAITING_CONNECTION;
        stcp_datas->time_out = TIME_OUT;
        //printf("Connexion time out ! \n");
    }
}
