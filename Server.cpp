#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <utility>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>

#include "Server.h"
#include "Logger.h"
#include "RatabaseManager.h"
#include "Parser.h"
#include "Sockets.h"

using namespace ratabase;

Server::Server(int port):
    port_(port)
{
    serverInit();
    rm_ = std::unique_ptr<RatabaseManager>(new RatabaseManager());
    parser_ = std::unique_ptr<Parser>(new Parser());
    LOG_DEBUG << "ctor[" << this << "]";
}

Server::~Server()
{
    LOG_DEBUG << "dtor[" << this << "]";
    sockets::close(servsock_);
}

void Server::serverInit()
{
    if (port_ < 1024 || port_ > 65535) {
        LOG_FATAL << "Server::serverInit: Invalid port";
    }

    struct sockaddr_in servaddr;
    ::bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((servsock_ = ::socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        LOG_FATAL << "make socket error";
    }

    const int on = 1;
    ::setsockopt(servsock_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (::setsockopt(servsock_, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) == -1) {
        LOG_ERROR << "setsockopt REUSEPORT failed.";
    }

    sockets::bindOrDie(servsock_, (struct sockaddr* ) &servaddr);

    sockets::listenOrDie(servsock_);
}

void Server::run()
{
    for (int i = 1; ; ++i) {
        connsock_ = ::accept(servsock_, nullptr, nullptr);
        if (connsock_ < 0) {
            LOG_FATAL << "Server::run: accept error";
        }

        LOG_INFO << "Connect to client " << i << "";

        int ret;
        if ((ret = fork()) < 0) {
            continue;
        } else if (ret == 0) {
            while (this->processRequest())
                ;
            LOG_INFO << "Close connection to client " << i;
            sockets::close(connsock_);
        }
    }

}

bool Server::processRequest()
{
    if (recvRequest() == false) {
        LOG_ERROR << "Failed in receiving request...";
        return false;
    }

    LOG_INFO << "Recevie request, parsing request...";
    if (parseRequest() == false) {
        return true;
    }

    LOG_INFO << "Parse command finished, operating database...";
    dbOperate();

    if (sendRespond() == false) {
        LOG_ERROR << "Failed in sending respond...";
        return false;
    }

    return true;
}

bool Server::recvRequest()
{
    char buf[1024];
    ssize_t nread = sockets::read(connsock_, buf, sizeof(buf));
    if (nread > 0) {
        LOG_DEBUG << "read buffer: " << buf;
        parser_.get()->addData(buf, nread);
        return true;
    } else {
        return false;
    }
}

bool Server::sendRespond()
{
    LOG_INFO << "sending respond...";
    string msg = rm_->getMsg();
    LOG_DEBUG << "ger reply from manager: " << msg;
    LOG_INFO << "sock: " << connsock_;
    ssize_t nread = sockets::write(connsock_, msg.c_str(), msg.size());
    LOG_INFO << nread ;
    if (nread > 0) {
        LOG_DEBUG << "send buf: " << msg;
        return true;
    }
    return false;
}

bool Server::parseRequest()
{
    if (parser_.get()->parse(cmd_) == false) {
        LOG_ERROR << "Failed in parsing request. Sending error message...";
        string reply = parser_.get()->getReplyFromParser();
        sockets::write(connsock_, reply.c_str(), reply.size());
        return false;
    }
    return true;
}

void Server::dbOperate()
{
    if (rm_.get()->manageDB(cmd_) == false) {
        LOG_ERROR << "Failed in operating ratabase. Sending erorr message...";
    } else {
        LOG_ERROR << "Operating ratabase ok.";
    }
}
