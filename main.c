#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define MENU " --------------------------------------------\n|                                            |\n|                   SPOOF                    |\n|                                            |\n|  1 - Enviar uma playlist                   |\n|  2 - Ver suas playlists                    |\n|  3 - Ver todas as músicas                  |\n|  4 - Fazer uma playlist                    |\n|  5 - Menu de operações                     |\n|  6 - Sair                                  |\n|                                            |\n -------------------------------------------\n"

#define PROMPT ">> "

char *read_line() {
    char *string = NULL;
    char c;
    int i = 0;
    
    do {
        c = fgetc(stdin);
        string = (char *) realloc (string, sizeof(char)*(i+1));
        string[i++] = c;
    } while (c != 10);
    string[i-i] = '\0';
    
    return string;
}

int main() {
    int op = 0, i = 0, n;
    char *string;
    struct dirent *de;
    DIR *dir;
    
    printf(MENU);
    printf(PROMPT);
    
    do {
        scanf ("%d", &op);
        switch (op) {
            case 1:
                printf("Digite o nome da playlist que deseja enviar\n");
                printf(PROMPT);
                string = read_line();
                printf("%s\n", string);
                free(string);
                break;
            case 2:
                dir = opendir("./playlists");
                
                while ((de = readdir (dir)) != NULL)
                    printf("%s\n", de->d_name);
                
                closedir(dir);
                printf(PROMPT);
                break;
            case 3:
                dir = opendir("./myMusic");
                
                while ((de = readdir (dir)) != NULL)
                    printf("%s\n", de->d_name);
                
                closedir(dir);
                printf(PROMPT);
                break;
            case 4:
                printf(PROMPT);
                break;
            case 5:
                printf(MENU);
                printf(PROMPT);
                break;
        }
        
    } while (op != 6);
    
    return 0;
}
