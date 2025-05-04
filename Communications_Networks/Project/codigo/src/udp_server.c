#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../header/linked_list.h"
#include "../header/utilities.h"

#define N_ADMIN_COMMANDS 7

void handle_admin_login(int socket_fd, node* ll_head, struct sockaddr_in* client_addr) {
    char message[BUFLEN];
    
    while (1) {
        receive_message_udp(message, BUFLEN, socket_fd, client_addr);
        return_value login = validate_message(message, "LOGIN [^ ]+ [^ ]+$");

        if (login.status == 0) {
            user aux;
            sscanf(message, "LOGIN %s %s", aux.username, aux.password);

            return_value auth = authenticate(ll_head, aux.username, aux.password, true, NULL);
            send_message_udp(auth.message, BUFLEN, socket_fd, client_addr);

            if (auth.status == 0)
                break;
            else
                continue;
                          
        } else {
            send_message_udp(login.message, BUFLEN, socket_fd, client_addr);
        }
    }

}

int validate_admin_commands(char* message){

    char* commands[] = {
        "HELP$",
        "LIST$",
        "EXIT$",
        "QUIT_SERVER$",
        "ADD_USER [^ ]+ [^ ]+ aluno$",
        "ADD_USER [^ ]+ [^ ]+ professor$",
        "DEL [^ ]+$",
        "ADD_USER [^ ]+ [^ ]+ administrador$"
    };

    for(int i=0; i<N_ADMIN_COMMANDS; i++){
        if(validate_message(message, commands[i]).status == 0){
            return i;
        }
    }

    return -1;
}

void send_linked_list_udp(node* ll_head, int socket_fd, struct sockaddr_in* client_addr){
    char message[BUFLEN];
    node* current = ll_head;

    while(current != NULL){
        strcat(message, current->pessoa.username);
        strcat(message, " - ");
        strcat(message, current->pessoa.password);
        strcat(message, " - ");
        strcat(message, current->pessoa.role);
        strcat(message, "\n");

        current = current->next;
    }

    send_message_udp(message, BUFLEN, socket_fd, client_addr);
}

void quit_server(connection_node* connection_head){

    connection_node* temp = connection_head;
    while(temp != NULL){
        close(temp->fd);
        temp = temp->next;
    }

    temp = connection_head;
    while(temp != NULL){
        pthread_cancel(temp->thread);
        pthread_join(temp->thread, NULL);
        temp = temp->next;
    }
}

void add_user(char* str, node** ll_head){

    user aux;
    sscanf(str, "ADD_USER %s %s %s", aux.username, aux.password, aux.role);

    *ll_head = insert_at_beginning(*ll_head, aux);
}

void delete_user(char* str, node** ll_head, int socket_fd, struct sockaddr_in* client_addr){

    user aux;
    sscanf(str, "DEL %s", aux.username);

    *ll_head = delete_node(*ll_head, aux.username, socket_fd, client_addr);
    
    send_message_udp("USER DELETED SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
}

int handle_admin_commands(int socket_fd, node** ll_head, connection_node** connection_head, struct sockaddr_in* client_addr){
    char message[BUFLEN];

    while(1){
        
        receive_message_udp(message, BUFLEN, socket_fd, client_addr);
        
        switch(validate_admin_commands(message)){

            case 0:
                send_message_udp("- LIST\n- ADD_USER {username} {password} {administrador/aluno/professor}\n- DEL {username}\n- QUIT_SERVER\n- EXIT\n", BUFLEN, socket_fd, client_addr);
                break;
            
            case 1:
                send_linked_list_udp(*ll_head, socket_fd, client_addr);
                break;

            case 2:
                send_message_udp("EXIT SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
                return 1;
            
            case 3:
                quit_server(*connection_head);
                send_message_udp("QUIT SERVER SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
                return 0;

            case 4:
                add_user(message, ll_head);
                send_message_udp("ADDED NEW ALUNO SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
                break;

            case 5:
                add_user(message, ll_head);
                send_message_udp("ADDED NEW PROFESSOR SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
                break;

            case 6:
                delete_user(message, ll_head, socket_fd, client_addr);
                break;

            case 7:
                add_user(message, ll_head);
                send_message_udp("ADDED NEW ADMINISTRATOR SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);
                break;
            
            default:
                send_message_udp("REJECTED: Invalid syntax or command doesn't exist\n", BUFLEN, socket_fd, client_addr);
                break;
        }
    }
}

void handle_admin(int socket_fd, node** ll_head, connection_node** connection_head){

    struct sockaddr_in client_addr;

    do{
        handle_admin_login(socket_fd, *ll_head, &client_addr);
    } while(handle_admin_commands(socket_fd, ll_head, connection_head, &client_addr) == 1);
    
}