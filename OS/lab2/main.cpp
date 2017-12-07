#include <atomic>
#include <iostream>
#include <semaphore.h>
#include <signal.h>
#include <sstream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using std::endl;
using std::cout;
constexpr int N = 100;

int main() {
  sem_t sem_full;
  sem_init(&sem_full, 2, 0);

  sem_t sem_empty;
  sem_init(&sem_empty, 2, 1);

  volatile int sum = 0;
  std::thread go([&] {
    for (int i = 1; i < N + 1; ++i) {
      sem_wait(&sem_empty);
      sum += i;
      sem_post(&sem_full);
    }
  });
  for (int i = 1; i < N+1 ; ++i) {
    sem_wait(&sem_full);
    cout << i << "-->" << sum << std::endl;
    sem_post(&sem_empty);
  }
  go.join();
  sem_destroy(&sem_full);
  sem_destroy(&sem_empty);
  return 0;
}