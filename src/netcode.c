#include "netcode.h"

// Constants
#define PORT 2137

// Server Operations
void *serverOps(void *vargp){
    // Locals
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* banner = "-- Secure File Teleporter v0.1 --\n";
    char* msg = "";

    // Setup server socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socker File Descriptor failure.");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Socket failed to bind.");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd, 3) < 0){
        perror("Failed to listen.");
        exit(EXIT_FAILURE);
    }
    if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
        perror("Failed to accept connection.");
        exit(EXIT_FAILURE);
    }
    
    // Network operations
    send(new_socket, banner, strlen(banner), 0);
    printf("Banner sent.\n");
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);

    // Closing socket
    close(new_socket);
    shutdown(server_fd, SHUT_RDWR);
}

void *clientOps(void *vargp){
    // Locals
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* msg = "Hello, World!\n";
    char buffer[1024] = { 0 };
    
    // Setup client socket
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\nFailed to create client socket.\n");
        return NULL;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        printf("\nInvalid address/Address not supported.\n");
        return NULL;
    }
    if((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))){
        printf("\nStill raining.");
        return NULL;
    }

    // Network operations
    valread = read(client_fd, buffer, 1024);
    printf("%s\n", buffer);
    send(client_fd, msg, strlen(msg), 0);
    printf("Client message sent.\n");
    
    // Close connection
    close(client_fd);
    return 0;
}