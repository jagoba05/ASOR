#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include <sys/types.h> 
#include <sys/socket.h> 


#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <time.h>

#include <sys/select.h>


#include <unistd.h>


int main (int argc, char**argv) {


  if (argc < 2) {
    printf("Faltn argumentos \n");
    return -1;
  }

  struct addrinfo hints;
  struct addrinfo *result, *iterator;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
      printf("ERROR: Fallo al ejecutar el getaddrinfo.");
      exit(EXIT_FAILURE);
  }

  int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (bind(socketUDP, result->ai_addr, result->ai_addrlen) != 0) {
    printf("ERROR: No se ha podido ejecutar el bind.");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(result);

  char buf[2];
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];

  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);

  fd_set dflectura;
  int df = -1;

  while(1){

    while(df == -1) {
      FD_ZERO(&dflectura); 
      FD_SET(socketUDP, &dflectura); 
      FD_SET(0, &dflectura);
      df = select(socketUDP+1, &dflectura, NULL, NULL, NULL);
    }

    time_t tiempo = time(NULL);
    struct tm *tm = localtime(&tiempo);
    size_t max;
    char s[50];

    if (FD_ISSET(socketUDP,&dflectura)){
      ssize_t bytes = recvfrom(socketUDP, buf, 2, 0, (struct sockaddr *) &client_addr, &client_addrlen);

      getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
      printf("%i byte(s) de %s:%s\n", bytes, host, serv);
      buf[1] = '\0';

      if (buf[0] == 't'){
        size_t bytesT = strftime(s, max, "%I:%M:%S %p", tm);
        s[bytesT] = '\0';

        sendto(socketUDP, s, bytesT, 0, (struct sockaddr *) &client_addr, client_addrlen);

      }else if (buf[0] =='d'){
        size_t bytesT = strftime(s, max, "%Y-%m-%d", tm);
        s[bytesT] = '\0';

        sendto(socketUDP, s, bytesT, 0, (struct sockaddr *) &client_addr, client_addrlen);
      }else if (buf[0] =='q'){
        printf("Salir\n");
        exit(0);
      }else{
        printf("Error comando desconocido %d...\n", buf[0]);
      }

    } else {
      read(0, buf, 2);
      printf("%i byte(s)\n",2);
      buf[1] = '\0';

      if (buf[0] == 't'){
        size_t bytesT = strftime(s, max, "%I:%M:%S %p", tm);
        s[bytesT] = '\0';

        printf("%s\n", s);

      }else if (buf[0] =='d'){
        size_t bytesT = strftime(s, max, "%Y-%m-%d", tm);
        s[bytesT] = '\0';

        printf("%s\n", s);
      }else if (buf[0] =='q'){
        printf("Salir\n");
        exit(0);
      }else{
        printf("Error comando desconocido %d...\n", buf[0]);
      }
    }
  }

  return 0;
}