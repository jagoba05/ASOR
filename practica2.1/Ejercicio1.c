#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc,char ** argv){
        if(setuid(0) == -1){
                perror("Error en setuid");
        }
return 1;
}
