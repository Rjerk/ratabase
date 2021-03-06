#ifndef VALUE_H
#define VALUE_H

#include "Common.h"
#include "Cmd.h"
#include "List.h"

using std::vector;

class Value {
public:
    Value();
    Value(const Value& rhs);
    ~Value();
    Value& operator=(Value rhs);
    void set(int type_, const cmd_v& cmd);

    string getString() const { return *(string*)val; }
    void appString(const string& str);
    void clearString();

    string printList() const;
    void pushList(const string& new_elem);
    ListNode popList();
    size_t sizeList() const;
    int indexList(const string& elem) const;
    void putList(size_t pos, const string& elem);
    string getList(size_t pos) const;
    bool deleteList(const string& elem);

    void addDict(const vector<string>& params);
    bool deleteDict(const string& key);
    size_t sizeDict() const;
    bool getDict(const string& key, Value& v);
    string printDict() const;

    void freeValue();
private:
    void swap(Value& rhs);
    void setString(const string& s);
    void setList(const char* key, const vector<string>& params);
    void setDict(const vector<string>& params);
public:
    int type;
    void* val;
};

#endif
