#include "parser.h"
#include <cstring>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
using std::istringstream;

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
bool Parser::parse(cmd_v& cmd)
{
    string buf = string(buffer);
    istringstream cmdstr(buf);

    cmdstr >> cmd.cmd_name; // read command name
    cmdstr >> cmd.obj_name; // read object name
    string param;
    while (cmdstr >> param)
        cmd.params.push_back(param);

    switch (cmd_map[cmd.cmd_name]) {
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
			cerr << "Command \"" << cmd.cmd_name << "\" not found" << endl;
			return false;
    };
}

bool Parser::check0(const cmd_v& cmd)
{
    if (cmd.obj_name.size() == 0)
        return true;
    else {
        cerr << "Command \"" << cmd.cmd_name
             << "\" should have 0 parameter" << endl;
        return false;
    }
}

bool Parser::check1(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() == 0)
        return true;
    else {
        cerr << "Command \"" << cmd.cmd_name
             << "\" should have 1 parameter." << endl;
        return false;
    }
}

bool Parser::check2(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() == 1)
        return true;
    else {
        cerr << "Command \"" << cmd.cmd_name
             << "\" should have 2 parameters." << endl;
        return false;
    }
}

bool Parser::checkMore(const cmd_v& cmd)
{
    if (cmd.obj_name.size() != 0 && cmd.params.size() > 0 &&
        cmd.params.size() % 2 == 0)
        return true;
    else {
        cerr << "Command \"" << cmd.cmd_name
             << "\" should have 4 or more parameters." << endl;
        return false;
    }
}
