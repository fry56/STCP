/*
** EPITECH PROJECT, 2023
** stcp_receive.c
** File description:
** desc
*/

#include <signal.h>
#include <stcp_functions.h>
#include <stcp_struct.h>
#include <stdlib.h>
#include <stdio.h>
#include <t_string.h>
#include <t_mem.h>

extern stcp *stcp_datas;

static const struct stcp_packet_type_t packet_type_datas[] = {
    {0, stcp_hand_check},
    {1, stcp_sync}
};

static void stcp_init_header()
{
    stcp_datas->packet->header
        = *(stcp_packet_header *)binary_to_str(stcp_datas->buffer);
    if (stcp_datas->packet->header.hash != PACKET_HASH) {
        printf("Corrupted packet drop. (HASH : %d)\n", stcp_datas->packet->header.hash);
        stcp_destroy_packet();
        stcp_datas->status = (stcp_datas->linked_puid != -1)
            ? STATUS_CONNECTED : STATUS_WAITING_CONNECTION;
    }
    printf("Valide Header. (HASH : %d)\n", stcp_datas->packet->header.hash);
}

static void stpc_init_packet()
{
    printf("-- NEW PACKET INIT -- \n");
    stcp_datas->packet = tcalloc(1, sizeof(stcp_packet));
    if (stcp_datas->packet == NULL)
        return;
    if ((stcp_datas->packet->body = tcalloc(1, 4048)) == NULL) {
        free(stcp_datas->packet);
        return;
    }
    stcp_datas->bits_received = 0;
    stcp_datas->time_out = TIME_OUT;
}

static void stcp_call_packet_function()
{
    packet_type_datas[(int)stcp_datas->packet->header.type]
        .type_function(stcp_datas->packet);
    stcp_destroy_packet();
}

static void stcp_check_packet()
{
    printf("--- Packet receive ---\n");
    printf("Type : %d \n", stcp_datas->packet->header.type);
    printf("Size : %d \n", stcp_datas->packet->header.size);

    if ((stcp_datas->linked_puid == -1
        && stcp_datas->status != STATUS_WAITING_CONNECTION)
        && stcp_datas->status != STATUS_WAITING_HAND_CHECK) {
        printf("Packet drop, Not linked.\n");
        stcp_destroy_packet();
        return;
    }
    stcp_datas->packet->body[stcp_datas->packet->header.size + 1] = '\0';
    stcp_call_packet_function();
}

void stcp_receive(int type)
{
    char bit = '0';
    if (stcp_datas->packet == NULL)
        stpc_init_packet();
    if (type == SIGUSR2)
        bit = '1';
    if (stcp_datas->bits_received < PACKET_SIZE)
        stcp_datas->buffer[stcp_datas->bits_received++] = bit;
    else
        stcp_datas->packet->body[(stcp_datas->bits_received++) - (PACKET_SIZE)] = bit;
    if (stcp_datas->bits_received == PACKET_SIZE)
        stcp_init_header();
    if (((stcp_datas->bits_received) - PACKET_SIZE) == (stcp_datas->packet->header.size))
        stcp_check_packet();
}
