#include "Parser.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Logger.h"

using std::cout;
using std::endl;
using std::cerr;
using std::istringstream;

using namespace ratabase;

Parser::Parser():
    datalen_(0)
{
}

Parser::~Parser()
{
}

// add data from servbuf to buffer.
void Parser::addData(char* servbuf, const size_t len)
{
    ::memset(buffer_, char(), bufsz_);
    ::memcpy(buffer_, servbuf, len);
    datalen_ += len;
}

void Parser::writeReplyBuf(const string& str)
{
    ::memset(replybuf_, char(), bufsz_);
    ::sprintf(replybuf_, "%s", str.c_str());
}

std::string Parser::getReplyFromParser() const
{
    return std::string(replybuf_);
}

// parse command in buffer, and write parsing result to servbuf.
bool Parser::parse(cmd_v& cmd)
{
    string buf = string(buffer_);
    istringstream cmdstr(buf);
    cmd.cmd_name.clear();
    cmdstr >> cmd.cmd_name; // read command name
    cmd.obj_name.clear();
    cmdstr >> cmd.obj_name; // read object name
    string param;
    cmd.params.clear();
    while (cmdstr >> param) {
        cmd.params.push_back(param);
    }

    if (cmd_map.find(cmd.cmd_name) == cmd_map.end()) {
        string reply = "Unknown command \"" + cmd.cmd_name + "\"\n";
        writeReplyBuf(reply);
        LOG_ERROR << reply;
        return false;
    }
    cmd.type = cmd_map[cmd.cmd_name];
    switch (cmd.type) {
        case cmd_type::DISPLAY: // check 0 argument after command
            return check0(cmd);
        case cmd_type::CREATE:
        case cmd_type::SELECT:
        case cmd_type::DELETE:
        case cmd_type::SLEN:
        case cmd_type::SCLR:
        case cmd_type::LPOP:
        case cmd_type::LSIZE:
        case cmd_type::DSIZE:
            return check1(cmd); // check 1 argument after command

        case cmd_type::SSET:
        case cmd_type::SAPP:
        case cmd_type::LSET:
        case cmd_type::LPUSH:
        case cmd_type::LIDX:
        case cmd_type::LGET:
        case cmd_type::LDEL:
        case cmd_type::DGET:
        case cmd_type::DDEL:
			return check2(cmd); // check 2 arguments after command

        case cmd_type::DSET:
        case cmd_type::DADD:
			return checkMore(cmd); // check more arguments
        default:
            LOG_FATAL << "No way you come here ?!";
            return false; // never come.
    };
}

bool Parser::check0(const cmd_v& cmd)
{
    if (cmd.obj_name.size() == 0)
        return true;
    else {
        string reply = "Command \"" + cmd.cmd_name
             + "\" should have 0 parameter\n";
        writeReplyBuf(reply);
        LOG_ERROR << reply;
        return false;
    }
}

bool Parser::check1(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() == 0)
        return true;
    else {
        string reply = "Command \"" + cmd.cmd_name
             + "\" should have 1 parameter.\n";
        writeReplyBuf(reply);
        LOG_ERROR << reply;
        return false;
    }
}

bool Parser::check2(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() == 1)
        return true;
    else {
        string reply = "Command \"" + cmd.cmd_name
             + "\" should have 2 parameters.\n";
        writeReplyBuf(reply);
        LOG_ERROR << reply;
        return false;
    }
}

bool Parser::checkMore(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() > 0 &&
        cmd.params.size() % 2 == 0)
        return true;
    else {
        string reply = "Command \"" + cmd.cmd_name
             + "\" should have 4 or more parameters.\n";
        LOG_ERROR << reply;
        return false;
    }
}
