#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
//El directorio usado es el que nos encontramos /
int main(int argc,char ** argv){
        printf("Numero máximo de enlaces: %li\n", pathconf("/",_PC_LINK_MAX));
        printf("Tamaño máximo de una ruta: %li\n", pathconf("/",_PC_PATH_MAX));
        printf("Longitud máxima de nombre de ficheros: %li\n", pathconf("/",_PC_NAME_MAX));
        return 0;
}
