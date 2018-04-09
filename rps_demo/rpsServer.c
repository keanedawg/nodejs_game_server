/***********************************************************************
* Program:
*    Lab RockSrvT2, Rock/Paper/Scissors with Sockets - Server Code
*    Brother Jones, CS 460
* Author:
*    Cameron Fife
* Summary:
*    Server program that handles all the game logic between two clients
*    in Rock Paper Scissors.
************************************************************************
* Changes made to my code for the re-submission:
*    - Fixes some styling issues (indentation and same-line brackets)
*    - Added a main comment block
************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <stdbool.h>
//  #include <signal.h>

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

#define MAXDATASIZE 40

int winnersMatrix[256][256]; // This is pretty space innefficient but I'm lazy


/* 
Setup the matrix:
   -1 = Player 1 wins
   -0 = tie (Everyone's a winner!)
    1 = Player 2 wins 
*/
void setupMatrix() 
{
      winnersMatrix['r']['s'] = -1;
      winnersMatrix['r']['r'] = 0;
      winnersMatrix['r']['p'] = 1;
      winnersMatrix['p']['r'] = -1;
      winnersMatrix['p']['p'] = 0;
      winnersMatrix['p']['s'] = 1;
      winnersMatrix['s']['p'] = -1;
      winnersMatrix['s']['s'] = 0;
      winnersMatrix['s']['r'] = 1;
}



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
   if (sa->sa_family == AF_INET)
   {
      return &(((struct sockaddr_in*)sa)->sin_addr);
   }

   return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


/********************************************
* Main handles nearly all logic.
* This code is based heavily on the Beej 
* samples given. My code really begins at 
* line 161. The rest is just Beej's work.
*
* The logic that I handle is to set up two 
* separate connections to the server and 
* then handle game logic.
*********************************************/
int main(int argc, char *argv[])
{
   int sockfd;      // listen on sock_fd
   int new_fd;      // new connection on new_fd
   int player_1 = -1;    
   int player_2 = -1;  
   struct addrinfo hints;
   struct addrinfo *servinfo;
   struct addrinfo *p;
   struct sockaddr_storage their_addr; // connector's address information
   socklen_t sin_size;
   //struct sigaction sa;
   int yes=1;
   char s[INET6_ADDRSTRLEN];
   int rv;

   char buf[MAXDATASIZE];

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE; // use my IP

   if (argc != 2)
   {
      fprintf(stderr,"usage: server port\n");
      exit(1);
   }

   if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
   }

   // loop through all the results and bind to the first we can
   for(p = servinfo; p != NULL; p = p->ai_next)
   {
      if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1)
      {
         perror("server: socket");
         continue;
      }

      if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
            sizeof(int)) == -1)
      {
         perror("setsockopt");
         exit(1);
      }

      if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
      {
         close(sockfd);
         perror("server: bind");
         continue;
      }

      break;
   }

   freeaddrinfo(servinfo); // all done with this structure

   if (p == NULL)
   {
      fprintf(stderr, "server: failed to bind\n");
      exit(1);
   }

   if (listen(sockfd, BACKLOG) == -1)
   {
      perror("listen");
      exit(1);
   }

   printf("server: waiting for connections...\n");
   
   while(player_1 < 0)    // main accept() loop
   {
      sin_size = sizeof their_addr;
      player_1 = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
      if (player_1 == -1)
      {
         perror("accept");
         continue;
      }

      inet_ntop(their_addr.ss_family,
         get_in_addr((struct sockaddr *)&their_addr),
         s, sizeof s);
      printf("server: got connection from %s\n", s);

      if (send(player_1, "Cameron's server: You are player 1! You will go first.", 54, 0) == -1)
         perror("send");
   }

   while(player_2 < 0)    // main accept() loop
   {
      sin_size = sizeof their_addr;
      player_2 = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
      if (player_2 == -1)
      {
         perror("accept");
         continue;
      }

      inet_ntop(their_addr.ss_family,
         get_in_addr((struct sockaddr *)&their_addr),
         s, sizeof s);
      printf("server: got connection from %s\n", s);

      if (send(player_2, "Cameron's server: You are player 2. The game may commence!", 58, 0) == -1)
         perror("send");
   }

   bool isPlayerOnesTurn = true;
   char playerOnePlays = ' ';
   char playerTwoPlays = ' ';
   int numbytes;

   setupMatrix();

   while(1)    // Play the game
   {
      if (isPlayerOnesTurn) 
      {
            if ((numbytes = recv(player_1, buf, MAXDATASIZE-1, 0)) == -1)
            {
                  perror("recv");
                  exit(1);
            }
            buf[numbytes] = '\0';
            if (buf[0] == 'q') 
            {
                  printf("Player 1 exitted\n");
                  if (send(player_2, "q", 1, 0) == -1)
                        perror("send");
                  break;
            }
            playerOnePlays = buf[0];
            printf("Player 1 inputted: %c\n", buf[0]);
      }
      else {
            if ((numbytes = recv(player_2, buf, MAXDATASIZE-1, 0)) == -1)
            {
                  perror("recv");
                  exit(1);
            }
            buf[numbytes] = '\0';
            if (buf[0] == 'q') 
            {
                  printf("Player 2 exitted\n");
                  if (send(player_1, "q", 1, 0) == -1)
                        perror("send");
                  break;
            }
            playerTwoPlays = buf[0];
            printf("Player 2 inputted: %c\n", buf[0]);

            switch (winnersMatrix[playerOnePlays][playerTwoPlays]) 
            {
                  case -1:
                        if (send(player_1, "You won!", 8, 0) == -1)
                              perror("send");
                        if (send(player_2, "Complete and utter loser!", 25, 0) == -1)
                              perror("send");
                        printf("Player 1 wins!\n");
                        break;
                  case 1:
                        if (send(player_1, "Complete and utter loser!", 25, 0) == -1)
                              perror("send");
                        if (send(player_2, "You won!", 8, 0) == -1)
                              perror("send");
                        printf("Player 2 wins!\n");
                        break;
                  default:
                        // a tie
                        if (send(player_1, "We're all winners on this blessed day!", 38, 0) == -1)
                              perror("send");
                        if (send(player_2, "We're all winners on this blessed day!", 38, 0) == -1)
                              perror("send");
                        printf("We're all winners on this blessed day!\n");
                        break;
            }
      }
      isPlayerOnesTurn = !isPlayerOnesTurn;
   }
   
   
   close(player_1);
   close(player_2);

   return 0;
}

