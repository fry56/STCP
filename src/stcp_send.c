/*
** EPITECH PROJECT, 2023
** stcp_send.c
** File description:
** desc
*/

#include <stcp_struct.h>
#include <t_string.h>
#include <signal.h>
#include <unistd.h>
#include <stcp_functions.h>

extern stcp *stcp_datas;

static void stcp_send_buffer(int pid, char *buffer)
{
    for (; *buffer; buffer++) {
        if (*buffer == '1')
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(10000);
    }
    stcp_datas->status = 1;
    stcp_datas->time_out = TIME_OUT;
}

bool stcp_send(int pid, stcp_packet *packet)
{
    char *buffer;

    if (packet == NULL || stcp_datas->status == STATUS_WAITING_HAND_CHECK)
        return false;
    buffer = data_to_binary(&packet->header, sizeof(stcp_packet_header));
    buffer = tstr_concat(buffer, packet->body);
    stcp_send_buffer(pid, buffer);
    return true;
}
