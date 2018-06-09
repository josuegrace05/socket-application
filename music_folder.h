#ifndef MUSIC_FOLDER_H
#define MUSIC_FOLDER_H

#include <string>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

string sendMusicList();
void requestMusic(const char*);

#endif