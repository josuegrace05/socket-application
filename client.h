#ifndef CLIENT_H
#define CLIENT_H


typedef char byte;

int connectServer(char *);

int closeConnectionClient(int);

int sendMessage(int,byte*,int);

int receiveMessage(int,byte*,int);


#endif