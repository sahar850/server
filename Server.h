//
// Created by sahar on 03/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <unistd.h>
#include <netinet/in.h>

class Server {

public:
    Server(int port);
    void start();
    void stop();
    void connect(sockaddr_in &clientAddress,socklen_t &clientAddressLen);
    void ClientCom();

private:
    bool handleClient(int clientSocket, int clientSocket2) ;
    int port;
    int serverSocket;
    int numOfClients;
    int clientSocket1;
    int clientSocket2;
};

#endif //SERVER_SERVER_H