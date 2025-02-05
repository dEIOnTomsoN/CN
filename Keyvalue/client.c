#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

void start_client() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    char key_str[10];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    printf("Enter a key: ");
    scanf("%s", key_str);

    send(client_socket, key_str, strlen(key_str), 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    
    printf("Response from server: %s\n", buffer);

    close(client_socket);
}

int main() {
    start_client();
    return 0;
}

