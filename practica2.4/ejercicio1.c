#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define PIPE_W 1
#define PIPE_R 0

int main(int argv, char** argc){

  if (argv < 2) {
    printf("Error, faltan argumentos \n");
  }

  int fd[2];
  pipe(fd);
  switch (fork()) {
    case -1:
      perror("ERROR en  el fork");
      return 1;
      break;
    case 0:
    //Hijo
      dup2(fd[PIPE_R],0);
      close(fd[PIPE_W]);
      close(fd[PIPE_R]);
      execlp(argc[3],argc[3],argc[4]);
    break;
    default:
    //Padre
      dup2(fd[PIPE_W],1);
      close(fd[PIPE_W]);
      close(fd[PIPE_R]);
      execlp(argc[1],argc[1],argc[2]);
    break;
  }

}

