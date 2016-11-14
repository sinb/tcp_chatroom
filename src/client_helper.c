//
// Created by sinb on 16-11-14.
//
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "client_helper.h"
#include "server_helper.h"

void *client_send_msg_to_server(void *arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE+BUFF_SIZE];
    while(1){
        //puts("Input Message(Q quit):");
        fgets(arg, BUFF_SIZE, stdin);
        if( !strcmp(arg, "q\n") || !strcmp(arg, "Q\n") ){
            fputs("Quit!\n", stderr);
            close(sock);
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, arg);
        write(sock, name_msg, strlen(name_msg));
        //	fputs("Sent a message!\n", stderr);
    }
    return NULL;
}
void *client_recv_msg_from_server(void *arg)
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE+BUFF_SIZE];
    int str_len;
    while(1){
        str_len = (int) read(sock, name_msg, NAME_SIZE + BUFF_SIZE - 1);
        if(str_len < 0) return (void*)-1;
        name_msg[str_len] = 0;
        fputs(name_msg, stdout);
    }
    return NULL;
}

