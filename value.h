#ifndef VALUE_H
#define VALUE_H

#include "common.h"

class Value {
public:
    Value();
    Value(const Value& rhs);
    ~Value();
    Value& operator=(Value rhs);
    void set(int type_, const void* val_);
    void freeValue();
private:
    void swap(Value& rhs);
public:
    int type;
    const void* val;
};

#endif
