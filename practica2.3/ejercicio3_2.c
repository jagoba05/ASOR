#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char **argv) {
        if (argc != 2) {
    printf("Error, faltan argumentos\n");
    return -1;
  }

  int pid = atoi(argv[1]);
  int scheduler = sched_getscheduler(pid);

  //Planificación
  switch (scheduler) {
    case SCHED_OTHER:
      printf("SCHED: OTHER\n");
    break;
    case SCHED_FIFO:
     printf("SCHED: FIFO\n");
    break;
    case SCHED_RR:
      printf("SCHED: RR\n");
    break;
    default:
      printf("SCHED: ERROR\n");
    break;
  }
//Prioridad
  struct sched_param p;
  sched_getparam(pid,&p);
  printf("PRIORIDAD: %i\n", p.sched_priority);

  //Max y min
  int max = sched_get_priority_max(scheduler);
  int min = sched_get_priority_min(scheduler);
  printf("MAX: %i - MIN: %i\n", max, min);
  return 0;
}