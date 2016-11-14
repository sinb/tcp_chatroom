//
// Created by sinb on 16-11-14.
//

#ifndef TCP_CHATROOM_CLIENT_HELPER_H
#define TCP_CHATROOM_CLIENT_HELPER_H

#include "client_helper.h"
#include "server_helper.h"

#define NAME_SIZE 20
char name[NAME_SIZE];
char msg[BUFF_SIZE];

// client side helper
void *client_send_msg_to_server(void *arg);
void *client_recv_msg_from_server(void *arg);

#endif //TCP_CHATROOM_CLIENT_HELPER_H
