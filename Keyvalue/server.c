#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

void start_server() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int key_value_store[5] = {1, 2, 3, 4, 5};
    char *values[5] = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    if (listen(server_socket, 1) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server is waiting for a connection...\n");

    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Connection failed");
        exit(1);
    }

    recv(client_socket, buffer, sizeof(buffer), 0);
    int key = atoi(buffer);
    int found = 0;
    for (int i = 0; i < 5; i++) {
        if (key_value_store[i] == key) {
            send(client_socket, values[i], strlen(values[i]), 0);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        send(client_socket, "Key not found", 14, 0);
    }

    close(client_socket);
    close(server_socket);
}

int main() {
    start_server();
    return 0;
}
