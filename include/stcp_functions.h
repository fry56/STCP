/*
** EPITECH PROJECT, 2023
** stcp_functions.h
** File description:
** desc
*/
#ifndef stcp_functions
    #define stcp_functions

    #include <stcp_struct.h>
    #include <stcp_packet_type.h>
    #include <t_ctype.h>

    int stcp_init();

    void stcp_receive(int type);
    bool stcp_send(int pid, stcp_packet *packet);
    void stcp_destroy_packet(stcp_packet *packet);
    bool stcp_packet_drop();

    void stcp_time_out_update();

    stcp_packet *stcp_create_packet(char type, void *datas, int data_size);

    void stcp_hand_check(stcp_packet *packet);
    void stcp_send_hand_check();

    void stcp_sync(stcp_packet *packet);
    void stcp_send_sync(int pid);

    char *data_to_binary(void *data, tsize_t size);
#endif //stcp_functions
