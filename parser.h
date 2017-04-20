#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cassert>
#include <vector>

#include "cmd.h"

using std::string;

class Parser {
public:
    Parser();
    ~Parser();
    bool parse(cmd_v& cmd);
    void addData(char* buf, const size_t len);
private:
    bool check0(const cmd_v& cmd);
    bool check1(const cmd_v& cmd);
    bool check2(const cmd_v& cmd);
    bool checkMore(const cmd_v& cmd);
private:
    char* buffer;
    size_t buflen;
    static const size_t bufsz = 100;
};

#endif
