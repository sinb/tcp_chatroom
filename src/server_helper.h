//
// Created by sinb on 16-11-14.
//

#ifndef TCP_CHATROOM_HELPER_H
#define TCP_CHATROOM_HELPER_H

#define BUFF_SIZE 100
#define CLIENT_MAX 256

int clnt_cnt;
int clnt_socks[CLIENT_MAX];
pthread_mutex_t mutex;

// server side helper
void error_handling(char *message);
void *server_handle_clnt(void *arg);
void server_send_msg_to_all(char *msg, int len);
char* get_client_number(void);
#endif //TCP_CHATROOM_HELPER_H
