#ifndef RATABASE_H
#define RATABASE_H

#include "hash.h"
#include "cmd.h"
#include <string>

using std::string;

class Ratabase {
public:
    Ratabase(const string& name);
    ~Ratabase();
    string getName() { return dbname; }
    bool operate(const cmd_v& cmd);
private:
    bool addVal(const char* key, const Value& val);
    bool getVal(const char* key, Value& val);
    bool delVal(const char* key);
    bool sset(const cmd_v& cmd);
	bool sapp(const cmd_v& cmd);
	bool slen(const cmd_v& cmd);
	bool sclr(const cmd_v& cmd);
	bool lset(const cmd_v& cmd);
	bool lpush(const cmd_v& cmd);
	bool lpop(const cmd_v& cmd);
	bool lsize(const cmd_v& cmd);
	bool lidx(const cmd_v& cmd);
	bool lput(const cmd_v& cmd);
	bool lget(const cmd_v& cmd);
	bool ldel(const cmd_v& cmd);
	bool dset(const cmd_v& cmd);
	bool dadd(const cmd_v& cmd);
	bool ddel(const cmd_v& cmd);
	bool dsize(const cmd_v& cmd);
	bool dget(const cmd_v& cmd);
private:
    string dbname;
    Hashtable* htable;
};


#endif
