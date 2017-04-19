#include "server.h"

Server::Server()
{
    rb = new Ratabase();
    serverInit();
}

Server::~Server()
{
}

void Server::serverInit()
{
}

void Server::run()
{
}

void Server::process()
{
}

int main(int argc, char** argv)
{
    Server server;

    server.run();

    for ( ; ; ) {
        server.process();
    }
}
