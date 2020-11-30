#include <time.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
	time_t t = time(NULL);

	printf("Segundos desde el 1/1/1970: %li\n", t);

	return 0;
}