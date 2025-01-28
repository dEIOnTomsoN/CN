#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server_addr);

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connected to UDP server\n");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  

        if (strcmp(buffer, "exit") == 0)
            break;

        sendto(sock_fd, buffer, strlen(buffer), 0, 
               (struct sockaddr*)&server_addr, server_len);

        memset(buffer, 0, BUFFER_SIZE);
        recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, 
                 (struct sockaddr*)&server_addr, &server_len);
        printf("Echoed: %s\n", buffer);
    }

    close(sock_fd);
    return 0;
}
