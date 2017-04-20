#ifndef PARSER_H
#define PARSER_H

#include <string>

using std::string;

class Parser {
public:
    Parser();
    ~Parser();
    bool parse(char* servbuf);
    void addData(char* buf, const size_t len);
private:
    char* buffer;
    size_t buflen;
    static const size_t bufsz = 100;
};

#endif
