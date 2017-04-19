#include "ratabase.h"

const int HASH_TABLE_SLOT = 15;

Ratabase::Ratabase()
{
    htable = new Hashtable(HASH_TABLE_SLOT);
}

Ratabase::~Ratabase()
{
    delete htable;
}

// used to insert value to hash table.
void Ratabase::dbAdd(const char* key, const Value& val)
{
    htable->put(key, val);
}

// used to fetch a value.
bool Ratabase::dbGet(const char* key, Value& val)
{
    return htable->get(key, val);
}

// used to delete a value.
bool Ratabase::dbDelete(const char* key)
{
    return htable->remove(key);
}



