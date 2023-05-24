// Include once
#ifndef NETCODE_H_
#define NETCODE_H_

// Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// Network operation functions
void *serverOps(void *vargp);
void *clientOps(void *vargp);

#endif