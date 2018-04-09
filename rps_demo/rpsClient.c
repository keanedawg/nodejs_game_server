/***********************************************************************
* Program:
*    Lab RockClientT2, Rock/Paper/Scissors with Sockets - Client Code
*    Brother Jones, CS 460
* Author:
*    Cameron Fife
* Summary:
*    Client program for a good fun round of Rock, Paper, Scissors.
***********************************************************************
* Changes made to my code for the re-submission:
*   - Fixed some same line brackets
*   - Added comment block to main
***********************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define MAXDATASIZE 100 // max number of bytes we can get at once 

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
* line 106. The rest is just Beej's work.
*********************************************/
int main(int argc, char *argv[])
{
   int sockfd;
   int numbytes;  
   char buf[MAXDATASIZE];
   struct addrinfo hints;
   struct addrinfo *servinfo;
   struct addrinfo *p;
   int rv;
   char s[INET6_ADDRSTRLEN];

   if (argc != 3)
   {
      fprintf(stderr,"usage: client hostname port\n");
      exit(1);
   }

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;

   if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
   }

   // loop through all the results and connect to the first we can
   for (p = servinfo; p != NULL; p = p->ai_next)
   {
      if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1)
      {
         perror("client: socket");
         continue;
      }

      if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
      {
         perror("client: connect");
         close(sockfd);
         continue;
      }

      break;
   }

   if (p == NULL)
   {
      fprintf(stderr, "client: failed to connect\n");
      return 2;
   }

   inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
         s, sizeof s);
   printf("client: connecting to %s\n", s);

   freeaddrinfo(servinfo); // all done with this structure

   // Receive the initial connection message
   if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
   {
      perror("recv");
      exit(1);
   }
   buf[numbytes] = '\0';
   
   // Announce to them whether they are player 1 or 2
   printf("%s\n",buf);

   // Play the game
   char input[1];
   while (input[0] != 'q') 
   {
         if (input[0] != '\n') 
         {
               printf("Enter Input: ");
         }
         
         scanf("%c", &input);
         switch (input[0]) 
         {
               case 'r' :
               case 'p' :
               case 's' :
               {
                  if (send(sockfd, input, 2, 0) == -1)
                        perror("send");
                  printf("Message sent. Awaiting other player\'s input...\n");
                  if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1)
                  {
                        perror("recv");
                        exit(1);
                  }
                  if (numbytes == 0 || numbytes == 1) 
                  {
                        printf("Other player exitted. Have a nice day!\n", buf);
                        input[0] = 'q';
                        break;
                  }
                  buf[numbytes] = '\0';
                  printf("%s\n",buf);
                  break; 
                }
               case 'q' :
                  if (send(sockfd, input, 2, 0) == -1)
                        perror("send");
                  break;
               case '\n' :
                  break;
               default : 
               {
                  printf("Invalid Input! Try again.\n");
                  break;
               }
         }
   }

   close(sockfd);

   return 0;
}

