#include "Sockets.h"
#include "Logger.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

void sockets::setNonBlockAndCloseOnExec(int sockfd)
{
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags = flags | O_NONBLOCK;
    if ((::fcntl(sockfd, F_SETFL, flags)) == -1) {
        LOG_ERROR << "setNonBlockAndCloseOnExec: fcntl error - set O_NONBLOCK";
    }

    flags = ::fcntl(sockfd, F_GETFL, 0);
    flags |= FD_CLOEXEC;
    if (::fcntl(sockfd, F_SETFL, flags) == -1) {
        LOG_ERROR << "setNonBlockAndCloseOnExec: fcntl error - set FD_CLOEXEC";
    }
}

void sockets::connect(int sockfd, const struct sockaddr* addr)
{
    if (::connect(sockfd, addr,
            static_cast<socklen_t>(sizeof(struct sockaddr_in6))) == -1) {
        LOG_FATAL << "sockets::connect" << strerror(errno);
    }
}

void sockets::bindOrDie(int sockfd, const struct sockaddr* addr)
{
    if (::bind(sockfd, addr,
                static_cast<socklen_t>(sizeof(struct sockaddr_in6))) < 0) {
        LOG_FATAL << "sockets::bindOrDie";
    }
}

void sockets::listenOrDie(int sockfd)
{
    if (::listen(sockfd, SOMAXCONN) < 0) {
        LOG_FATAL << "sockets::listenOrDie";
    }
}

int sockets::accept(int sockfd, struct sockaddr_in6* addr)
{
    socklen_t addrlen = static_cast<socklen_t>(sizeof(*addr));
    int connfd = ::accept(sockfd,
            static_cast<struct sockaddr*>((void*)addr), &addrlen);
    setNonBlockAndCloseOnExec(connfd);
    if (connfd < 0) {
        auto saved_errno = errno;
        LOG_ERROR << "sockets::accept";
        switch (saved_errno) {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO:
            case EPERM:
            case EMFILE:
                errno = saved_errno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                LOG_FATAL << "unexpected error of ::accpet: "
                          << saved_errno << ::strerror(saved_errno);
                break;
            default:
                LOG_FATAL << "unknown error of ::accept: " << saved_errno;
                break;
        }
    }
    return connfd;
}

void sockets::close(int sockfd)
{
    if (::close(sockfd) == -1) {
        LOG_ERROR << "sockets::close";
    }
}

ssize_t sockets::read(int sockfd, void* buf, size_t count)
{
    ssize_t n;
    if ((n = ::read(sockfd, buf, count)) == -1) {
        LOG_ERROR << "sockets::read";
    }
    return n;
}

ssize_t sockets::write(int sockfd, const void* buf, size_t count)
{
    ssize_t n;
    if ((n = ::write(sockfd, buf, count)) == -1) {
        LOG_ERROR << "sockets::write";
    }
    return n;
}
