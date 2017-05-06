#ifndef HASHNODE_H
#define HASHNODE_H

#include "value.h"
#include <cstddef>
#include <iostream>
#include <cstring>

class Hashnode {
public:
    Hashnode(): key(nullptr), next(nullptr) { }
    Hashnode(const char* k, const Value& v):
        key(new char[strlen(k)+1]),
        value(v),
        next(nullptr)
    {
        strncpy(key, k, strlen(k));
        key[strlen(k)] = '\0';
    }
    ~Hashnode()
    {
        delete [] key;
        value.freeValue();
    }
    Hashnode(const Hashnode&) = delete;
    Hashnode& operator=(const Hashnode&) = delete;

    const char* getKey() const { return key; }
    Value getValue() const { return value; }
    void setValue(const Value& v) { value = v; }
    Hashnode* getNext() const { return next; }
    void setNext(Hashnode* n) { next = n; }
private:
    char* key;
    Value value;
    Hashnode* next;
};

#endif
