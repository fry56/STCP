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

    #define STATUS_WAITING_CONNECTION 0
    #define STATUS_CONNECTED 1
    #define STATUS_WAITING_HAND_CHECK 3

    typedef struct stcp_packet_header_t {
        char type;
        int size;
        int hash;
    } __attribute__((packed)) stcp_packet_header;

    typedef struct stcp_packet_t {
        stcp_packet_header header;
        char *body;
    } stcp_packet;

    struct stcp_packet_type_t {
        char id;
        void (*type_function)(stcp_packet *);
    };

    typedef struct stcp_s {
        int linked_puid;
        unsigned char status;
        stcp_packet *packet;
        char *buffer;
        int bits_received;
        int time_out;
    } stcp;

#endif //stcp_packet
