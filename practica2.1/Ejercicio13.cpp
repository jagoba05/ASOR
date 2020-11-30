#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

int main(){
  struct timeval tini,tfin;
  gettimeofday(&tini, NULL);
  int cont =0;
  for(int i = 0; i < 1000000; i++){
        cont++;
  }
  gettimeofday(&tfin, NULL);
  double tiempo = tfin.tv_usec - tini.tv_usec;
  std::cout<<"Ha tardado : "<< tiempo<<std::endl;
  return 1;
}
