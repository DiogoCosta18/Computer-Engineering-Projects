#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "../header/linked_list.h"
#include "../header/utilities.h"

#define N_STUDENT_COMMANDS 5
#define N_TEACHER_COMMANDS 5

#define CLASS_NAME_MAX 50
#define USERNAME_LEN 70

void handle_client_login(int socket_fd, node* ll_head, int* permissions, char* client_username){
    
    char message[BUFLEN];

    while(1){
        
        receive_message_tcp(message, BUFLEN, socket_fd);
        return_value login = validate_message(message, "LOGIN [^ ]+ [^ ]+$");
        
        if (login.status == 0) {
            user aux;
            sscanf(message, "LOGIN %s %s", aux.username, aux.password);

            return_value auth = authenticate(ll_head, aux.username, aux.password, false, permissions);
            send_message_tcp(auth.message, socket_fd);

            if (auth.status == 0){
                strcpy(client_username, aux.username);
                break;

            } else {
                continue;
            }

        } else{
            send_message_tcp(login.message, socket_fd);
        }

    }
}

int validate_student_commands(char* message){
    
    char* commands[] = {
        "HELP$",
        "LIST_CLASSES$",
        "EXIT$",
        "LIST_SUBSCRIBED$",
        "SUBSCRIBE_CLASS [^ ]+$",
    };

    for(int i=0; i<N_STUDENT_COMMANDS; i++){
        if(validate_message(message, commands[i]).status == 0){
            return i;
        }
    }

    return -1;

}

int validate_teacher_commands(char* message){
    
    char* commands[] = {
        "HELP$",
        "LIST_CLASSES$",
        "EXIT$",
        "CREATE_CLASS [^ ]+ [0-9]+$",
        "SEND [^ ]+ [^ ]+$"
    };

    for(int i=0; i<N_TEACHER_COMMANDS; i++){
        if(validate_message(message, commands[i]).status == 0){
            return i;
        }
    }

    return -1;

}

void subscribe_class(char* message, class_node** class_head, int client_fd, char* client_username){
    
    char class_name[CLASS_NAME_MAX];
    sscanf(message, "SUBSCRIBE_CLASS %s", class_name);

    class_node* temp = *class_head;
    while(temp != NULL){

        if(strcmp(temp->name, class_name) == 0){

            if(temp->current_size >= temp->max_size){
                send_message_tcp("ERROR: CLASS IS ALREADY FULL\n", client_fd);
                return;
            }

            char subscribe_info[BUFLEN];
            sprintf(subscribe_info, "CLASS INFO:\nCLASS ADDRESS: %s\nCLASS PORT: %d\n", temp->mc_addr, temp->port);

            strcpy(temp->alunos[temp->current_size], client_username);
            temp->current_size++;

            send_message_tcp(subscribe_info, client_fd);
            return;
        }

        temp = temp->next;
    }

    send_message_tcp("ERROR: CLASS DOES NOT EXIST\n", client_fd);
}

void list_classes(int client_fd, class_node** class_head){

    char response[BUFLEN];

    class_node* temp = *class_head;
    while(temp != NULL){

        strcat(response, "- ");
        strcat(response, temp->name);
        strcat(response, "\n");

        temp = temp->next;
    }

    if(strlen(response) == 0){
        send_message_tcp("ERROR: NO CLASSES FOUND\n", client_fd);

    } else{
        send_message_tcp(response, client_fd);
    }
}

void list_subscribed(int client_fd, class_node** class_head, char* client_username){

    char response[BUFLEN];

    class_node* temp = *class_head;
    while(temp != NULL){

        for(int i=0; i<temp->current_size; i++){
            if(strcmp(client_username, temp->alunos[i]) == 0){

                strcat(response, temp->name);
                strcat(response, "\n");
                break;

            }
        }

        temp = temp->next;
    }

    if(strlen(response) == 0){
        send_message_tcp("NOT SUBSCRIBED TO ANY CLASS\n", client_fd);

    } else{
        send_message_tcp(response, client_fd);
    }
}

