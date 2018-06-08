#include <stdio.h>
#include <dirent.h>

char *read_line() {
    char *string = NULL;
    char c;
    int i = 0;
    
    do {
        c = fgetc(stdin);
        string = (char *) realloc (string, sizeof(char)*(i+1));
        string[i++] = c;
    } while (c != 10);
    string[i-] = '\0';
    
    return string;
}

int main() {
    int op, i = 0, n;
    char *string;
    struct dirent *de;
    DIR *dir;
    
    printf(" --------------------------------------------\n|                                            |\n|                   SPOOF                    |\n|                                            |\n|  1 - Enviar uma playlist                   |\n|  2 - Ver suas playlists                    |\n|  3 - Ver todas as músicas                  |\n|  4 - Fazer uma playlist                    |\n|                                            |\n -------------------------------------------\n>> ");
    scanf ("%d", &op);
    switch (op) {
        case 1:
            printf("Digite o nome da playlist que deseja enviar\n>> ");
            string = read_line();
            free(string);
            break;
        case 2:
            dir = opendir("./playlists");
            
            while ((de = readdir (dir)) != NULL)
                printf("%s\n", de->d_name);
            
            closedir(dir);
            break;
        case 3:
            dir = opendir("./myMusic");
            
            while ((de = readdir (dir)) != NULL)
                printf("%s\n", de->d_name);
            
            closedir(dir);
            break;
        case 4:
            break;
    }
    
    return 0;
}
