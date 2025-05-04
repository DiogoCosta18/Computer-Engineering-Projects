#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <signal.h>

#include "../header/utilities.h"

typedef struct{

    char multicast_addr[20];
    int multicast_port;

} multicast_thread_args;

typedef struct{

    pthread_t thread;
    int multicast_fd;
    struct ip_mreq mreq;

} multicast_info;

multicast_info threads[10];
int thread_counter;

int socket_fd;

void* receive_multicast(void* args_ptr){

    multicast_thread_args* args = (multicast_thread_args*)args_ptr;

    int multicast_fd = socket(AF_INET, SOCK_DGRAM, 0);

    int reuse = 1;
    if (setsockopt(multicast_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEADDR)");
        close(multicast_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in multicast_addr;

    memset(&multicast_addr, 0, sizeof(struct sockaddr_in));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = INADDR_ANY;
    multicast_addr.sin_port = htons(args->multicast_port);

    if(bind(multicast_fd, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(args->multicast_addr);
    mreq.imr_interface.s_addr = INADDR_ANY;
    
    if(setsockopt(multicast_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    threads[thread_counter].multicast_fd = multicast_fd;
    threads[thread_counter].mreq = mreq;

    thread_counter++;

    char buffer[BUFLEN];

    while(1){
        receive_message_udp(buffer, BUFLEN, multicast_fd, &multicast_addr);
        printf("---------------------------------\n");
        printf("%s\n", buffer);
        printf("---------------------------------\n");
    }

}

void handle_tcp_server(int socket_fd){
    
    char message[BUFLEN];
    char response[BUFLEN];

    do{
        
        scanf(" %[^\n]", message);
        send_message_tcp(message, socket_fd);

        receive_message_tcp(response, BUFLEN, socket_fd);

        if(strlen(response) != 0){
            printf("---------------------------------\n");
            printf("%s", response);
            printf("---------------------------------\n");

        } else {
            break;
        }

        if(strncmp(response, "CLASS INFO", 10) == 0){
            
            multicast_thread_args args;
            sscanf(response, "CLASS INFO:\nCLASS ADDRESS: %s\nCLASS PORT: %d\n", args.multicast_addr, &args.multicast_port);

            pthread_create(&threads[thread_counter].thread, NULL, receive_multicast, (void*)&args);

        } 

    } while(strcmp(message, "EXIT") != 0);
}

void handle_sigint(){

    send_message_tcp("EXIT", socket_fd);

    char exit_response[BUFLEN];
    receive_message_tcp(exit_response, BUFLEN, socket_fd);
    printf("%s---------------------------------\n", exit_response);

    for(int i=0; i<thread_counter; i++){
        if (setsockopt(threads[i].multicast_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &threads[i].mreq, sizeof(struct ip_mreq)) == -1) {
            perror("setsockopt (IP_DROP_MEMBERSHIP)");
            exit(EXIT_FAILURE);
        }

        close(threads[i].multicast_fd);
        pthread_cancel(threads[i].thread);
    }

    for(int i=0; i<thread_counter; i++){
        pthread_join(threads[i].thread, NULL);
    }
    
    close(socket_fd);

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){

    if(argc != 3){
        printf("./admin_client <SERVER_IP> <CLASS_PORT>\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, SIG_IGN);

    char SERVER_IP[15];
    strcpy(SERVER_IP, argv[1]);
    const short CLASS_PORT = (short)atoi(argv[2]);

    thread_counter = 0;

    struct hostent *hostPtr;

    if((hostPtr = gethostbyname(SERVER_IP)) == 0){
        printf("Couldn't get host");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
    server_addr.sin_port = htons(CLASS_PORT);

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("TCP socket failed\n");
        exit(EXIT_FAILURE);
    }
    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("TCP connection failed\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);

    handle_tcp_server(socket_fd);

    close(socket_fd);

    return 0;
}
    