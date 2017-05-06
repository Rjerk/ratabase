#include "value.h"
#include "hash.h"
#include <utility>
#include <iostream>
#include <cstdlib>

Value::Value():
    type(COMMON), val(nullptr)
{
}

Value::~Value()
{
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
    swap(type, rhs.type);
    swap(val, rhs.val);
}

void Value::set(int type_, const cmd_v& cmd)
{
    type = type_;
    switch (type) {
        case STRING:
            setString(cmd.params.front()); break;
        case LIST:
            setList(cmd.obj_name.c_str(), cmd.params); break;
        case DICT:
            setDict(cmd.params); break;
        default:
            return ;
    }
}

void Value::setString(const string& str)
{
    val = static_cast<void*> (new string(str));
}

void Value::appString(const string& str)
{
    string s = getString() + str;
    freeValue();
    setString(s);
}

void Value::clearString()
{
    freeValue();
    setString("");
}

void Value::setList(const char* key, const vector<string>& params)
{
    List* lst = new List(string(key));
    for (auto s : params) {
        lst->push(s);
    }
    val = static_cast<void*> (lst);
    lst = nullptr;
}

string Value::printList() const
{
    List* lst = static_cast<List*>(val);
    return lst->print();
}

void Value::pushList(const string& new_elem)
{
    List* lst = static_cast<List*>(val);
    lst->push(new_elem);
}

ListNode Value::popList()
{
    List* lst = static_cast<List*>(val);
    return lst->pop();
}

size_t Value::sizeList() const
{
    List* lst = static_cast<List*>(val);
    return lst->size();
}

int Value::indexList(const string& elem) const
{
    List* lst = static_cast<List*>(val);
    return lst->index(elem);
}

void Value::putList(size_t pos, const string& elem)
{
    List* lst = static_cast<List*>(val);
    lst->put(pos, elem);
}

string Value::getList(size_t pos) const
{
    List* lst = static_cast<List*>(val);
    string s;
    if (lst->get(pos, s)) {
        return s;
    } else {
        return string();
    }
}

bool Value::deleteList(const string& elem)
{
    List* lst = static_cast<List*>(val);
    return lst->del(elem);
}

void Value::setDict(const vector<string>& params)
{
    Hashtable* dict = new Hashtable();

    for (vector<string>::const_iterator p = params.cbegin(), q = p+1;
                        p != params.cend();
                        p += 2, q += 2) {
        Value v;
        v.setString(*q);
        dict->put(p->c_str(), v);
    }

    val = static_cast<void*>(dict);
    dict = nullptr;
}

void Value::addDict(const vector<string>& params)
{
    Hashtable* dict = static_cast<Hashtable*>(val);
    for (vector<string>::const_iterator p = params.cbegin(), q = p+1;
                        p != params.cend();
                        p += 2, q += 2) {
        Value v;
        v.setString(*q);
        dict->put(p->c_str(), v);
    }
}

bool Value::deleteDict(const string& key)
{
    Hashtable* dict = static_cast<Hashtable*>(val);
    return dict->remove(key.c_str());
}

size_t Value::sizeDict() const
{
    Hashtable* dict = static_cast<Hashtable*>(val);
    return dict->size();
}

bool Value::getDict(const string& key, Value& v)
{
    Hashtable* dict = static_cast<Hashtable*>(val);
    return dict->get(key.c_str(), v);
}

string Value::printDict() const
{
    Hashtable* dict = static_cast<Hashtable*>(val);
    return dict->print();
}

void Value::freeValue()
{
    switch (type) {
        case STRING:
            delete (string*)val;
            break;
        case LIST:
            delete (List*)val;
            break;
        case DICT:
            delete (Hashtable*)val;
            break;
        default:
            break;
    }
}