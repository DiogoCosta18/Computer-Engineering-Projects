#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#include "../header/utilities.h"

int socket_fd;
struct sockaddr_in server_addr;


void handle_udp_server(int socket_fd, struct sockaddr_in* server_addr){
    
    char message[BUFLEN];
    char response[BUFLEN];

    do{

        scanf(" %[^\n]", message);
        send_message_udp(message, BUFLEN, socket_fd, server_addr);

        receive_message_udp(response, BUFLEN, socket_fd, server_addr);
        
        printf("---------------------------------\n");
        printf("%s", response);
        printf("---------------------------------\n");

    } while(strcmp(message, "QUIT_SERVER") != 0 && strcmp(message, "EXIT") != 0);

}

void handle_admin_sigint(){
    send_message_udp("EXIT", 5, socket_fd, &server_addr);
    close(socket_fd);

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){

    if(argc != 3){
        printf("./admin_client <SERVER_IP> <CONFIG_PORT>\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, SIG_IGN);

    char SERVER_IP[15];
    strcpy(SERVER_IP, argv[1]);
    const short CONFIG_PORT = (short)atoi(argv[2]);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(CONFIG_PORT);

    if((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        printf("UDP socket failed\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_admin_sigint);

    handle_udp_server(socket_fd, &server_addr);
    
    return 0;
}