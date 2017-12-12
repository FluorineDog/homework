#include <ctime>
#include <dirent.h>
#include <exception>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <semaphore.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <cassert>

using std::string;
using std::endl;
using std::cerr;
using std::cout;
using std::vector;

#define cout cerr
void worker(string path) {
  dirent64 **namelist;
  ssize_t count = scandir64(path.c_str(), &namelist, nullptr, alphasort64);
  if(count < 0){
    return;
  }
  // cout << "total " << count;
  cout << path << ":" << endl;
  vector<string> folder_list;
  auto setsymbols = [](char symbols[], int mode) {
    symbols++;
    if (mode & S_IRUSR == 0)
      *symbols++ = '-';
    if (mode & S_IWUSR == 0)
      *symbols++ = '-';
    if (mode & S_IXUSR == 0)
      *symbols++ = '-';

    if (mode & S_IRGRP == 0)
      *symbols++ = '-';
    if (mode & S_IWGRP == 0)
      *symbols++ = '-';
    if (mode & S_IXGRP == 0)
      *symbols++ = '-';

    if (mode & S_IROTH == 0)
      *symbols++ = '-';
    if (mode & S_IWOTH == 0)
      *symbols++ = '-';
    if (mode & S_IXOTH == 0)
      *symbols++ = '-';
  };
  auto getusername = [](struct stat64 &info) -> string {
    auto data = getpwuid(info.st_uid);
    return data->pw_name;
  };

  auto getgroupname = [](struct stat64 &info) -> string {
    auto data = getgrgid(info.st_gid);
    return data->gr_name;
  };

  auto gettimestring = [](struct stat64 &info) -> string {
    auto timestamp = info.st_mtim.tv_sec;
    string tmp = ctime(&timestamp);
    return tmp.substr(0, tmp.size() - 1);
  };

  // bool endlflag = false;
  for (size_t i = 0; i < count; ++i) {
    auto &ref = namelist[i];
    auto name = ref->d_name;
    if (name[0] == '.') {
      // start with "."
      continue;
    }
    struct stat64 info;
    auto new_path = path + "/" + name;
    int status = lstat64(new_path.c_str(), &info);
    if(status < 0){
      continue;
    }
    char symbols[] = "-rwxrwxrwx";
    setsymbols(symbols, info.st_mode);
    switch (info.st_mode & S_IFMT) {
    case S_IFREG: {
      symbols[0] = '-';
      cout << symbols << " ";
      cout << info.st_nlink << " ";
      cout << getusername(info) << " ";
      cout << getgroupname(info) << " ";
      cout << info.st_size << " ";
      cout << gettimestring(info) << " ";
      cout << name << endl;
    } break;
    case S_IFLNK: {
      symbols[0] = 'l';
      cout << symbols << " ";
      cout << info.st_nlink << " ";
      cout << getusername(info) << " ";
      cout << getgroupname(info) << " ";
      cout << info.st_size << " ";
      cout << gettimestring(info) << " ";
      cout << name << endl;
    } break;
    case S_IFDIR: {
      symbols[0] = 'd';
      cout << symbols << " ";
      cout << info.st_nlink << " ";
      cout << getusername(info) << " ";
      cout << getgroupname(info) << " ";
      cout << info.st_size << " ";
      cout << gettimestring(info) << " ";
      cout << name << endl;
      folder_list.push_back(name);
    } break;
    default:
      symbols[0] = '-';
      cout << symbols << " ";
      cout << info.st_nlink << " ";
      cout << getusername(info) << " ";
      cout << getgroupname(info) << " ";
      cout << info.st_size << " ";
      cout << gettimestring(info) << " ";
      cout << name << endl;
    }
    delete namelist[i];
  }
  delete namelist;
  for (auto name : folder_list) {
    auto new_path = path + "/" + name;
    cout << endl;
    worker(new_path);
  }
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  if (argc > 2) {
    std::cerr << "Usage ls-lR [path]";
  }
  char path[512];
  if (argc == 1) {
    strcpy(path, "/proc");
  } else {
    strncpy(path, argv[1], 512);
  }
  worker(path);
}