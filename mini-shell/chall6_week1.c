#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 50

char buffer[BUFFER_SIZE];

char *args[] = {"/usr/sbin/date", "date", NULL};
char *cmd = "date";
char *args2[] = {"date", NULL};

void exec_family(char *type) {
  if (strcmp(type, "execlp") == 0) {
    if (execlp(args[0], args[1], (char *)args[2]) == 1) {
      sprintf(buffer, "%s\n", strerror(errno));
      write(STDOUT_FILENO, buffer, strlen(buffer));
      exit(EXIT_FAILURE);
    }

  } else if (strcmp(type, "execvp") == 0) {
    if (execvp(cmd, args2) == -1) {
      sprintf(buffer, "%s\n", strerror(errno));
      write(STDOUT_FILENO, buffer, strlen(buffer));
      exit(EXIT_FAILURE);
    }

  } else if (strcmp(type, "execle") == 0) {
    if (execle(args[0], args[1], args[2]) == -1) {
      sprintf(buffer, "%s\n", strerror(errno));
      write(STDOUT_FILENO, buffer, strlen(buffer));
      exit(EXIT_FAILURE);
    }
  } else {
    write(STDOUT_FILENO, "wrong type!\n", strlen("wrong type!\n"));
  }
}
int main(int argc, char *argv[]) {

  exec_family("execle");

  return EXIT_SUCCESS;
}
