//
// Created by sahar on 03/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <unistd.h>
#include <netinet/in.h>

class Server {

public:
    /**
     * constructor
     * @param port
     */
    Server(int port);
    /**
     * running the game
     */
    void start();
    /**
     * close the server socket - not in use
     */
    void stop();
    /**
     * connect players and sending 1 to first player and 2 for second
     * @param clientAddress
     * @param clientAddressLen
     */
    void connect(sockaddr_in &clientAddress,socklen_t &clientAddressLen);
    /**
     * manage the communication of two players.
     * sending to each other the chosen disc
     *  0,0 if there is no move
     *  -2,-2 if the game is over
     */
    void ClientCom();
    /**
     * sending to each other the chosen disc
     *  0,0 if there is no move
     *  -2,-2 if the game is over
     * @param clientSocket - current player
     * @param clientSocket2 - opponent player
     * @return - false if game continue and true otherwise(game over)
     */
    bool handleClient(int clientSocket, int clientSocket2) ;

private:

    int port;
    int serverSocket;
    int numOfClients;
    int clientSocket1;
    int clientSocket2;
};

#endif //SERVER_SERVER_H