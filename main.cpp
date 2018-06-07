#include <string>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// envia um vetor com os nomes das músicas dentro do diretório myMusic
vector<string> sendMusicList(){
	DIR *dir;
	struct dirent *files;
	vector<string> musicList;

	// cria uma struct que navega pelos arquivos do diretório myMusic
	if ((dir = opendir ("./myMusic")) != NULL) {

	  while ((files = readdir (dir)) != NULL) {
	  	// cada arquivo é inserido no vetor de listas de música
	  	if(!strcmp(files->d_name,".") || !strcmp(files->d_name,"..")) continue;
	    musicList.push_back(files->d_name);
	  }
	  closedir (dir);
	} else {
		cout << "Could not find directory: /myMusic" << endl;
	}	

	//ordena a lista de músicas
	sort(musicList.begin(), musicList.end());
	for(string s : musicList){
		cout << s << endl;
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


int main()
{
	string input;

	cin >> input;
	requestMusic(input.c_str());
}
