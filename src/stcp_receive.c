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

static bool stcp_init_header()
{
    stcp_datas->temp_received->header
        = *(stcp_packet_header *)binary_to_str(stcp_datas->buffer);
    if (stcp_datas->temp_received->header.hash != PACKET_HASH) {
        printf("Corrupted packet drop. (HASH : %d)\n", stcp_datas->temp_received->header.hash);
        stcp_packet_drop();
        return false;
    }
    printf("Valide Header. (HASH : %d)\n", stcp_datas->temp_received->header.hash);
    return true;
}

static bool stpc_init_packet()
{
    printf("-- NEW PACKET INIT -- \n");
    stcp_datas->temp_received = tcalloc(1, sizeof(stcp_packet));
    if (stcp_datas->temp_received == NULL)
        return false;
    if ((stcp_datas->temp_received->body = tcalloc(1, 4048)) == NULL) {
        stcp_packet_drop();
        return false;
    }
    stcp_datas->bits_received = 0;
    stcp_datas->time_out = TIME_OUT;
    stcp_datas->datas_entering = true;
    return true;
}

static void stcp_call_packet_function()
{
    packet_type_datas[(int)stcp_datas->temp_received->header.type]
        .type_function(stcp_datas->temp_received);
    stcp_destroy_packet(stcp_datas->temp_received);
}

static bool stcp_check_packet()
{
    printf("--- Packet receive ---\n");
    printf("Type : %d \n", stcp_datas->temp_received->header.type);
    printf("Size : %d \n", stcp_datas->temp_received->header.size);

    if ((stcp_datas->linked_puid == -1
        && stcp_datas->status != STATUS_WAITING_CONNECTION)
        && stcp_datas->status != STATUS_WAITING_HAND_CHECK) {
        printf("Packet drop, Not linked.\n");
        stcp_destroy_packet(stcp_datas->temp_received);
        stcp_datas->temp_received = NULL;
        return false;
    }
    stcp_datas->temp_received->body[stcp_datas->temp_received->header.size + 1] = '\0';
    //stcp_call_packet_function();
    stcp_destroy_packet(stcp_datas->temp_received);
    stcp_datas->temp_received = NULL;
    printf("Packet drop\n");
    stcp_datas->datas_entering = false;
    return true;
}

void stcp_receive(int type)
{
    char bit = '0';
    if (stcp_datas->temp_received == NULL)
        if (!stpc_init_packet())
            return;
    if (type == SIGUSR2)
        bit = '1';
    if (stcp_datas->bits_received < PACKET_SIZE)
        stcp_datas->buffer[stcp_datas->bits_received++] = bit;
    else
        stcp_datas->temp_received->body[(stcp_datas->bits_received++) - (PACKET_SIZE)] = bit;
    stcp_datas->time_out = TIME_OUT;
    if (stcp_datas->bits_received == PACKET_SIZE)
        if (!stcp_init_header())
            return;
    if (((stcp_datas->bits_received) - PACKET_SIZE) == (stcp_datas->temp_received->header.size))
        if (!stcp_check_packet())
            return;
}
