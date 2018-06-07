#include <stdio.h>
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

int connectServer(){
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

	if(inet_pton(AF_INET,"127.0.0.1", &serverAddress.sin_addr)<= 0){
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
		exit();
	}

	prinf("Servidor respondendo corretamente");
	return serverSocket;
}

void closeConnection(int serverSocket){
	close(serverSocket);
}

int main(int argc, char const * argv[]){
	int length = 1024;
	char *buffer = (char *) malloc(sizeof(char *) * length);
	int serverSocket;
	serverSocket = connectServer();


/*	
	send(serverSocket, buffer, strlen(buffer),0);
	printf("Hello message sent \n");
	

	if((valread = recv(serverSocket,buffer,length,0)) < 0){
		printf("Problema no recebimento da mensagem");
		return(-1);
	}
	
	if(buffer[0]== 'c'){
		printf("Servidor respondendo\n");
	}

	//valread = read(socket,buffer,1024);
	printf("%s\n", buffer);
*/
	closeConnection(serverSocket);

	return 0;
}