#include <arpa/inet.h>

namespace sockets {

void connect(int sockfd, const struct sockaddr* addr);

void bindOrDie(int sockfd, const struct sockaddr* addr);

void listenOrDie(int sockfd);

int accept(int sockfd, struct sockaddr_in6* addr);

ssize_t read(int sockfd, void* buf, size_t count);

ssize_t write(int sockfd, const void* buf, size_t count);

void close(int sockfd);

void setNonBlockAndCloseOnExec(int sockfd);
}
