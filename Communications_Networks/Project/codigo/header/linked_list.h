#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

typedef struct {

    char username[70];
    char password[128];
    char role[14];

} user;

typedef struct node {

    user pessoa;
    struct node* next;

} node;

void send_message_udp(char message[], int message_length, int socket_fd, struct sockaddr_in* client_addr);

node* create_node(user new_user);
node* insert_at_beginning(node* head, user new_user);
node* delete_node(node* head, char* username, int socket_fd, struct sockaddr_in* client_addr);
void read_file(node** head, char* FILE_NAME);
void write_list_to_file(node* head, char* FILE_NAME);
void free_list(node* head);
void print_list(node* head);

//---------------------------------------------------------------

typedef struct connection_node {

    pthread_t thread;
    int fd;
    char protocol;
    struct connection_node* next;

} connection_node;

connection_node* create_connection_node(pthread_t thread, int fd, char protocol);
connection_node* insert_connection_at_beginning(connection_node* head, pthread_t thread, int fd, char protocol);
void free_connection_list(connection_node* head);
void print_connection_list(connection_node* head);

//---------------------------------------------------------------

extern int class_counter;

typedef struct class_node{

    char name[50];
    int max_size;
    int current_size;

    char** alunos;

    int port;
    char mc_addr[20];
    int mc_fd;

    struct sockaddr_in addr_in;

    struct class_node* next;

} class_node;

class_node* create_class_node(char* name, int max_size);
class_node* insert_class_at_beginning(class_node* head, char* name, int max_size);
void free_class_list(class_node* head);
void print_class_list(class_node* head);

#endif