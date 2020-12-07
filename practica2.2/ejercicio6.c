#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	mode_t prev = umask(027); // 027

        int file = open("ejercicio6.txt", O_CREAT, 0777);

        return 0;
}
