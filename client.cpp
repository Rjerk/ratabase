#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>
#include "Sockets.h"
#include "Logger.h"
#include "Config.h"

constexpr size_t BUF_SIZE = 1024;

void error_handling(const std::string& msg);

int main(int argc, char** argv)
{
    int port = -1;
    if (argc == 1) {
        port = DEFAULT_PORT;
    } else if (argc == 2) {
        port = atoi(argv[1]);
    } else if (argc > 2) {
        std::cerr << "usage: ./client [ <port> ]\n";
        exit(0);
    }

    int sock = ::socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() error");
        exit(0);
    }

    struct sockaddr_in serv_adr;
    ::bzero(&serv_adr, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(port);

    sockets::connect(sock, (struct sockaddr*) &serv_adr);

    char message[BUF_SIZE];
    std::cout << "Welcome to use Ratabase (use 'q' or 'Q' to quit)\n";
    while (1) {
        std::cout << "Ratabase> ";
        if (fgets(message, BUF_SIZE, stdin) == NULL && ferror(stdin)) {
            perror("fgets error");
        }
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        } else if (!strcmp(message, "\n")) {
            continue;
        }
        ssize_t ret = sockets::write(sock, message, strlen(message));
        ret = ::read(sock, message, BUF_SIZE);
        if (ret < 0) {
            exit(0);
        }
        message[ret] = '\0';
        std::cout << message;
    }

    ::close(sock);
}
