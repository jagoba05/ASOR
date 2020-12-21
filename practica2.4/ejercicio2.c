#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#define WR 1
#define RD 0

int main(int argc, char **argv)
{
    //crear las tuberias debemos controlar la salida
    int fds[2];
    int fds2[2];
    int h_p = pipe(fds);
    int p_h = pipe(fds2);
    int status;
    char buf[2048];
    char l = 'l';
    char q = 'q';
    //fork
    pid_t pid= fork();
    if(pid==0){
        read(fds[0],&buf,sizeof(char)*2048);
		printf("Hijo dice: %s\n",buf);
        write(fds2[1],&l,sizeof(char));
        sleep(1);
        int i = 0;
        while(i < 10){
            write(fds[1],"",1);
            i++;
        }
        write(fds[1],&q,1);
    }
    else{
        read(0,&buf,sizeof(char)*2048);
        write(fds[1], &buf, sizeof(char)*2048);
        read(fds2[0],&buf,sizeof(char)*2048);
		printf("Hijo dice: %s\n",buf);
        close(fds[WR]);
        close(fds2[WR]);
        close(fds[RD]);
        close(fds2[RD]);
        
    }
    return 0;
}
