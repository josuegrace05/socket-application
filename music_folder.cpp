#include "music_folder.h"

// envia um vetor com os nomes das músicas dentro do diretório myMusic
string sendMusicList(){
	DIR *dir;
	struct dirent *files;
	vector<string> musicVector;
	string musicList = "";

	// cria uma struct que navega pelos arquivos do diretório myMusic
	if ((dir = opendir ("./myMusic")) != NULL) {

	  while ((files = readdir (dir)) != NULL) {
	  	// cada arquivo é inserido no vetor de listas de música
	  	if(!strcmp(files->d_name,".") || !strcmp(files->d_name,"..")) continue;
	    musicVector.push_back(files->d_name);
	  }
	  closedir (dir);
	} else {
		cout << "Could not find directory: /myMusic" << endl;
	}	

	//ordena a lista de músicas
	sort(musicVector.begin(), musicVector.end());

	for(string s : musicVector){
		musicList.append(s + "\n");
	}

	return musicList;
}

void requestMusic(const char* musicRequest){
	DIR *dir;
	struct dirent *files;
	ifstream musicFile;

	// cria uma struct que navega pelos arquivos do diretório myMusic
	if ((dir = opendir ("./myMusic")) != NULL) {

	  while ((files = readdir (dir)) != NULL) {
	  	if(!strcmp(files->d_name,".") || !strcmp(files->d_name,"..")) continue;
	  	if(!strcmp(files->d_name, musicRequest)){
	  		musicFile.open(files->d_name, ifstream::in);
	  		cout << musicFile.is_open() << endl;
	  		break;
	  	}
	  }
	  closedir (dir);
	} else {
		cout << "Could not find directory: /myMusic" << endl;
	}	

	if(musicFile.is_open()){
		cout << "File found" << endl;
	}else{
		cout << "Could not find requested music" << endl;
	}
}
