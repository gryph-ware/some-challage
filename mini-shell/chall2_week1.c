#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

char buffer[50];

int main() {

  pid_t child = fork();
  char *args[] = {"/bin/ls", "-l", NULL};

  if (child == 0) {    
    sprintf(buffer, "child is running at pid: %d ppid: %d\n", getpid(),
            getppid());
    write(STDOUT_FILENO, buffer, strlen(buffer));
    if (execv(args[0], args) < 0) {
      sprintf(buffer, "%s\n", strerror(errno));
      write(STDOUT_FILENO, buffer, strlen(buffer));
      exit(EXIT_FAILURE);
    }
  } else if (child > 0) {
    sprintf(buffer, "parent is waiting pid: %d\n", getpid());
    write(STDOUT_FILENO, buffer, strlen(buffer));
    wait(NULL);
  } else {
    sprintf(buffer, "%s", strerror(errno));
    write(STDOUT_FILENO, buffer, strlen(buffer));
    exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;  
}  
