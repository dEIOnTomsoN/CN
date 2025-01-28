#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d\n", PORT);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, 
                                          (struct sockaddr*)&client_addr, &client_len);
        if (bytes_received > 0) {
            printf("Received: %s\n", buffer);
            sendto(server_fd, buffer, bytes_received, 0, 
                   (struct sockaddr*)&client_addr, client_len);
        }
    }

    close(server_fd);
    return 0;
}
