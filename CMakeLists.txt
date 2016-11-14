cmake_minimum_required(VERSION 2.8)
project(tcp_chatroom)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_FILES src/server.c src/server_helper.h src/server_helper.c src/client_helper.h src/client_helper.c)
set(CLIENT_FILES src/client.c src/server_helper.h src/server_helper.c src/client_helper.h src/client_helper.c)

add_executable(tcp_chatroom_server ${SERVER_FILES})
TARGET_LINK_LIBRARIES( tcp_chatroom_server pthread)

add_executable(tcp_chatroom_client ${CLIENT_FILES})
TARGET_LINK_LIBRARIES( tcp_chatroom_client pthread)