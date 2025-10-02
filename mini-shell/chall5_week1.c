#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {

  //   char buffer[BUFFER_SIZE];
  
  pid_t process_child = fork();
  if (process_child == 0) {
    printf("child is running...");
    _exit(0);
  } else if (process_child > 0) {
    printf("parent sleep 6s....");
    sleep(10);    
  }    
  
  return EXIT_SUCCESS;  
}  
