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
    string operate(const cmd_v& cmd);
private:
	void setMsg(const string& str);
    void addVal(const char* key, const Value& val);
    bool getVal(const char* key, Value& val);
    bool delVal(const char* key);

    void sset(const cmd_v& cmd);
	void sapp(const cmd_v& cmd);
	void slen(const cmd_v& cmd);
	void sclr(const cmd_v& cmd);

	void lset(const cmd_v& cmd);
	void listOperate(const cmd_v& cmd);
	void lpush(Value& v, const string& s);
	void lpop(Value& v);
	void lsize(const Value& v);
	void lidx(const Value& v, const string& elem);
	void lput(Value& v, size_t pos, const string& elem);
	void lget(const Value& v, size_t pos);
	void ldel(Value& v, const string& s);

	void dset(const cmd_v& cmd);
	void dadd(const cmd_v& cmd);
	void ddel(const cmd_v& cmd);
	void dsize(const cmd_v& cmd);
	void dget(const cmd_v& cmd);
private:
    string dbname;
    Hashtable* htable;
    string msg;
};


#endif
