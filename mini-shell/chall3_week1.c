#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 40

void run() {

  char command[20];
  char *args[20];
  
  ssize_t bytes = read(STDIN_FILENO, command, sizeof(command));
  command[bytes - 1] = '\0';
  
  char *token = strtok(command, " ");
  int i = 0;  
  
  while (token != NULL) {
    *(args + i) = token;
    i++;
    token = strtok(NULL, " ");
  }
  args[i] = NULL;

  execvp(args[0], args);  
}

int main() {

  char *message = (char *)malloc(BUFFER_SIZE * sizeof(char));

  pid_t child = fork();
  if (child >= 0) {
    switch (child) {
    case 0:
      sprintf(message, "child is running at parent %d\n: ", getppid());
      write(STDOUT_FILENO, message, strlen(message));
      run();      
      break;
    default:
      sprintf(message, "parent is running at pid %d\n: ", getpid());
      write(STDOUT_FILENO, message, strlen(message));
      wait(NULL);      
    }
  } else {
    sprintf(message, "%s", strerror(errno));
    write(STDOUT_FILENO, message, strlen(message));
    free(message);    
    exit(EXIT_FAILURE);    
  }    

  free(message);  
  
  return EXIT_SUCCESS;
}
