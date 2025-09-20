#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 50

int main() {

  char buffer[BUFFER_SIZE];
  pid_t child = fork();

  if (child == 0) {
    sprintf(buffer, "child pid: %d, ppid is: %d\n", getpid(), getppid());
    write(STDOUT_FILENO, buffer, sizeof(buffer));
  } else if (child > 0) {
    sprintf(buffer, "parent ppid is: %d\n", getpid());
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    wait(NULL);
  } else {
    sprintf(buffer, "%d", errno);
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;  
}  
