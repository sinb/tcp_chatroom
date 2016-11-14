//
// Created by sinb on 16-11-14.
//
#include<stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server_helper.h"


void server_send_msg_to_all(char *msg, int len)//send message to all clients
{
    int i;
    pthread_mutex_lock(&mutex);
    for(i=0; i<clnt_cnt; i++){
        write(clnt_socks[i], msg, len);
    }
    pthread_mutex_unlock(&mutex);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

void *server_handle_clnt(void *arg)
{
    int sock_client = *((int *)arg);
    int str_len = 0, i;
    char msg[BUFF_SIZE];

    while((str_len = read(sock_client, msg, BUFF_SIZE-1)) > 0){
        //msg[str_len] = 0;
        //printf("Received a messgae: %s", msg);
        server_send_msg_to_all(msg, str_len);
    }

    pthread_mutex_lock(&mutex);
    for(i=0; i<clnt_cnt; i++){//remove disconnencted client
        if(sock_client == clnt_socks[i]){
            while(i++ <= clnt_cnt-1){
                clnt_socks[i] = clnt_socks[i+1];
            }
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutex);
    close(sock_client);

    return NULL;
}
