#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv){
        struct stat s;
        if(stat(argv[0],&s)==0){
                if(s.st_mode & S_IFDIR){
                        printf("La ruta es un direcotrio\n");
                }
                else if(s.st_mode & S_IFREG){
                        int ln = link(argv[1],"archivo.hard");
                        int ln2 = symlink(argv[1],"archivo.sym");
                        printf("Hechos\n");
                }
        }
return 1;
}
