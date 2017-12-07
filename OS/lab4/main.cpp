#include <iostream>
#include <semaphore.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using std::string;
using std::endl;
using std::cerr;
using std::cout;

void worker(string path) {
  struct stat64 info;
  lstat64(path.c_str(), &info);
  switch (info.st_mode & S_IFMT) {
  case S_IFREG: {
		cerr << "info of " << path << endl;
  } break;
  case S_IFLNK: {
		cerr << "link of " << path << endl;
  } break;
  case S_IFDIR: {
		auto s = opendir(path.c_str());
    dirent64** namelist;
		size_t count = scandir64(path.c_str(), &namelist, nullptr, alphasort64);
    // cout << "total " << count;
    for(size_t i = 0; i < count; ++i){
      auto &ref = namelist[i]; 
      string cur = path + "/" + ref->d_name;
      cout << path << ref->d_name << ":" << endl;
      
    }
  } break;
  default:
    cerr <<"WTF";
  }
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  if (argc > 2) {
    std::cerr << "Usage ls-lR [path]";
  }
  char path[512];
  if (argc == 1) {
		strcpy(path, ".");
  } else {
    strncpy(path, argv[1], 512);
  }
  worker(path);
}