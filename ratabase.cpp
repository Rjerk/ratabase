#include "ratabase.h"

const int HASH_TABLE_SLOT = 15;

Ratabase::Ratabase(const string& name):
    dbname(name)
{
    htable = new Hashtable(HASH_TABLE_SLOT);
}

Ratabase::~Ratabase()
{
    delete htable;
}

bool Ratabase::operate(const cmd_v& cmd)
{
    return true;
}

// used to insert value to hash table.
void Ratabase::addVal(const char* key, const Value& val)
{
    htable->put(key, val);
}

// used to fetch a value.
bool Ratabase::getVal(const char* key, Value& val)
{
    return htable->get(key, val);
}

// used to delete a value.
bool Ratabase::delVal(const char* key)
{
    return htable->remove(key);
}



