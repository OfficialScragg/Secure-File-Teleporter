#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 2137

int main(){
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