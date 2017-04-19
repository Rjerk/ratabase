#ifndef SERVER_H
#define SERVER_H

#include "ratabase.h"

class Server {
public:
    Server();
    ~Server();
    void run();
    void process();
private:
    void serverInit();
    void createDb();
private:
    int servSock;
    int listenSock;
    Ratabase* rb;
};


#endif
