#include "connection.c"
/*
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080

typedef char byte;


struct sockaddr_in serverAddress; // struct que armazena o endereço do servidor
struct sockaddr_in clientAddress; // struct que armazena o endereço do cliente

int beServer(){
	int serverSocket = 0, clientSocket, valread;
	int opt = 1;
	int addrlen = sizeof(serverAddress);
	byte confirm;
	int length = 1024;
	byte *buffer = (byte *) malloc(sizeof(byte *) * length);
	char *hello = "Testando se o cliente recebeu essa parada";
 
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0 ){ //
		perror("Socket Failed");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORT);

	if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(serverSocket,3)<0){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if((clientSocket = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t *) &addrlen)) <0){
		perror("accept");
		exit(EXIT_FAILURE);
	}

	return clientSocket;
}


*/
int main(int argc, char const * argv[]){
	int length = 1024;
	byte *buffer = malloc(sizeof(char)*1024);
	byte *hello = "Helloooo do servidoooor";
	int sock = beServer();
	
	sendMessage(sock,hello,strlen(hello));
	
	receiveMessage(sock,buffer,length);
	printf("\n%s",buffer);

/*	

	if((valread = recv(clientSocket,&confirm,sizeof(byte),0)) < 0){
		printf("Problema no envio da mensagem");
		return(-1);
	}

	if(confirm == 1){
		printf("tentativa de comunicaçao do cliente funfando\n");
	}
	confirm = 0;
	
	//printf("%s/n", buffer);
	send(clientSocket,&confirm,sizeof(byte),0);

	//int sockfd = socket(AF_INET, SOCK_STREAM, 0); //Criando o socket
	//int setsockopt(int sockfd, int level, int optname, const void *optval, soclen_t optlen); // manipulaçao do socket
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);//Linka o socket no endereço e na porta especificada
	//int listen(int sockfd, int backlog);// coloca o server para escutar
	//int new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	printf("%s","\nHello Message Sent");
	free(buffer);
	close(clientSocket);
	close(serverSocket);
*/	
	return 0;
}