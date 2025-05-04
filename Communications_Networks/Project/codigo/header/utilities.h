#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>

#include "../header/linked_list.h"

#define BUFLEN 500 //70(username) + 128(password) + 14(role) + 12(extra characters) + extra

typedef struct {

    int client_fd;
    node** ll_head;
    connection_node** connection_head;
    class_node** class_head;

} tcp_client_thread_args;

typedef struct{
    int status;
    char message[BUFLEN];
} return_value;

void receive_message_tcp(char message[], int message_length, int socket_fd);
void send_message_tcp(char message[], int socket_fd);
void receive_message_udp(char message[], int message_length, int socket_fd, struct sockaddr_in* client_addr);

return_value validate_message(char* message, char* regex_pattern);
return_value authenticate(node* ll_head, char* input_username, char* input_password, bool is_admin, int* permissions);

#endif