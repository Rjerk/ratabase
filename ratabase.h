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
    void addVal(const char* key, const Value& val);
    bool getVal(const char* key, Value& val);
    bool delVal(const char* key);
private:
    string dbname;
    Hashtable* htable;
};


#endif
