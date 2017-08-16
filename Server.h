#ifndef SERVER_H
#define SERVER_H

#include <memory>

#include "noncopyable.h"
#include "Cmd.h"

namespace ratabase {

class RatabaseManager;
class Parser;

class Server : noncopyable {
public:
    Server(int port);
    ~Server();
    void run();
private:
    void serverInit();
    bool processRequest();
    bool recvRequest();
    bool sendRespond();
    bool parseRequest();
    void dbOperate();
private:
    int port_;
    int servsock_;
    int connsock_;
    static constexpr size_t bufsz = 1024;
    std::unique_ptr<RatabaseManager> rm_;
    std::unique_ptr<Parser> parser_;
    cmd_v cmd_;
};

}
#endif
