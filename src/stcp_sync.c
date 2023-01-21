/*
** EPITECH PROJECT, 2023
** stcp_sync.c
** File description:
** desc
*/

#include <stcp_packet_type.h>
#include <stcp_functions.h>
#include <stdio.h>
#include <t_string.h>
#include <t_math.h>
#include <unistd.h>

extern stcp *stcp_datas;

void stcp_sync(stcp_packet *packet)
{
    if (stcp_datas->linked_puid != -1)
        return;
    stcp_datas->linked_puid = *(int *)binary_to_str(packet->body);
    printf("Sync with puid : %d \n", stcp_datas->linked_puid);
    stcp_send_hand_check();
}

void stcp_send_sync(int pid)
{
    int own_pid = getpid();
    if (stcp_datas->linked_puid != -1)
        return;
    stcp_packet *new_packet = stcp_create_packet(1, &own_pid, sizeof(int));
    stcp_send(pid, new_packet);
}
