#ifndef PARSER_H
#define PARSER_H

#include "Cmd.h"
#include "noncopyable.h"

namespace ratabase {

class Parser : noncopyable {
public:
    Parser();
    ~Parser();
    bool parse(cmd_v& cmd);
    void addData(char* buf, const size_t len);
    std::string getReplyFromParser() const;
private:
    bool check0(const cmd_v& cmd);
    bool check1(const cmd_v& cmd);
    bool check2(const cmd_v& cmd);
    bool checkMore(const cmd_v& cmd);
    void writeReplyBuf(const string& str);
private:
    size_t datalen_;
    static constexpr size_t bufsz_ = 100;
    char buffer_[bufsz_];
    char replybuf_[bufsz_];
};

}

#endif
