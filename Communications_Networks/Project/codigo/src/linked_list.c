#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFLEN 224 //70(username) + 128(password) + 14(role) + 12(extra characters)
#define USERNAME_LEN 70

//Sends udp messages on message buffer
void send_message_udp(char message[], int message_length, int socket_fd, struct sockaddr_in* client_addr){

    socklen_t socket_len = sizeof(*client_addr);

    if(sendto(socket_fd, message, message_length, 0, (struct sockaddr *)client_addr, socket_len) < 0) {
		printf("Error sending message\n");
        exit(EXIT_FAILURE);
	}

}

typedef struct {

    char username[70];
    char password[128];
    char role[14];

} user;

typedef struct node {

    user pessoa;
    struct node* next;

} node;

node* create_node(user new_user){

    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        perror("ERROR: Creating new user node\n");
        exit(EXIT_FAILURE);
    }

    new_node->pessoa = new_user;
    new_node->next = NULL;

    return new_node;
}

node* insert_at_beginning(node* head, user new_user){
    node* new_node = create_node(new_user);
    new_node->next = head;
    return new_node;
}

node* delete_node(node* head, char* username, int socket_fd, struct sockaddr_in* client_addr){
    node* current = head;
    node* prev = NULL;

    if(current != NULL && strcmp(current->pessoa.username, username) == 0){
        node* temp = current;
        head = current->next;
        free(temp);
        return head;
    }

    while(current != NULL && strcmp(current->pessoa.username, username) != 0){
        prev = current;
        current = current->next;
    }

    if(current == NULL){
        send_message_udp("Username not found in the list\n", BUFLEN, socket_fd, client_addr);
        return head;
    }

    prev->next = current->next;
    free(current);

    send_message_udp("Deleted user SUCCESSFULLY\n", BUFLEN, socket_fd, client_addr);

    return head;
}

void read_file(node** head, char* FILE_NAME){

    char file_path[FILENAME_MAX + 5];
    strcpy(file_path, "data/");
    strcat(file_path, FILE_NAME);

    FILE* file = fopen(file_path, "r");
    if(file == NULL){
        perror("ERROR: Opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[BUFLEN];
    while(fgets(line, BUFLEN, file) != NULL){
        
        user aux;
        sscanf(line, "%[^;];%[^;];%s", aux.username, aux.password, aux.role);

        *head = insert_at_beginning(*head, aux);

    }

}

void write_list_to_file(node* head, char* FILE_NAME){

    char file_path[FILENAME_MAX + 5];
    strcpy(file_path, "data/");
    strcat(file_path, FILE_NAME);

    FILE* file = fopen(file_path, "w");
    if(file == NULL){
        perror("ERROR: Opening file\n");
        exit(EXIT_FAILURE);
    }

    node* temp = head;
    while(temp != NULL){
        fprintf(file, "%s;%s;%s\n", temp->pessoa.username, temp->pessoa.password, temp->pessoa.role);
        temp = temp->next;
    }

    fclose(file);
}

void free_list(node* head){
    node* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(node* head){
    node* temp = head;
    while(temp != NULL){
        printf("Username: %s / ", temp->pessoa.username);
        printf("Password: %s / ", temp->pessoa.password);
        printf("Role: %s\n", temp->pessoa.role);
        temp = temp->next;
    }
}

/*-----------------
    THREAD LIST
-----------------*/

typedef struct connection_node {

    pthread_t thread;
    int fd;
    char protocol;
    struct connection_node* next;

} connection_node;

connection_node* create_connection_node(pthread_t thread, int fd, char protocol){

    connection_node* new_node = (connection_node*)malloc(sizeof(connection_node));
    if (new_node == NULL) {
        perror("ERROR: Creating new user node\n");
        exit(EXIT_FAILURE);
    }

    new_node->thread = thread;
    new_node->fd = fd;
    new_node->protocol = protocol;
    new_node->next = NULL;

    return new_node;
}

connection_node* insert_connection_at_beginning(connection_node* head, pthread_t thread, int fd, char protocol){
    connection_node* new_node = create_connection_node(thread, fd, protocol);
    new_node->next = head;
    return new_node;
}

void free_connection_list(connection_node* head){
    connection_node* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_connection_list(connection_node* head){
    connection_node* temp = head;
    while(temp != NULL){
        printf("socket fd: %d / ", temp->fd);
        printf("Protocol: %c\n", temp->protocol);
        temp = temp->next;
    }
}

/*------------------
    CLASSES LIST
------------------*/

int class_counter;

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

class_node* create_class_node(char* name, int max_size){

    class_counter++;

    class_node* new_node = (class_node*)malloc(sizeof(class_node));
    if (new_node == NULL) {
        perror("ERROR: Creating new user node\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->name, name);
    new_node->max_size = max_size;
    new_node->current_size = 0;

    new_node->port = 3000 + class_counter;
    sprintf(new_node->mc_addr, "239.0.0.%d", class_counter);

    if((new_node->mc_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("ERROR making multicast socket\n");
        exit(EXIT_FAILURE);
    }

    memset(&new_node->addr_in, 0, sizeof(struct sockaddr_in));
    new_node->addr_in.sin_family = AF_INET;
    new_node->addr_in.sin_addr.s_addr = inet_addr(new_node->mc_addr);
    new_node->addr_in.sin_port = htons(new_node->port);

    int enable=3;
    if(setsockopt(new_node->mc_fd, IPPROTO_IP, IP_MULTICAST_TTL, &enable, sizeof(enable)) < 0){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    new_node->alunos = (char**)malloc(max_size * sizeof(char*));
    if(new_node->alunos == NULL){
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<max_size; i++){
        new_node->alunos[i] = (char*)malloc(USERNAME_LEN * sizeof(char));

        if(new_node->alunos[i] == NULL){
            perror("Failed to allocate memory for a string");
            for (int j = 0; j < i; j++) {
                free(new_node->alunos[j]);
            }
            free(new_node->alunos);
            exit(EXIT_FAILURE);
        }
    }

    new_node->next = NULL;

    return new_node;
}

class_node* insert_class_at_beginning(class_node* head, char* name, int max_size){
    class_node* new_node = create_class_node(name, max_size);
    new_node->next = head;
    return new_node;
}

void free_class_list(class_node* head){
    class_node* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        
        for(int i=0; i<temp->max_size; i++){
            free(temp->alunos[i]);
        }
        free(temp->alunos);

        free(temp);
    }
}

void print_class_list(class_node* head){
    class_node* temp = head;
    while(temp != NULL){
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}
