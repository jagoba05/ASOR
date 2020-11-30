#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc,char ** argv){
        struct utsname buf;
        int error;
        error = uname(&buf);
        if(error == -1){
                perror("uname");
                return -1;
        }
	printf("Sysname: %s \n",buf.sysname);
        printf("Nodename: %s \n",buf.nodename);
        printf("Release: %s \n",buf.release);
        printf("Version: %s \n",buf.version);
        printf("Machine: %s/n",buf.machine);
return 0;
}
