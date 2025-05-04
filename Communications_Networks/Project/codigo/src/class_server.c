#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wait.h>
#include <signal.h>

#include "../header/linked_list.h"
#include "../header/utilities.h"
#include "../header/user.h"

#define MAX_CLIENTS 5

char FILE_NAME[FILENAME_MAX];

typedef struct {

    short PORT;
    node** ll_head;
    connection_node** connection_head;
    class_node** class_head;

} thread_args;

pthread_t tcp_handler;
pthread_t udp_handler;

node* head;
connection_node* connection_head;
class_node* class_head;

int udp_fd;
int tcp_fd;

void* handle_tcp(void *args_ptr){
    class_counter = 0;

    thread_args *args = (thread_args *)args_ptr;

    short PORT = args->PORT;
    node** ll_head = args->ll_head;
    connection_node** connection_head = args->connection_head;
    class_node** class_head = args->class_head;
    
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    tcp_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(tcp_fd < 0){
        printf("TCP socket failed\n");
        pthread_exit(NULL);
    }

    if(bind(tcp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("TCP bind failed\n");
        pthread_exit(NULL);
    }

    if(listen(tcp_fd, MAX_CLIENTS) < 0){
        printf("TCP listen failed\n");
        pthread_exit(NULL);
    }

    printf("TCP socket listening...\n");

    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);

    while(1){
        int client_fd = accept(tcp_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
        if(client_fd < 0){
            printf("TCP client accept failed\n");
            pthread_exit(NULL);
        } else {

            pthread_t thread;

            tcp_client_thread_args client_args;
            client_args.client_fd = client_fd;
            client_args.ll_head = ll_head;
            client_args.connection_head = connection_head;
            client_args.class_head = class_head;

            *connection_head = insert_connection_at_beginning(*connection_head, thread, client_fd, 't');

            if(pthread_create(&thread, NULL, handle_client, (void *)&client_args) != 0){
                printf("Thread creation failed\n");
                close(client_fd);
                continue;
            }            
        }
    }

    printf("TCP socket closing...\n");
}

void* handle_udp(void *args_ptr){
    thread_args *args = (thread_args *)args_ptr;

    short PORT = args->PORT;
    node** ll_head = args->ll_head;
    connection_node** connection_head = args->connection_head;

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    udp_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp_fd < 0){
        printf("UDP socket failed\n");
        pthread_exit(NULL);
    }

    if(bind(udp_fd,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("UDP bind failed\n");
        pthread_exit(NULL);
	}

    printf("UDP socket listening...\n");
    
    handle_admin(udp_fd, ll_head, connection_head);

    close(udp_fd);
    close(tcp_fd);

    pthread_cancel(tcp_handler);
    pthread_join(tcp_handler, NULL);

    pthread_exit(NULL);
}

void handle_server_sigint(){
    quit_server(connection_head);

    pthread_cancel(tcp_handler);
    pthread_cancel(udp_handler);

    pthread_join(tcp_handler, NULL);
    pthread_join(udp_handler, NULL);

    close(tcp_fd);
    close(udp_fd);

    write_list_to_file(head, FILE_NAME);

    free_connection_list(connection_head);
    free_class_list(class_head);
    free_list(head);

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    
    if(argc != 4){
        perror("./class_server <CLASS_PORT> <CONFIG_PORT> <config_file_name.txt>\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, SIG_IGN);

    const short CLASS_PORT = (short)atoi(argv[1]);
    const short CONFIG_PORT = (short)atoi(argv[2]);
    strcpy(FILE_NAME, argv[3]);

    head = NULL;
    read_file(&head, FILE_NAME);

    connection_head = NULL;
    class_head = NULL;

    //udp thread

    thread_args udp_args;
    udp_args.PORT = CONFIG_PORT;
    udp_args.ll_head = &head;
    udp_args.connection_head = &connection_head;
    udp_args.class_head = &class_head;

    pthread_create(&udp_handler, NULL, handle_udp, (void *)&udp_args);

    //tcp thread

    thread_args tcp_args;
    tcp_args.PORT = CLASS_PORT;
    tcp_args.ll_head = &head;
    tcp_args.connection_head = &connection_head;
    tcp_args.class_head = &class_head;

    pthread_create(&tcp_handler, NULL, handle_tcp, (void *)&tcp_args);

    signal(SIGINT, handle_server_sigint);

    pthread_join(udp_handler, NULL);
    pthread_join(tcp_handler, NULL);

    write_list_to_file(head, FILE_NAME);

    free_connection_list(connection_head);
    free_class_list(class_head);
    free_list(head);

    return 0;

}