void remove_student_from_classes(class_node** head, char* username){

    class_node* temp = *head;
    while(temp != NULL){

        int i;
        for(i=0; i<temp->current_size; i++){

            if(strcmp(temp->alunos[i], username) == 0){
                
                for(int j=i; j<temp->current_size-1; j++){
                    temp->alunos[j] = temp->alunos[j + 1];
                }

                temp->current_size--;
                break;

            }
        }

        temp = temp->next;
    }
}

void handle_student_commands(int client_fd, class_node** class_head, char* client_username){

    char message[BUFLEN];
    while(1){
        receive_message_tcp(message, BUFLEN, client_fd);

        switch(validate_student_commands(message)){

            case 0:
                send_message_tcp("- LIST_CLASSES\n- LIST_SUBSCRIBED\n- SUBSCRIBE_CLASS {class name}\n- EXIT\n", client_fd);
                break;

            case 1:
                list_classes(client_fd, class_head);
                break;

            case 2:
                remove_student_from_classes(class_head, client_username);
                send_message_tcp("EXIT SUCCESSFULLY\n", client_fd);
                return;

            case 3:
                list_subscribed(client_fd, class_head, client_username);
                break;

            case 4:
                subscribe_class(message, class_head, client_fd, client_username);
                break;
            
            default:
                send_message_tcp("REJECTED: Invalid syntax or command doesn't exist\n", client_fd);
                break;
        }
    }
}

void add_class(char* str, class_node** class_head, int client_fd){

    char class_name[CLASS_NAME_MAX];
    int class_max_size;

    sscanf(str, "CREATE_CLASS %s %d", class_name, &class_max_size);

    if(class_max_size <= 0){
        send_message_tcp("ERROR: CLASS SIZE HAS TO BE A POSITIVE INTEGER\n", client_fd);
        return;
    }

    class_node* temp = *class_head;

    while(temp != NULL){

        if(strcmp(temp->name, class_name) == 0){
            send_message_tcp("ERROR: CLASS ALREADY EXISTS\n", client_fd);
            return;
        }
        temp = temp->next;
    }

    *class_head = insert_class_at_beginning(*class_head, class_name, class_max_size);
    send_message_tcp("CLASS CREATED SUCCESSFULLY\n", client_fd);
}

void send_multicast(char* message, class_node** class_head, int client_fd){

    char class_name[CLASS_NAME_MAX];
    char buf[BUFLEN];

    sscanf(message, "SEND %s %s", class_name, buf);

    class_node* temp = *class_head;
    while(temp != NULL){

        if(strcmp(temp->name, class_name) == 0){
            send_message_udp(buf, BUFLEN, temp->mc_fd, &temp->addr_in);
            send_message_tcp("MESSAGE SENT SUCCESSFULLY\n", client_fd);
            return;
        }
        temp = temp->next;
    }

    send_message_tcp("ERROR: CLASS NOT FOUND\n", client_fd);
}

void handle_teacher_commands(int client_fd, class_node** class_head){

    char message[BUFLEN];
    while(1){
        receive_message_tcp(message, BUFLEN, client_fd);

        switch(validate_teacher_commands(message)){

            case 0:
                send_message_tcp("- LIST_CLASSES\n- CREATE_CLASS {class name} {class max size}\n- SEND {class name} {message}\n- EXIT\n", client_fd);
                break;

            case 1:
                list_classes(client_fd, class_head);
                break;

            case 2:
                send_message_tcp("\nEXIT SUCCESSFULLY\n", client_fd);
                return;

            case 3:
                add_class(message, class_head, client_fd);
                break;

            case 4:
                send_multicast(message, class_head, client_fd);
                break;
            
            default:
                send_message_tcp("REJECTED: Invalid syntax or command doesn't exist\n", client_fd);
                break;
        }
    }
}

void *handle_client(void *args_ptr){
    tcp_client_thread_args *args = (tcp_client_thread_args *)args_ptr;

    int client_fd = args->client_fd;
    node** ll_head = args->ll_head;
    class_node** class_head = args->class_head;

    int client_perms = 0;
    char client_username[USERNAME_LEN];

    handle_client_login(client_fd, *ll_head, &client_perms, client_username);

    if(client_perms){
        handle_teacher_commands(client_fd, class_head);
    } else{
        handle_student_commands(client_fd, class_head, client_username);
    }

    close(client_fd);
    pthread_exit(NULL);

}