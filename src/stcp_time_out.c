/*
** EPITECH PROJECT, 2023
** stcp_time_out.c
** File description:
** desc
*/

#include <stcp_struct.h>
#include <stcp_functions.h>

extern stcp *stcp_datas;

static void stcp_time_out()
{
    stcp_datas->linked_puid = -1;
    stcp_datas->status = STATUS_WAITING_CONNECTION;
    stcp_datas->time_out = TIME_OUT;
    stcp_destroy_packet(stcp_datas->temp_sended);
    stcp_destroy_packet(stcp_datas->temp_received);
    printf("Connexion time out ! \n");
}

static void stcp_hand_check_time_out()
{
    if (stcp_datas->retry == RETRY && stcp_datas->time_out == 0) {
        stcp_time_out();
        return;
    }
    if (stcp_datas->time_out == 0) {
        stcp_datas->time_out = TIME_OUT;
        stcp_datas->retry++;
        stcp_send(stcp_datas->temp_sended->pid_dest
                , stcp_datas->temp_sended);
        printf("Packet resend Try : %d\n", stcp_datas->retry);
    }
}

void stcp_time_out_update()
{
    if (stcp_datas->datas_entering
        || stcp_datas->status == STATUS_WAITING_HAND_CHECK) {
        stcp_datas->time_out--;
    }
    if (stcp_datas->time_out == 0) {
        if (stcp_datas->datas_entering) {
            stcp_packet_drop();
            return;
        }
        if (stcp_datas->status == STATUS_WAITING_HAND_CHECK)
            stcp_hand_check_time_out();
    }
}
