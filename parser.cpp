#include "parser.h"
#include <cstring>
#include <cassert>

Parser::Parser():
    buflen(0)
{
    buffer = new char[bufsz];
}

Parser::~Parser()
{
    delete [] buffer;
}

// add data from servbuf to buffer.
void Parser::addData(char* servbuf, const size_t len)
{
    memset(buffer, char(), bufsz);
    memcpy(buffer, servbuf, len);
    buflen += len;
}

// parse command in buffer, and write parsing result to servbuf.
bool Parser::parse(char* servbuf)
{
    memset(servbuf, char(), buflen);
    memcpy(servbuf, buffer, buflen);
    servbuf[buflen] = '\0';
    return true;
}
