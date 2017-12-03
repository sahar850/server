//
// Created by sahar on 03/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


class server {
public:
    server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket;

    int calc(int arg1, const char op,int arg2)const;
};


#endif //SERVER_SERVER_H
