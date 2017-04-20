#ifndef SERVER_H
#define SERVER_H

#include "ratabase.h"
#include "parser.h"
#include <memory>
#include <arpa/inet.h>
#include <sys/socket.h>

class Server {
public:
    Server(int port_ = 9999);
    ~Server();
    void run();
    bool processRequest();
private:
    void serverInit();
    bool recvRequest();
    bool sendRespond();
    bool parseRequest();
    bool dbOperate();
    void createDb();
private:
    int servSock;
    int connSock;
    int port;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    char* buf;
    static const size_t bufsz = 1024;
    Ratabase** db;
    Parser* parser;
    cmd_v cmd;
};


#endif
