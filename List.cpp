#include "List.h"
#include <iostream>
#include <sstream>

List::List(const string& name):
    obj_name(name), sz(0), head(nullptr), tail(nullptr)
{
}

List::~List()
{
    while (head != tail) {
        head = head->next;
        delete head->prev;
    }
    delete tail;
}

void List::push(const string& s)
{
    ListNode* node = new ListNode();
    node->s = s;
    if (sz == 0) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        node = nullptr;
    }
    ++sz;
}

ListNode List::pop()
{
    ListNode* node = head;
    if (sz == 0) {
        return ListNode();
    } else if (sz == 1){
        head = tail = nullptr;
        --sz;
        return *node;
    } else {
        head = head->next;
        node->next = nullptr;
        head->prev = nullptr;
        --sz;
        return *node;
    }
}

int List::index(const string& s) const
{
    ListNode* p = head;
    size_t i = 0;
    while (p->next != nullptr) {
        if (p->s == s) {
            return (int)i;
        }
        ++i;
        p = p->next;
    }
    return -1;
}

void List::put(size_t pos, const string& s)
{
    ListNode* newnode = new ListNode();
    newnode->s = s;
    if (pos > sz)
        pos = sz;
    if (pos == sz)
        push(s);
    else if (pos == 0) {
        head->prev = newnode;
        newnode->next = head;
        head = newnode;
    } else {
        ListNode* p = head;
        size_t i = 0;
        while (p->next != nullptr) {
            if (i != pos) {
                ++i;
                p = p->next;
            } else {
            	break;
			}
        }
        p->prev->next = newnode;
        newnode->prev = p->prev;
        p->prev = newnode;
        newnode->next = p;
    }
    newnode = nullptr;
    ++sz;
}

bool List::get(const size_t pos, string& s)
{
    if (pos >= sz)
        return false;

    ListNode* p = head;
    size_t i = 0;
    while (p->next != nullptr) {
        if (i == pos) {
            s = p->s;
            break;
        } else {
            p = p->next;
            ++i;
        }
    }
    return true;
}

bool List::del(const string& s)
{
    size_t pos;
    if ((pos = index(s)) != size_t(-1)) {
        if (pos == 0) {
            pop();
            return true;
        } else if (pos == sz-1) {
            if (sz == 1) {
                delete tail;
                head = tail = nullptr;
            } else {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            }
        } else {
            ListNode* p = head;
            while (p->next != nullptr) {
                if (p->s == s)
                    break;
                else
                	p = p->next;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
        }
        --sz;
        return true;
    } else {
        return false;
    }
}

string List::print()
{
    std::ostringstream os;
    ListNode* p = head;
    if (p == nullptr)
        os << "[]" << std::endl;

    os << "[";
    while (p != nullptr && p->next != nullptr) {
        os << p->s << ", ";
        p = p->next;
    }
    os << p->s << "]";
    return os.str();
}
