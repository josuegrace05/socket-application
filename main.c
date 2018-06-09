#include <stdio.h>
#include "connection.c"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MENU " --------------------------------------------\n|                                            |\n|                   SPOOF                    |\n|                                            |\n|  1 - Enviar uma playlist                   |\n|  2 - Ver suas playlists                    |\n|  3 - Ver suas as músicas                   |\n|  4 - Fazer uma playlist                    |\n|                                            |\n|  5 - Menu de operações                     |\n|  6 - Se tornar Servidor                    |\n|  7 - Se tornar Cliente                     |\n|  8 - Sair                                  |\n|                                            |\n -------------------------------------------\n"

#define PROMPT ">> "

// função de leitura de string do stdin
char *read_line() {
    int i = 0;
    char c;
    char *string = NULL;
    
    fgetc(stdin);
    
    do {
        scanf("%c", &c);
        string = (char *) realloc(string, sizeof(char)*(i+1));
        string[i++] = c;
    } while (c != 10);
    string[i-1] = '\0';
    
    return string;
}

int main() {
    int op = 0, i = 0, count = 0, n, m = 99;
    char *ip;
    int serverSocket, clientSocket;
    int *array = NULL;
    char *string, *new;
    struct dirent *de;
    DIR *dir;
    FILE *fp;
    
    printf(MENU); // interface do menu
    
    do {
        printf(PROMPT); // prompt do usuário para receber comandos
        scanf ("%d", &op);
        switch (op) {
            case 1:
                printf("Digite o nome da playlist que deseja enviar\n");
                printf(PROMPT);
                
                string = read_line();
                // enviar para o cliente o arquivo
                free(string);
                break;
            case 2: // imprimi todas as playlists do diretório
                dir = opendir("./playlists");
                
                while ((de = readdir (dir)) != NULL)
                    printf("%s\n", de->d_name);
                
                closedir(dir);
                break;
            case 3: // imprimi todas as músicas do diretório
                dir = opendir("./myMusic");
                
                while ((de = readdir (dir)) != NULL)
                    printf("%s\n", de->d_name);
                
                closedir(dir);
                break;
            case 4: // lê o nome da nova playlist e cria ela no dir ./playlists, adicionando as músicas desejadas
                printf("Digite o nome da playlist que deseja criar\n");
                printf(PROMPT);
                 
                string = read_line();
                new = (char *) malloc(sizeof(char)*(strlen(string)+12));
                memcpy(new, "./playlists/", sizeof(char)*12);
                strcat(new,string);
                printf("%s\n", new);
    
                fp = fopen(new, "w+");
                
                printf("Liste as músicas que deseja adicionar a playlist, quando terminar digite 0\n");
                
                dir = opendir("./myMusic");
                
                count = 0;
                while ((de = readdir (dir)) != NULL) { // imprimi a lista de músicas para escolha
                    printf("%d: %s\n", count+1, de->d_name);
                    count++;
                }
                
                array = (int *) calloc(count,sizeof(int));
                while (m != 0) { // marca as músicas que serão adicionadas
                    printf(PROMPT);
                    scanf("%d", &m);
                    if (m != 0) array[m-1] = 1;
                }
                
                closedir(dir);
                dir = opendir("./myMusic");
                
                count = 0;
                while ((de = readdir (dir)) != NULL) { // adiciona no .txt apenas as músicas marcadas
                    if (array[count] == 1)
                        fprintf(fp, "%s\n", de->d_name);
                    count++;
                }
                
                printf("Playlist criada com sucesso\n");
                
                closedir(dir);
                fclose(fp);
                free(string);
                free(new);
                break;
            case 5:
                printf(MENU);
                break;
            case 6:
                clientSocket = beServer(&serverSocket);
                break;
            case 7:
                printf("Digite o IP do servidor\n");
                printf(PROMPT);
                ip = read_line();
                serverSocket = connectServer(ip);
                break;
        }
        
    } while (op != 8);
    
    return 0;
}
