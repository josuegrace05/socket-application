#include <stdio.h>
#include <dirent.h>

int main() {
	int op;
	struct dirent *de;
    DIR *dir;

	printf(" --------------------------------------------\n|                                            |\n|                   SPOOF                    |\n|                                            |\n|  1 - Enviar uma playlist                   |\n|  2 - Ver suas playlists                    |\n|  3 - Ver todas as músicas                  |\n|  4 - Fazer uma playlist                    |\n|                                            |\n -------------------------------------------\n>> ");
	scanf ("%d", &op);
	switch (op) {
		case 1:
           	break;
		case 2:
			dir = opendir("./playlists");

			while ((de = readdir (dir)) != NULL) {
           		printf("%s\n", de->d_name);
           	}

           	closedir(dir);
			break;
		case 3:
			dir = opendir("./musics");

			while ((de = readdir (dir)) != NULL) {
           		printf("%s\n", de->d_name);
           	}

           	closedir(dir);
			break;
		case 4:
			break;
	}

	return 0;
}