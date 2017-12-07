#include <iostream>
#include <signal.h>
#include <sstream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
int global_child_id;
int pid1;
int pid2;

#define CHECK(status_)                                                         \
  do {                                                                         \
    status = status_;                                                          \
    if (status >= 0)                                                           \
      break;                                                                   \
    cerr << "status"                                                           \
         << "***" << strerror(errno) << " at line " << __LINE__ << endl;       \
    exit(-1);                                                                  \
  } while (0)

void workload_write(int write_pipe_fd) {
  // write
  int counter = 0;
  char buf[30];
  while (true) {
    sleep(1);
    sprintf(buf, "I send you %d time(s)", ++counter);
    write(write_pipe_fd, buf, sizeof(buf));
  }
}

void workload_read(int read_pipe_fd) {
  // write
  char buf[30] = "nothing here";
  while (true) {
    int status = read(read_pipe_fd, &buf, sizeof(buf));
    CHECK(status);
    cout << buf << endl;
  }
}

void killee(int) {
  cerr << "Child Process " << global_child_id << " killed by parent" << endl;
  _exit(0);
}

void killer(int) { 
  cerr << "i'm killer" << endl;
  kill(pid1, SIGUSR1);
  kill(pid2, SIGUSR1);
  cerr << "parrent is killed";
  exit(0);
}
void deaf(int){
}

int main() {
  int pipefd[2];
  int status = pipe(pipefd);
  CHECK(status);
  pid2 = fork();
  if (pid2 == 0) {
    // in child process
    global_child_id = 2;
    signal(SIGINT, deaf);
    signal(SIGUSR1, killee);
    close(pipefd[1]); 
    workload_read(pipefd[0]);
    close(pipefd[0]);
    _exit(0);
  }

  close(pipefd[0]); 

  pid1 = fork();
  if (pid1 == 0) {
    // in child process
    global_child_id = 2;
    signal(SIGINT, deaf);
    signal(SIGUSR1, killee);
    workload_write(pipefd[1]);
    close(pipefd[1]);
    _exit(0);
  }
  close(pipefd[1]);

  signal(SIGINT, killer);
  int tmp;
  waitpid(pid1, &tmp, 0);
  waitpid(pid2, &tmp, 0);
  cerr << "dragon returning" << endl;
  return 0;
}