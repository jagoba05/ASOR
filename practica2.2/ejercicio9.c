#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char **argv) {
 if(argc <2){
	printf("No hay ruta del archivo\n");
        return -1;
 }
 struct stat buff;
 int statint = stat(argv[1],&buff);
        if(statint == -1){
                printf("El directorio no existe! \n");
                return -1;
         }
printf("Minor: %li\n", (long) major(buff.st_dev));
 printf("I-nodo: %li\n",buff.st_ino);
 printf("Mode: %i\n",buff.st_mode);
 mode_t mode = buff.st_mode;
        if (S_ISLNK(mode)){
                printf("%s Es un enlace simbólico.\n", argv[1]);
        } else if (S_ISREG(mode)) {
                printf("%s Es un archivo.\n", argv[1]);
        } else if (S_ISDIR(mode)) {
                printf("%s Es un directorio.\n", argv[1]);
        }
 time_t t = buff.st_atime;
 struct tm *tm1=localtime(&t);
 printf("El ultimo acceso: %d:%d\n", tm1->tm_hour, tm1->tm_min);

 time_t t2 = buff.st_mtime;
 struct tm *tm2= localtime(&t2);
 printf("Ultimo acceso: %d:%d\n", tm2->tm_hour, tm2->tm_min);
 time_t t3 = buff.st_ctime;
printf("Minor: %li\n", (long) major(buff.st_dev));
 printf("I-nodo: %li\n",buff.st_ino);
 printf("Mode: %i\n",buff.st_mode);
 mode_t mode = buff.st_mode;
        if (S_ISLNK(mode)){
                printf("%s Es un enlace simbólico.\n", argv[1]);
        } else if (S_ISREG(mode)) {
                printf("%s Es un archivo.\n", argv[1]);
        } else if (S_ISDIR(mode)) {
                printf("%s Es un directorio.\n", argv[1]);
        }
 time_t t = buff.st_atime;
 struct tm *tm1=localtime(&t);
 printf("El ultimo acceso: %d:%d\n", tm1->tm_hour, tm1->tm_min);

 time_t t2 = buff.st_mtime;
 struct tm *tm2= localtime(&t2);
 printf("Ultimo acceso: %d:%d\n", tm2->tm_hour, tm2->tm_min);
 
 time_t t3 = buff.st_ctime;
 struct tm *tm3= localtime(&t3);
 printf("Ultimo acceso: %d:%d\n",tm3->tm_hour,tm3->tm_min);
 return -1;
}