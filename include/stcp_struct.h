/*
** EPITECH PROJECT, 2023
** stcp_packet.h
** File description:
** desc
*/
#ifndef stcp_packet_h
    #define stcp_packet_h
    #define PACKET_HASH 55479854

    #include <stdbool.h>

    #define PACKET_SIZE 72
    #define TIME_OUT 15
    #define RETRY 5

    #define STATUS_WAITING_CONNECTION 0
    #define STATUS_CONNECTED 1
    #define STATUS_WAITING_HAND_CHECK 3

    typedef struct stcp_packet_header_t {
        unsigned char type;
        unsigned int size;
        int hash;
    } __attribute__((packed)) stcp_packet_header;

    typedef struct stcp_packet_t {
        stcp_packet_header header;
        int pid_dest;
        char *body;
    } stcp_packet;

    struct stcp_packet_type_t {
        unsigned char id;
        void (*type_function)(stcp_packet *);
    };

    typedef struct stcp_s {
        int linked_puid;
        unsigned char status;
        bool datas_entering;
        stcp_packet *temp_received;
        stcp_packet *temp_sended;
        char *buffer;
        unsigned int bits_received;
        unsigned int time_out;
        unsigned char retry;
    } stcp;

#endif //stcp_packet
