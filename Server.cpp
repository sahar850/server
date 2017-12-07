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
#include <stdexcept>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::
Server(int port) : port(port), serverSocket(0) { cout << "Server" << endl; }
void Server::start() {
    numOfClients = 0;
   /* int clientSocket1;
    int clientSocket2;*/
// Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw runtime_error ("Error on binding");
    }
// Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    puts("aaaa");
// Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    //connecting to client
    while(true) {
        connect(clientAddress, clientAddressLen);
        ClientCom();
// Close communication with the client
        stop();
        numOfClients = 0;

    }
 }


void Server::stop() {
    close(clientSocket1);
    close(clientSocket2);
}


void Server::connect (sockaddr_in &clientAddress,socklen_t &clientAddressLen) {
    while (numOfClients < MAX_CONNECTED_CLIENTS) {
// Accept a new client connection
        cout << "Waiting for client connections..." << endl;

        cout << numOfClients << endl;
        if (numOfClients == 0) {
            clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
            cout << "Client connected" << endl;
            numOfClients++;
            if (clientSocket1 == -1) {
                throw runtime_error("Error on accept client 1");
            }
        }
        cout << numOfClients << endl;
        if (numOfClients == 1) {
            clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
            cout << "Client connected" << endl;
            numOfClients++;
            if (clientSocket2 == -1) {
                throw runtime_error("Error on accept client 2");
            }
        }
    }
}


void Server::ClientCom() {
    if (numOfClients == MAX_CONNECTED_CLIENTS) {
        int i;
        //player 1
        int n = read(clientSocket1, &i, sizeof(i));
        cout << endl << "read1 " << i << endl;
        if (n == -1) {
            cout << "Error reading from socket" << endl;
        }
        i = 1;
        n = write(clientSocket1, &i, sizeof(i));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }
        //player2
        n = read(clientSocket2, &i, sizeof(i));
        cout << endl << "read2 " << i << endl;
        if (n == -1) {
            cout << "Error reading from socket" << endl;
        }
        i = 2;
        n = write(clientSocket2, &i, sizeof(i));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
        }
        n = read(clientSocket2, &i, sizeof(i));
        cout << endl << "read3 " << i << endl;
        if (n == -1) {
            cout << "Error reading from socket" << endl;
        }
    }
    while (true) {
        if (!handleClient(clientSocket1, clientSocket2)) {
            break;
        }
        if (!handleClient(clientSocket2, clientSocket1)) {
            break;
        }
    }
}


// Handle requests from a specific client
bool Server::handleClient(int clientSocket, int clientSocket2) {
    int rowCordination, colCordination;
    char op;
    // while (true) {
// Read new exercise arguments
    int n = read(clientSocket, &rowCordination, sizeof (rowCordination));

    if (n == -1) {
        cout << "Error reading rowCordination" << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    n = read(clientSocket, &colCordination, sizeof (colCordination));
    if (n == -1) {
        cout << "Error reading colCordination" << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    if(rowCordination == -2 && colCordination== -2) {
        return false;
    }
// Write the result back to the client

    n = write(clientSocket2, &rowCordination, sizeof(rowCordination));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    n = write(clientSocket2, &colCordination, sizeof(colCordination));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    return true;
}