/*
** EPITECH PROJECT, 2023
** stcp_init.c
** File description:
** desc
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stcp_functions.h>
#include <stcp_struct.h>
#include <stdlib.h>
#include <t_mem.h>

extern stcp *stcp_datas;

int stcp_init()
{
    stcp *new_stcp = malloc(sizeof(stcp));
    struct sigaction action;

    if (new_stcp == NULL)
        return 0;
    if ((new_stcp->buffer = tcalloc(1, 4048)) == NULL) {
        free(new_stcp);
        return 0;
    }
    sigemptyset(&action.sa_mask);
    action.sa_handler = stcp_receive;
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    new_stcp->linked_puid = -1;
    new_stcp->status = STATUS_WAITING_CONNECTION;
    new_stcp->packet = NULL;
    new_stcp->time_out = TIME_OUT;
    stcp_datas = new_stcp;
    return 1;
}
