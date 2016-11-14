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

void server_send_msg_to_one(char *msg, int len, int sock_client)//send message to all clients
{
    write(sock_client, msg, len);
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

    while((str_len = (int) read(sock_client, msg, BUFF_SIZE - 1)) > 0){
        //msg[str_len] = 0;
        //printf("Received a messgae: %s", msg);
        if (strstr(msg, "\\List") != NULL)
        {
            printf("%d\n", strlen(get_client_number()));
            server_send_msg_to_one(get_client_number(), strlen(get_client_number()), sock_client);
        }

        else
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

char* get_client_number(void)
{
    char message[30];
    int num = 0, i;
    for (i = 0; i < CLIENT_MAX; ++i)
    {
        if (clnt_socks[i] > 2)
            num += 1;
    }
    sprintf(message, "Current Client Number: %d\n", num);
    return message;
}