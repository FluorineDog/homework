#include <atomic>
#include <iostream>
#include <semaphore.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using std::endl;
using std::cout;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "usage ./cp src dest" << endl;
    return 0;
  }
  constexpr size_t BLOCKS = 16;
  constexpr size_t BLOCK_LENGTH = 1 * 1024 * 1024;

  auto size_holder =
      (size_t *)mmap(nullptr, sizeof(size_t) * 10, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  auto sem_holder =
      (sem_t *)mmap(nullptr, sizeof(sem_t) * 2, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  auto buffer =
      (char *)mmap(nullptr, BLOCKS * BLOCK_LENGTH, PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  sem_t *empty_sem = sem_holder;
  sem_t *full_sem = sem_holder + 1;
  sem_init(empty_sem, 1, BLOCKS);
  sem_init(full_sem, 1, 0);
  // size_t total_size;
  // {
  //   struct stat64 info_buf;
  //   stat64(argv[1], &info_buf);
  //   total_size = info_buf.st_size;
  // }

  pid_t child_pid = fork();
  if (child_pid == 0) {
    // reader
    auto rf = fopen(argv[1], "rb");
    int index = 0;
    while (true) {
      sem_wait(empty_sem);
      auto nread = fread(buffer + index * BLOCK_LENGTH, 1, BLOCK_LENGTH, rf);
			size_holder[index] = nread;
      sem_post(full_sem);
			if(nread == 0){
				break;
			}
      index++;
      index %= BLOCKS;
    }
    fclose(rf);
  } else {
    // receiver
    auto wf = fopen(argv[2], "wb");
    int index = 0;
    while (true) {
      sem_wait(full_sem);
			auto nread = size_holder[index];
			if(nread == 0){
				break;
			}
      fwrite(buffer + index * BLOCK_LENGTH, 1, nread, wf);
      sem_post(empty_sem);
      index++;
      index %= BLOCKS;
    }
    fclose(wf);
  }
	sem_destroy(full_sem);
	sem_destroy(empty_sem);
  munmap(size_holder, sizeof(size_t) * BLOCKS);
  munmap(sem_holder, sizeof(sem_t) * 2);
  munmap(buffer, BLOCKS * BLOCK_LENGTH);
}
