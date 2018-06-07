#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080



int main(int argc, char const * argv[]){
	
	int sockfd, new_socket, valread;

	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";


	printf("Deu ruim");
 
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0 ){
		perror("Socket Failed");
		exit(EXIT_FAILURE);
	}

	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);


	if(bind(sockfd, (struct sockaddr *) &address, sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(sockfd,3)<0){
		perror("listen");
		exit(EXIT_FAILURE);
	}


	if((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *) &addrlen)) <0){
		perror("accept");
		exit(EXIT_FAILURE);
	}


	valread = read(new_socket,buffer,1024);
	printf("%s/n", buffer);
	send(new_socket, hello, strlen(hello),0);

	//int sockfd = socket(AF_INET, SOCK_STREAM, 0); //Criando o socket
	//int setsockopt(int sockfd, int level, int optname, const void *optval, soclen_t optlen); // manipulaçao do socket
	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);//Linka o socket no endereço e na porta especificada
	//int listen(int sockfd, int backlog);// coloca o server para escutar
	//int new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	printf("%s/n",buffer);
	return 0;
}