#ifndef USER_H
#define USER_H

#include "../header/linked_list.h"

void handle_admin(int socket_fd, node** ll_head, connection_node** connection_head);
void *handle_client(void *args_ptr);

void quit_server(connection_node* connection_head);

#endif