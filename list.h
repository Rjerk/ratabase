#ifndef LIST_H
#define LIST_H

#include <string>

using std::string;


struct ListNode {
    ListNode(): s(""), prev(nullptr), next(nullptr) {}
    ~ListNode()
    {
        prev = next = nullptr;
    }
    string s;
    struct ListNode* prev;
    struct ListNode* next;
};

class List {
public:
    List(const string& name);
    ~List();
    void push(const string& s);
    ListNode pop();
    size_t size() const { return sz; }
    size_t index(const string& s) const;
    void put(size_t pos, const string& s);
    bool get(const size_t pos, string& s);
    bool del(const string& s);
    void print();
private:
    string obj_name;
    size_t sz;
    ListNode* head;
    ListNode* tail;
};

#endif
