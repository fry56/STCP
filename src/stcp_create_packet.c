/*
** EPITECH PROJECT, 2023
** stcp_create_packet.c
** File description:
** desc
*/

#include <stcp_struct.h>
#include <stdlib.h>
#include <t_string.h>
#include <stcp_functions.h>

stcp_packet *stcp_create_packet(char type, void *datas, int data_size)
{
    stcp_packet *new_packet;
    if (data_size >= 4031)
        return NULL;
    if ((new_packet = malloc(sizeof(stcp_packet))) == NULL)
        return NULL;
    new_packet->body = data_to_binary(datas, data_size);
    new_packet->header.type = type;
    new_packet->header.size = tstr_len(new_packet->body);
    new_packet->header.hash = PACKET_HASH;
    return new_packet;
}
