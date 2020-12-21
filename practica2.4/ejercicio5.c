
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(){
  char *tuberia = "tuberia";
  mkfifo(tuberia, 0644);
  char *tuberia2 = "tuberia2";
  mkfifo(tuberia2, 0644);
  char buffer[257];

  //tuberias
  int pipe1 = open(tuberia, O_RDONLY | O_NONBLOCK);
  int pipe2 = open(tuberia2, O_RDONLY | O_NONBLOCK);
  int cambios, pipeactual;
  while (cambios != -1 ) {
    fd_set conjunto;
    FD_ZERO(&conjunto);
    FD_SET(pipe1, &conjunto);
    FD_SET(pipe2, &conjunto);
    int numpipeactual;

    cambios = select((pipe1 < pipe2) ? pipe2 + 1 : pipe1 + 1, &conjunto, NULL,NULL,NULL);

    if (cambios > 0){
      //Definimos en qué pipe nos encontramos.
      if (FD_ISSET(pipe1, &conjunto)) {
        numpipeactual = 1;
        pipeactual = pipe1;
      } else if (FD_ISSET(pipe2, &conjunto)) {
        numpipeactual = 2;
        pipeactual = pipe2;
      }

      ssize_t readsize = 256;
			while (readsize == 256) {
				readsize = read(pipeactual, buffer, 256);
				buffer[readsize] = '\0';
				printf("Tuberia %i: %s", numpipeactual, buffer);
			}


      if (readsize != 256 && numpipeactual == 1) {
        close(pipe1);
        pipe1 = open(tuberia, O_RDONLY | O_NONBLOCK);
				if (pipe1 == -1) {
					perror("No se pudo abrir la tuberia1");
					close(pipe1);
					close(pipe2);
					return -1;
				}
      } else if(readsize != 256 && numpipeactual == 2) {
        close(pipe2);
        pipe2 = open(tuberia2, O_RDONLY | O_NONBLOCK);
				if (pipe1 == -1) {
					perror("No se pudo abrir la tuberia2");
					close(pipe1);
					close(pipe2);
					return -1;
				}
      }
    }
  }
  close(pipe1);
  close(pipe2);
  return 0;
}