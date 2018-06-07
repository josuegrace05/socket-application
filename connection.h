#ifndef CONNECTION_H
#define CONNECTION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


typedef char byte;

int connectServer(char *);
int beServer();
void closeConnection(int);
int sendMessage(int,byte*,int);
int receiveMessage(int,byte*,int);


#endif