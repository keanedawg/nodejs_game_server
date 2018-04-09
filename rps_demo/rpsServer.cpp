/***********************************************************************
* Program:
*    Lab RockSrv, Rock/Paper/Scissors with Sockets - Server Code
*    Brother Jones, CS 460
* Author:
*    Christian Rahman
* Summary:
*    Server program for the rock/paper/scissors game.
************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

using namespace std;

/***********************************************************************
 * This will be the main driver of the server
************************************************************************/
int main(int argc, char *argv[])
{
   // Get the port number
   int port = atoi(argv[1]);
   char outputMessage[128];

   // Setup the socket
   sockaddr_in serverAddress;
   bzero((char*)&serverAddress, sizeof(serverAddress));
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
   serverAddress.sin_port = htons(port);

   // Connect to socket
   int serverCon = socket(AF_INET, SOCK_STREAM, 0);
   if(serverCon < 0)
   {
      cerr << "Error establishing the server socket connection." << endl;
      exit(0);
   }
   // Bind the socket to its local address
   int bindStatus = bind(serverCon, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
   if(bindStatus < 0)
   {
      cerr << "Error binding socket to local address." << endl;
      exit(0);
   }
   cout << "Players are readying up!..." << endl;

   // Listen for up to 2 requests at a time
   listen(serverCon, 2);
   
   sockaddr_in newSocketAddress;
   socklen_t newSocketAddressSize = sizeof(newSocketAddress);

   // Set up player 1 socket
   int player1Socket = accept(serverCon, (sockaddr *)&newSocketAddress, &newSocketAddressSize);
   if(player1Socket < 0)
   {
      cerr << "Error setting up socket from player 1.";
      exit(1);
   }
  
   // Tell player 1 that they are player 1
   string prompt = "You are Player Alpha!";
   memset(&outputMessage, 0, sizeof(outputMessage));  
   strcpy(outputMessage, prompt.c_str());
   send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
   cout << "Player 1 is connected.\nWaiting for connection with player 2...\n";

   // Set up player 2 socket
   int player2Socket = accept(serverCon, (sockaddr *)&newSocketAddress, &newSocketAddressSize);
   if(player2Socket < 0)
   {
      cerr << "Error setting up socket from player 2.";
      exit(1);
   }
   // Tell player 2 they are player 2
   prompt = "You are Player Omega!";
   memset(&outputMessage, 0, sizeof(outputMessage));  
   strcpy(outputMessage, prompt.c_str());
   send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
   cout << "Player 2 is connected\nAlpha vs. Omega, Begin!\n";

   // This is the game loop
   while(1)
   {
      cout << "Waiting for player 1 to choose\n";
      
      // Send player 1 to choose rps
      memset(&outputMessage, 0, sizeof(outputMessage)); 
      string data = "ready";
      strcpy(outputMessage, data.c_str());
      send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
      
      // Recieve player 1's weapon
      memset(&outputMessage, 0, sizeof(outputMessage));
      recv(player1Socket, (char*)&outputMessage, sizeof(outputMessage), 0);
      // Quit the game if player 1 is quitting
      if(!strcmp(outputMessage, "quit"))
      {
         cout << "Player Alpha has quit\n";
         
         // Tell player 2 to quit the game
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "quit";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         break;
      }
      
      // Store player 1's weapon
      string p1Weapon = outputMessage;

      cout << "Waiting for player 2 to choose\n";
      
      // Send player 2 to choose rps
      memset(&outputMessage, 0, sizeof(outputMessage)); 
      data = "ready";
      strcpy(outputMessage, data.c_str());
      send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
      // Recieve player 2's weapon
      memset(&outputMessage, 0, sizeof(outputMessage));
      recv(player2Socket, (char*)&outputMessage, sizeof(outputMessage), 0);
      
      // Quit the game if player 2 is quitting
      if(!strcmp(outputMessage, "quit"))
      {
         cout << "Player Omega has quit\n";
         
         // Tell player 1 to quit the game
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "quit";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         break;
      }
      
      // Store player 2's weapon
      string p2Weapon = outputMessage;
      
      // Game Rules
      if(p1Weapon == p2Weapon)
      {
         memset(&outputMessage, 0, sizeof(outputMessage));  
         data = "Both players used the same weapon. Tie game!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "The players tied.\n";
      }
      else if (p1Weapon == "r" && p2Weapon == "p")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose paper! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose rock! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 2 wins!\n";
      }
      else if (p1Weapon == "r" && p2Weapon == "s")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose scissors! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose rock! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 1 wins!\n";
      }
      else if (p1Weapon == "p" && p2Weapon == "r")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose rock! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose paper! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 1 wins!\n";
      }
      else if (p1Weapon == "p" && p2Weapon == "s")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose scissors! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose paper! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 2 wins!\n";
      }
      else if (p1Weapon == "s" && p2Weapon == "r")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose rock! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose scissors! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 2 wins!\n";
      }
      else if (p1Weapon == "s" && p2Weapon == "p")
      {
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Omega chose paper! You are the winner!";
         strcpy(outputMessage, data.c_str());
         send(player1Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         memset(&outputMessage, 0, sizeof(outputMessage)); 
         data = "Player Alpha chose scissors! You are the loser!";
         strcpy(outputMessage, data.c_str());
         send(player2Socket, (char*)&outputMessage, strlen(outputMessage), 0);
         cout << "Player 1 wins!\n";
      }

      // Get the readys
      memset(&outputMessage, 0, sizeof(outputMessage));
      recv(player2Socket, (char*)&outputMessage, sizeof(outputMessage), 0);
      memset(&outputMessage, 0, sizeof(outputMessage));
      recv(player1Socket, (char*)&outputMessage, sizeof(outputMessage), 0);
         
   }
   
   // Close the sockets
   close(player1Socket);
   close(player2Socket);
   close(serverCon);

   return 0;
}