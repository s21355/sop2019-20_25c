/**
 * @file client.cpp
 * @author Tadeusz Pu�niakowski
 * @brief Basic client
 * @version 0.1
 * @date 2019-01-16
 *
 * @copyright Copyright (c) 2019 Tadeusz Pu�niakowski
 * @license MIT
 * 
 * Zmodyfikował Szymon Ciemny s21355 
 */

#include <netdb.h>

#include <unistd.h>

#include <string.h>

#include <stdio.h>

#include <dirent.h>

#include <sys/socket.h>

/**
 * @brief opens a connection to given host and port
 *
 * @param addr_txt
 * @param port_txt
 *
 * @return connected socket
 */

int connect_to(const char * addr_txt,
  const char * port_txt) {
  struct addrinfo hints;
  bzero((char * ) & hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; ///< IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; ///< stream socket

  struct addrinfo * addr_p;
  int err = getaddrinfo(addr_txt, port_txt, & hints, & addr_p);
  if (err) {
    fprintf(stderr, gai_strerror(err));
    return -1;
  }
  struct addrinfo * rp;
  // find first working address that we can connect to
  for (rp = addr_p; rp != NULL; rp = rp->ai_next) {
    int connected_socket =
      socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (connected_socket != -1) {
      if (connect(connected_socket, rp->ai_addr, rp->ai_addrlen) != -1) {
        freeaddrinfo(addr_p); // remember - cleanup
        return connected_socket;
      }
    }
  }
  freeaddrinfo(addr_p);
  fprintf(stderr, "could not open connection\n");
  return -1;
}

/**
 * @file server.cpp
 * @author Tadeusz Pu�niakowski
 * @brief
 * @version 0.1
 * @date 2019-01-16
 * @copyright Copyright (c) 2019 Tadeusz Pu�niakowski
 * @license MIT
 *
 * Zmodyfikował Szymon Ciemny s21355 
 */

#include <netdb.h>

#include <unistd.h>

#include <stdio.h>

#include <string.h>

#include <netdb.h>

#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <stdlib.h>
#include <signal.h>

# define MAX 100
# define PORT 9921
# define SA struct sockaddr

/**
 * @brief create listening socket
 *
 * @param success callback that receive bind-ed socket
 * @param error callback on error
 * @param server_name the address on which we should listen
 * @param port_name port on which we listen
 * @param max_queue the number of waiting connections
 */

void sendFile(int sockfd, char *name)  // Funkcja wysyłająca plik
{ 
  printf("W funkcji sendfile plik : %s \n",name);
  char buff[MAX];       // bufor
  char path[100];
  strncpy(path, "//home//share//", 100); // sciezka zp likam
  strcat(path,name); // dodanie do sciezki nazyw pliku
  printf("Pelna sciezka zadanego pliku: %s \n",path);
  // czytanie pliku
  FILE *fp;
  fp=fopen(path,"r");
           
  if( fp == NULL ){
  printf("Bład podczas otwierania pliku\n");
  return ;
  }
  while ( fgets(buff,MAX,fp) != NULL ) // do konca znakow albo konca pliku
  write(sockfd,buff,sizeof(buff));  // wysylaj dane z bufora do socketu
  fclose (fp);       // zamknij plik
  printf("Plik został wysłany \n");
}

void recvFile(int sockfd, char* name) {
  char buff[MAX]; // bufor
  char name_buff[100];
  sprintf(name_buff,"%s", name);
  FILE * fp;
  fp = fopen(name_buff, "w"); // zapisz do pliku

  if (fp == NULL) {
    printf("Bład podczas otwierania pliku\n");
    return;
  }

  while (read(sockfd, buff, MAX) > 0) {
    fprintf(fp, "%s", buff);
    printf("Bufor tekstu %s", buff);
  }

  printf("Zapisano plik \n");
  printf("Plik nazywa sie :  %s !! \n", name);
}

int listen_server(char * server_name, char * port_name, int max_queue) {
  int listening_socket;
  if (server_name == NULL)
    server_name = "0.0.0.0";
  if (port_name == NULL)
    port_name = "9921";
  if (max_queue <= 0)
    max_queue = 32;
  struct addrinfo hints;

  bzero((char * ) & hints, sizeof(struct addrinfo));

  hints.ai_family = AF_UNSPEC; ///< IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; ///< Stream socket
  hints.ai_flags = AI_PASSIVE; ///< For wildcard IP address
  hints.ai_protocol = 0; ///< Any protocol
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  struct addrinfo * result, * rp;
  int s = getaddrinfo(server_name, port_name, & hints, & result);
  if (s != 0) {
    fprintf(stderr, gai_strerror(s));
    return -1;
  }

  // try to create socket and bind it to address
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    listening_socket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (listening_socket != -1) {
      int yes = 1;
      if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, & yes,
          sizeof(yes)) == -1) {
        fprintf(stderr, "setsockopt( ... ) error\n");
        return -1;
      }
      if (bind(listening_socket, rp->ai_addr, rp->ai_addrlen) == 0) {
        freeaddrinfo(result);
        if (listen(listening_socket, max_queue) == -1) {
          fprintf(stderr, "listen error\n");
          return -1;
        }
        return listening_socket;
      }
      close(listening_socket); // didn't work, let's close socket
    }
  }
  freeaddrinfo(result);
  fprintf(stderr, "error binding adress\n");
  return -1;
}

void sos(int s, char * msg) // sos = send_over_socket
{
  write(s, msg, 100);
}

