#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex.h>

#include "../header/linked_list.h"

#define BUFLEN 500 //70(username) + 128(password) + 14(role) + 12(extra characters)

typedef struct{
    int status;
    char message[BUFLEN];
} return_value;

void receive_message_tcp(char message[], int message_length, int socket_fd){

    memset(message, 0, message_length);

    int bytes_received;
    if((bytes_received = read(socket_fd, message, BUFLEN)) < 0){
        printf("Error receiving message");
        exit(EXIT_FAILURE);
    }

    message[bytes_received] = '\0';

}

void send_message_tcp(char message[], int socket_fd){

    if(write(socket_fd, message, strlen(message)) < 0) {
        printf("Error sending message\n");
        exit(EXIT_FAILURE);
    }

}

//Receives udp messages and saves it on message buffer
void receive_message_udp(char message[], int message_length, int socket_fd, struct sockaddr_in* client_addr){

    memset(message, 0, message_length);

    socklen_t socket_len = sizeof(*client_addr);
    int recv_len;
    if((recv_len = recvfrom(socket_fd, message, BUFLEN, 0, (struct sockaddr *)client_addr, (socklen_t *)&socket_len)) < 0){
        printf("Error receiving message\n");
        exit(EXIT_FAILURE);
    }

    message[recv_len] = '\0';

}

return_value validate_message(char* message, char* regex_pattern){
    
    regex_t regex;
    int ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret != 0) {
        return_value regex_compile_failed = {1, "REJECTED: Please try again\n"};
        return regex_compile_failed;
    }

    ret = regexec(&regex, message, 0, NULL, 0);
    if (ret == 0) {
        regfree(&regex);

        return_value parse_correct = {0, ""};
        return parse_correct;

    } else if (ret == REG_NOMATCH) {
        regfree(&regex);

        return_value wrong_syntax = {1, "REJECTED: Invalid syntax\n"};
        return wrong_syntax;
    }

    regfree(&regex);

    return_value regex_match_failed = {1, "REJECTED: Please try again\n"};
    return regex_match_failed;
}

return_value authenticate(node* ll_head, char* input_username, char* input_password, bool is_admin, int* permissions){

    if(ll_head == NULL){
        return_value empty_list_error = {1, "REJECTED: Please try again\n"};
        return empty_list_error;
    }

    node* current = ll_head;
    while(current != NULL){

        if(strcmp(current->pessoa.username, input_username) == 0){

            if(strcmp(current->pessoa.password, input_password) == 0){

                if((is_admin && strcmp(current->pessoa.role, "administrator") == 0) || (!is_admin && strcmp(current->pessoa.role, "aluno") == 0)){
                    return_value login_success = {0, "OK: Logged in successfully\nType HELP to see a list of commands\n"};
                    return login_success;
                    
                } else if(!is_admin && strcmp(current->pessoa.role, "professor") == 0){
                    *permissions = 1;

                    return_value login_success = {0, "OK: Logged in successfully\nType HELP to see a list of commands\n"};
                    return login_success;
                }

                return_value login_success = {1, "REJECTED: Insufficient Permissions\n"};
                return login_success;

            } else{
                return_value incorrect_password = {1, "REJECTED: Username or password incorrect. Please try again\n"};
                return incorrect_password;
            }

        }

        current = current->next;
    }

    return_value username_not_found = {1, "REJECTED: Username not found. Please try again\n"};
    return username_not_found;
}