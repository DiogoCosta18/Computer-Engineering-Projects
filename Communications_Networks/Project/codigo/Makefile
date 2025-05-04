DEBUG ?= 0
ifeq ($(DEBUG), 1)
    DEBUG_FLAGS = -g
else
    DEBUG_FLAGS =
endif

FLAGS = -Wall -Wextra

all: class_client admin_client class_server

class_client: src/class_client.c src/utilities.c src/linked_list.c
	gcc $(DEBUG_FLAGS) $(FLAGS) -pthread $^ -o bin/$@

admin_client: src/admin_client.c src/utilities.c src/linked_list.c
	gcc $(DEBUG_FLAGS) $(FLAGS) $^ -o bin/$@

class_server: src/class_server.c src/linked_list.c src/utilities.c src/tcp_server.c src/udp_server.c
	gcc $(DEBUG_FLAGS) $(FLAGS) -pthread $^ -o bin/$@

clean:
	rm -rf bin/*
