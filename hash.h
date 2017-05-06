#ifndef HASH_H
#define HASH_H

#include "hashnode.h"
#include <cstddef>

class Hashtable {
public:
    Hashtable();
    Hashtable(size_t sz);
    ~Hashtable();
    Hashtable(const Hashtable&) = delete;
    Hashtable& operator=(const Hashtable&) = delete;
	unsigned hashFunc(const char* s);
	size_t getSlot(const char* s);
    bool get(const char* key, Value& value);
    void put(const char* key, const Value& value);
    bool remove(const char* key);
    size_t size() const { return elemsz; }
    string print() const;
private:
	size_t tablesz;
    size_t elemsz;
    Hashnode** table;
};

#endif
