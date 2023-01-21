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
    printf("Send \n");
    for (; *buffer; buffer++) {
        if (*buffer == '1')
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(10000);
    }
    stcp_datas->time_out = TIME_OUT;
}

bool stcp_send(int pid, stcp_packet *packet)
{
    char *buffer;

    if (packet == NULL)
        return false;
    if (pid == - 1)
        return false;
    stcp_destroy_packet(stcp_datas->temp_sended);
    stcp_datas->temp_sended = packet;
    stcp_datas->temp_sended->pid_dest = pid;
    buffer = data_to_binary(&packet->header, sizeof(stcp_packet_header));
    buffer = tstr_concat(buffer, packet->body);
    stcp_send_buffer(pid, buffer);
    return true;
}
