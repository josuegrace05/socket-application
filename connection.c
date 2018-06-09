#include "connection.h"

#define PORT 8080

typedef char byte;


struct sockaddr_in clientAddress;
struct sockaddr_in serverAddress;


int beServer(int *serverSocket){
	int clientSocket, valread;
	int opt = 1;
	int addrlen = sizeof(serverAddress);
	byte confirm;
	int length = 1024;
	byte *buffer = (byte *) malloc(sizeof(byte *) * length);
	char *hello = "Testando se o cliente recebeu essa parada";
 
	if((*serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0 ){ //
		perror("Socket Failed");
		exit(EXIT_FAILURE);
	}
    
    if(setsockopt(*serverSocket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORT);

	if(bind(*serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if(listen(*serverSocket,3)<0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if((clientSocket = accept(*serverSocket, (struct sockaddr *)&serverAddress, (socklen_t *) &addrlen)) <0){
		perror("accept");
		exit(EXIT_FAILURE);
	}


	if((valread = recv(clientSocket,&confirm,sizeof(byte),0)) < 0){
		printf("Problema no envio da mensagem");
		return(-1);
	}

	if(confirm == 1){
		printf("Tentativa de comunicação do cliente bem sucedida\n");
	}
	confirm = 0;
	
	//printf("%s/n", buffer);
	send(clientSocket,&confirm,sizeof(byte),0);
	
	return clientSocket;

}

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

	//printf("Servidor respondendo corretamente");
	return serverSocket;
}

void closeConnection(int anySocket){
	close(anySocket);
}

int sendMessage(int serverSocket, byte *buffer, int length){
	send(serverSocket, buffer, length,0);
	return 0;
}

int receiveMessage(int serverSocket,byte *buffer, int length){
	if(recv(serverSocket,(void*)buffer,length,0) < 0){
		printf("Problema no recebimento da mensagem");
		perror("listen");
		exit(EXIT_FAILURE);
	}	
	return 0;
}
