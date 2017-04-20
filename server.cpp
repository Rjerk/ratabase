#include "server.h"

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

const int DB_MAX_NUM = 10;

using std::cout;
using std::endl;
using std::cerr;

Server::Server(int port_):
    port(port_)
{
    buf = new char[bufsz];
    db = new Ratabase*[DB_MAX_NUM];
    for (size_t i = 0; i < DB_MAX_NUM; ++i) {
        db[i] = nullptr;
    }
    db[0] = new Ratabase;
}

Server::~Server()
{
    for (size_t i = 0; i < DB_MAX_NUM; ++i) {
        delete db[i];
    }
    delete [] db;
    delete [] buf;
    close(servSock);
}

void Server::serverInit()
{
    if (port < 1024 || port > 65535) {
        cerr << "Invalid port." << endl;
        return ;
    }

    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((servSock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "socket() error." << endl;
        return ;
    }

    if (bind(servSock, (struct sockaddr* ) &servAddr,
                       sizeof(servAddr)) < 0) {
        cerr << "bind() error." << endl;
        return ;
    }

    if (listen(servSock, 5) < 0) {
        cerr << "liten() error." << endl;
        return ;
    }
}

void Server::run()
{
    serverInit();
    for (int i = 1; ; ++i) {
        socklen_t len = sizeof(clntAddr);
        if ((connSock = accept(servSock,
            (struct sockaddr*) &clntAddr, &len)) < 0) {
            cerr << "accept() error." << endl;
        } else {
            cout << "---Connect to client " << i << "---\n" << endl;
        }

        int ret;
        if ((ret = fork()) < 0) {
            continue;
        } else if (ret == 0) {
            parser = new Parser();
            while (this->processRequest())
                ;
            cout << "\n---Close connection to client " << i << "---\n" << endl;
        } else
            close(connSock);

    }

}

bool Server::processRequest()
{
    if (this->recvRequest() == false) {
        cerr << "Failed receiving request." << endl;
        return false;
    }

    cout << "Receive request finished, parsing request..." << endl;
    if (this->parseRequest() == false) {
        cerr << "Failed parsing request." << endl;
    //    return false;
    }

    cout << "Parse command finished, operating database..." << endl;
    if (this->dbOperate() == false) {
        cerr << "Failed operating database." << endl;
        return false;
    }

    string s = cmd.cmd_name + " " + cmd.obj_name;
    for (string i : cmd.params)
        s += (" " + i);
    memset(buf, char(), bufsz);
    sprintf (buf, "%s", s.c_str());

    cout << "Handle request finished, sending respond..." << endl;
    if (this->sendRespond() == false) {
        cerr << "Failed send respond." << endl;
        return false;
    }
    return true;
}

bool Server::recvRequest()
{
    memset(buf, char(), bufsz);
    ssize_t nread = read(connSock, buf, bufsz);
    if (nread > 0) {
        cout << "read length: " << nread << endl;
        cout << "read buffer: " << buf;
        parser->addData(buf, nread);
        return true;
    } else {
        cerr << "Client closed the connection." << endl;
        return false;
    }
}

bool Server::sendRespond()
{
    size_t len = strlen(buf);
    ssize_t nread = write(connSock, buf, len);
    if (nread > 0) {
        cout << "send len: " << len << endl;
        cout << "send buf: " << buf << endl;
        return true;
    } else {
        cerr << "write() error." << endl;
        return false;
    }
}

bool Server::parseRequest()
{
    return parser->parse(cmd);
}

bool Server::dbOperate()
{
    return true;
}

int main(int argc, char** argv)
{
    Server* server;

    if (argc == 2)
        server = new Server(atoi(argv[1]));
    else
        server = new Server();

    server->run();

    delete server;
    return 0;
}
