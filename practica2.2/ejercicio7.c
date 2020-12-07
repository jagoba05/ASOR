#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	mode_t antes = umask(027);
    int file = open("ejercicio7.txt", O_CREAT, 0777);
    mode_t mas = umask(antes);
    printf("Ultima : %i\n", mas);
    return 1;
}
