/*
** EPITECH PROJECT, 2023
** stcp_listener.c
** File description:
** desc
*/


#include <stdio.h>
#include <unistd.h>
#include <stcp_struct.h>

extern stcp *stcp_datas;

int stcp_listener()
{
    printf("Server pid : %d \n", getppid());
    printf("Whaiting connection ... \n");
    while(1);
}