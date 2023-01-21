/*
** EPITECH PROJECT, 2023
** stcp_hand_check.c
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

void stcp_hand_check(stcp_packet *packet)
{
    if (!stcp_datas->waiting_hand_check)
        return;
    if (stcp_datas->linked_puid == -1) {
        stcp_datas->linked_puid = *(int *) binary_to_str(packet->body);
        printf("Sync with puid : %d \n", stcp_datas->linked_puid);
    }
    stcp_datas->waiting_hand_check = false;
}

void stcp_send_hand_check()
{
    int own_pid = getpid();
    if (stcp_datas->linked_puid == -1)
        return;
    printf("Init hand check \n");
    stcp_packet *new_packet = stcp_create_packet(0, &own_pid, sizeof(int));
    stcp_send(stcp_datas->linked_puid, new_packet);
}
