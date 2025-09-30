#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {

  char buffer[BUFFER_SIZE];  
  const char *fileName = "hello.txt";
  const char *message = "hello container";

  int fd = open(fileName, O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd < 3) {
    sprintf(buffer, "%s\n", strerror(errno));
    write(STDOUT_FILENO, buffer, strlen(buffer));
    close(fd);
    exit(EXIT_FAILURE);
  }

  write(fd, message, strlen(message));

  /*pointer at da first letter*/
  lseek(fd, 0, SEEK_SET); // pointing at "h"

  ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
  if (bytes < 0) {
    sprintf(buffer, "%s\n", strerror(errno));
    write(STDOUT_FILENO, buffer, strlen(buffer));
    close(fd);
    exit(EXIT_FAILURE);
  }

  buffer[bytes] = '\0';

  write(STDOUT_FILENO, buffer, bytes);

  close(fd);  
  
  return EXIT_SUCCESS;  
}  
