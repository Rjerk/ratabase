#include "value.h"
#include <utility>
#include <iostream>
#include <cstdlib>

Value::Value():
    type(COMMON), val(nullptr)
{
}

Value::~Value()
{
    freeValue();
}

Value::Value(const Value& rhs)
{
    type = rhs.type;
    val = rhs.val;
}

Value& Value::operator=(Value rhs)
{
    this->swap(rhs);
    return *this;
}

void Value::swap(Value& rhs)
{
    using std::swap;
    std::swap(type, rhs.type);
    std::swap(val, rhs.val);
}

void Value::set(int type_, const void* val_)
{
    val = val_;
    type = type_;
    return ;
}

void Value::freeValue()
{
    switch (type) {
        case STRING:
            break;
        case LIST:
            break;
        case DICT:
            break;
        default:
            break;
    }
}


