#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>

int main(int argc, char **argv) {
  int pid = atoi(argv[1]);
  printf("PID: %i\n", pid);
  printf("PPID: %i\n", getppid());
  printf("PPID: %i\n", getsid(pid));
  struct rlimit limit;
  if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
    perror("No se encontro los limites");
    return -1;
  }
  printf("Limite: %li\n", limit.rlim_max);

  char *path = malloc(sizeof(char)*(4096 + 1));
  char *rpath = getcwd(path, 4096 + 1);
  printf("Path: %s\n", path);
  free (path);

  return 0;
}