char * ros(int s, int print) // ros = read_over_socket // print 1 - pokazuj printf , print 0 = nie pokazujs
{
  char msg[100];
  char limit[100];
  strncpy(limit, "stop", 100);
  read(s, msg, 100);
  //printf("%s \n", msg);
  if (strcmp(msg, limit) != 0) {
    if (print == 1) printf("%s \n", msg);
    return strdup(msg);
  } else
    return strdup(msg);
}

/**
 * @brief function that performs accepting of connections.
 * @param listening_socket the correct listening socket
 * @param host if not NULL, then it will get the host name
 * @param ervice if not NULL, then it will get the port (service) name
 * @return connected or failed socket descriptor
 */

int do_accept(int listening_socket, char * host, char * service) {
  struct sockaddr_storage peer_addr;
  socklen_t peer_addr_len = sizeof(struct sockaddr_storage);
  int connected_socket =
    accept(listening_socket, (struct sockaddr * ) & peer_addr, & peer_addr_len);

  if (connected_socket == -1) {
    fprintf(stderr, "could not accept connection!\n");
    return connected_socket;
  } else {
    if ((host != NULL) || (service != NULL)) {
      char host_[NI_MAXHOST], service_[NI_MAXSERV];
      getnameinfo((struct sockaddr * ) & peer_addr, peer_addr_len, host_,
        NI_MAXHOST, service_, NI_MAXSERV, NI_NUMERICSERV);
      if (host != NULL)
        strcpy(host, host_);
      if (service != NULL)
        strcpy(service, service_);
    }
    return connected_socket;
  }
}


//----------------------------------------------------------SERVER----------------------------------------------------------

#ifdef __SERVER
int s; // globalna zmienna dla socketu

void sigintHandler(int sig_num) // obsluga przerwania
{ 
    signal(SIGINT, sigintHandler); // jesli ctrl+c
    printf("\n Elegancko koncze polaczenie \n"); 
    close(s); //zamknij globalny socket
    exit(0);
}

int main(int argc, char ** argv) {

signal(SIGINT, sigintHandler); // obslucha ctrl+c

while(1)
{
  // -------------------------------------- OBSLUGA LOGU
  FILE * flog;
  flog = fopen("log.txt", "w"); // zapisz do pliku

  if (flog == NULL) {
    printf("Bład podczas otwierania pliku\n");
    return;
  }

 
    
    





  int listening_socket = listen_server("*", (argc > 1) ? argv[1] : "9921", 2);
  char host[NI_MAXHOST], service[NI_MAXSERV];
  while(1){
  printf("Czekam na połączenie..\n");
   
  s = do_accept(listening_socket, host, service);
  ros(s, 1); // Odczyt nawiazania komunikacji
  fprintf(flog, "Nawizano polaczenie z %s na port= %s", host,service);
  sos(s, "Pliki możliwe do pobrania: ");
  // -------------------------------------------
  DIR * d;
  struct dirent * dir;
  d = opendir("/home/share");
  sos(s, "Katalog udostępniony : /home/share \n");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") && strcmp(dir->d_name, "") != 0) { // niepotrzebne kropki dir
        printf("%s\n", dir->d_name);

        //------------
        int dlugosc;
        char dlugosc_char[10];
        dlugosc = strlen(dir->d_name);
        sprintf(dlugosc_char, "%d", dlugosc);
        //printf("Dlugosc %d,%s", dlugosc,dlugosc_char);
        char fullname[100];
        memset(fullname, 0, sizeof fullname);
        strcat(fullname, dir->d_name);
        strcat(fullname, "[");
        strcat(fullname, dlugosc_char);
        strcat(fullname, "]");
        printf("Fullname %s", fullname);
        sos(s, fullname);
        memset(fullname, 0, sizeof fullname);

        //------------
      }
    }
    sos(s, "stop");
    closedir(d);
    int sockfd = s; 

    
    char sock_buff[100];
    while (read(s, sock_buff, 100) < 0) {}
    printf("Buffor socket: %s \n", sock_buff);
    printf("przed wyslaniem \n");
    sendFile(s,sock_buff);
    printf("po wyslaniu \n");
    
    }
  }
fclose(flog);
}
 
  return 0;
}
#endif

//----------------------------------------------------------CLIENT----------------------------------------------------------

#ifdef __CLIENT
/**
 * @brief The main function. Arguments can be [host] [port] [message to send]
 *
 * It shows how to use the connect_to function
 */

int main(int argc, char ** argv) {
  char limitx[100];
  strncpy(limitx, "stop", 100);
  char bufferx[100];
  printf("Probuuje nawiazac polaczenie \n");
  
  int s = connect_to((argc > 1) ? argv[1] : "localhost",
    (argc > 2) ? argv[2] : "9921");
  if (s > 0) {

    sos(s, "Rozpocznij program");
    ros(s, 1); // oczekuje odpowiedzi
    do {
      //for(int i=0; i<6; i++){
      strncpy(bufferx, ros(s, 0), 100);
      if (strcmp(bufferx, limitx) != 0) printf("%s \n", bufferx);
      //printf("Bufor : %s | Limit: %s \n",bufferx,limitx);
      //}
    } while (strcmp(bufferx, limitx) != 0);
    // do // oczekuje listy plikow
    printf("\nPodaj nazwe pliku ktory chcesz pobrac: \n");
    char name[100];
    fgets(name, 100, stdin);
    int len=strlen(name); 
    if(name[len-1]=='\n') name[len-1]='\0';
    printf("Rozpoczynam zadanie pobrania: %s", name);
    sos(s, name);
    recvFile(s, name);
    close(s);
    
    return 0;
  } else {
    return -1;
  }
}
#endif