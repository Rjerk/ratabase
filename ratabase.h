#ifndef RATABASE_H
#define RATABASE_H

#include "hash.h"

class Ratabase {
public:
    Ratabase();
    ~Ratabase();
    void dbAdd(const char* key, const Value& val);
    bool dbGet(const char* key, Value& val);
    bool dbDelete(const char* key);
private:
    Hashtable* htable; // pimp
};


#endif
