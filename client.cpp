#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const size_t BUF_SIZE = 1024;
void error_handling(const std::string& msg);

int main(int argc, char** argv)
{
    int sock;
    char* message = new char[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;
    int port = 9999;

    if (argc == 2) {
        port = atoi(argv[1]);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    while (1) {
        std::cout << "Ratabase> ";
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        str_len = write(sock, message, strlen(message));
        int recv_len = 0;
        while (recv_len < str_len) {
            int recv_cnt = read(sock, message+recv_len, BUF_SIZE-1);
            if (recv_cnt == -1)
                error_handling("read() error!");

            recv_len += recv_cnt;
        }
        message[str_len] = '\0';
        std::cout << message;
    }

    delete [] message;
    close(sock);
    return 0;
}

void error_handling(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

