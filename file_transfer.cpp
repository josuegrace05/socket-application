#include <string>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


int main()
{
	std::ifstream ifs ("myMusic/teste.mp3", std::ifstream::in);
	std::ofstream ofs ("myMusic/teste_out.mp3", std::ofstream::out); 

	char c = ifs.get();

	while(ifs.good()){
		ofs.put(c);
		std:: cout << c;
		c = ifs.get();
	}

	ifs.close();
	ofs.close();

	return 0;
}
