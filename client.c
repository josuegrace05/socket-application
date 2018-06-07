#include "connection.c"
/*
#include <stdio.h>
//#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

typedef char byte;

struct sockaddr_in clientAddress;
struct sockaddr_in serverAddress;

int connectServer(char *ip){
	int serverSocket = 0;
	byte confirmConnection = 1;
	byte receiveConnection;

	if((serverSocket = socket(AF_INET, SOCK_STREAM,0))< 0){
		printf("Socket Creation error");
		return -1;
	}

	memset(&serverAddress, '0', sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	//127.0.0.1
	//rodrigo 172.28.121.166

	if(inet_pton(AF_INET,ip, &serverAddress.sin_addr)<= 0){
		printf("\n Invalid Adrees");
		return -1;
	}

	if(connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
		printf("Connection Failed");
		return -1;
	}

	//envia e recebe um byte de confirmaçao para ter certeza que a conexao esta estabelecida	

	send(serverSocket, &confirmConnection,sizeof(byte),0);
	printf("Hello message sent \n");
	
	if((recv(serverSocket,&receiveConnection,sizeof(byte),0)) < 0){
		printf("Problema no recebimento da mensagem");
		return(-1);
	}
	if(receiveConnection!= 0){
		printf("Sem resposta do Servidor");
		exit(EXIT_FAILURE);
	}

	printf("Servidor respondendo corretamente");
	return serverSocket;
}

void closeConnectionClient(int serverSocket){
	close(serverSocket);
}

int sendMessage(int serverSocket, byte *buffer, int length){
	send(serverSocket, buffer, strlen(buffer),0);
	return 0;
}

int receiveMessage(int serverSocket, int lenght, byte *buffer){
	if(recv(serverSocket,buffer,length,0) < 0){
		printf("Problema no recebimento da mensagem");
		return(-1);
	}	
	return 0;
}
*/

int main(){
	char *ip = "127.0.0.1";
	byte *hello = "Helloooo do cliente";
	char *buffer = malloc(sizeof(char) * 1024);
	int sock = connectServer(ip);
	receiveMessage(sock,buffer,1024);

	sendMessage(sock,hello,strlen(hello));
	printf("%s", buffer);

	return 0;
}