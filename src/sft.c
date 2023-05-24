// Author: OfficialScragg
// Date: 24/05/2023
// Peer-to-Peer file transfer application.

// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// Custom headers
#include "crypto.h"
#include "file-ops.h"
#include "netcode.h"

// Constants
#define PORT 2137

// Controller
int main(int argc, char const* argv[]){
    // Setup server and client threads
    pthread_t srv_id, cli_id;
    printf("Server starting...\n");
    pthread_create(&srv_id, NULL, serverOps, NULL);
    printf("Server up.\n");
    pthread_create(&cli_id, NULL, clientOps, NULL);
    pthread_join(cli_id, NULL);
    return 0;
}