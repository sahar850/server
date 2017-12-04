//
// Created by sahar on 03/12/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::
Server(int port) : port(port), serverSocket(0) { cout << "Server" << endl; }
void Server::start() {
    int numOfClients = 0;
    int clientSocket1;
    int clientSocket2;
// Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
        // Assign a local address to the socket
        struct sockaddr_in serverAddress;
        bzero((void *)&serverAddress,sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            throw "Error on binding";
        }
// Start listening to incoming connections
        listen(serverSocket, MAX_CONNECTED_CLIENTS);
// Define the client socket's structures
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen;
    while (numOfClients < MAX_CONNECTED_CLIENTS) {
// Accept a new client connection
        cout << "Waiting for client connections..." << endl;
        if(numOfClients == 0) {
            numOfClients++;
            clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
            cout << "Client connected" << endl;
            cout<<"waiting for the other player to connect";
            if (clientSocket1 == -1) {
                numOfClients--;
                //******************************************************************************
                throw "Error on accept";
            }
            int n = write(clientSocket1, &numOfClients, sizeof(numOfClients));
            if (n == -1) {
                cout << "Error writing to socket" << endl;
            }
        }

       if(numOfClients == 1){
           clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
           cout << "Client connected" << endl;
           numOfClients++;
           if (clientSocket2 == -1) {
               numOfClients--;
               //******************************************************************************
               throw "Error on accept";
           }
           int n = write(clientSocket2, &numOfClients, sizeof(numOfClients));
           if (n == -1) {
               cout << "Error writing to socket" << endl;
           }
       }

       //while()
        if (numOfClients == MAX_CONNECTED_CLIENTS) {
            handleClient(clientSocket1,clientSocket2);
            handleClient(clientSocket2,clientSocket1);
        }
// Close communication with the client
        close(clientSocket1);
        close(clientSocket2);
    }
}


// Handle requests from a specific client
void Server::handleClient(int clientSocket, int clientSocket2) {
    int cordination[2];
    //char op;
    while (true) {
// Read new exercise arguments
        int n = read(clientSocket, &cordination[0], sizeof (cordination[0]));
        if (n == -1) {
            cout << "Error reading arg1" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
      /*  n = read(clientSocket, &op, sizeof(op));
        if (n == -1) {
            cout << "Error reading operator" << endl;
            return;
        }*/
        n = read(clientSocket, &cordination[1], sizeof(cordination[1]));
        if (n == -1) {
            cout << "Error reading arg2" << endl;
            return;
        }
       // cout << "Got exercise: " << arg1 << op << arg2 << endl;
        //int result = calc(arg1, op, arg2);
// Write the result back to the client

        n = write(clientSocket2, &cordination, sizeof(cordination));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
    }
}