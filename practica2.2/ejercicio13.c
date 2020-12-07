#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char **argv){
    if(argc < 2){
        printf("Falta la ruta del archivo\n");
        return -1;
    }
	int fd = open(argv[1], O_CREAT | O_RDWR,0777);
    if (fd == -1){
        printf("No se ha podido crear el fichero\n");
        return -1;
    }
	int fd3 = dup2(fd,2);
    int fd2 = dup2(fd,1);
    printf("Se esta redirigiendo a %d\n",argv[1]);
    if(setuid(0)== -1){
        perror("Error");
    }
	dup2(fd2,fd);
    dup2(fd3,fd);
    return 1;
}
