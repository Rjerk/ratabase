#ifndef HASHNODE_H
#define HASHNODE_H

#include "value.h"
#include <cstddef>
#include <iostream>

class Hashnode {
public:
    Hashnode(): key(nullptr), next(nullptr) { }
    Hashnode(const char* k, const Value& v):
        key(k), value(v), next(nullptr) { }

    Hashnode(const Hashnode&) = delete;
    Hashnode& operator=(const Hashnode&) = delete;

    const char* getKey() const { return key;}
    Value getValue() const { return value; }
    void setValue(const Value& v) { value = v; }
    Hashnode* getNext() const { return next; }
    void setNext(Hashnode* n) { next = n; }
private:
    const char* key;
    Value value;
    Hashnode* next;
};

#endif
