#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(){
  for (int i = 0; i < 255; i++){
     printf("ERROR(%d): %s\n", i, strerror(i));
        }
  return 1;
}
