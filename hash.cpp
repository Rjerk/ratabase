#include "hash.h"
#include <cstring>
#include <sstream>

Hashtable::Hashtable(size_t sz):
    tablesz(sz), elemsz(0)
{
    table = new Hashnode*[sz];
    for (size_t i = 0; i < sz; ++i) {
        table[i] = nullptr;
    }
}

Hashtable::Hashtable():
    Hashtable(5)
{
}

Hashtable::~Hashtable()
{
	for (size_t i = 0; i < tablesz; ++i) {
    	Hashnode* entry = table[i];
        while (entry != nullptr) {
            Hashnode* prev = entry->getNext();
            entry = entry->getNext();
            delete prev;
        }
        table[i] = nullptr;
    }
    delete [] table;
}

unsigned Hashtable::hashFunc(const char* s) // fnv1a hash.
{
    unsigned hashvalue = 0x811C9DC5; // 2166136261 as seed.
    const unsigned fnv_prime = 0x01000193; // 16777619
    while (*s) {
        hashvalue = (*s++ ^ hashvalue) * fnv_prime;
    }
    return hashvalue;
}

size_t Hashtable::getSlot(const char* s)
{
	return hashFunc(s) % tablesz;
}

bool Hashtable::get(const char* key, Value& value)
{
    Hashnode* entry = table[getSlot(key)];

    while (entry != nullptr) {
        if (strcmp(entry->getKey(), key) == 0) {
            value = entry->getValue();
            return true;
        }
        entry = entry->getNext();
    }
    return false;
}

void Hashtable::put(const char* key, const Value& value)
{
	size_t index = getSlot(key);
    ++elemsz;
    Hashnode* entry = table[index];
    Hashnode* prev = nullptr;

    while (entry != nullptr && strcmp(entry->getKey(), key) != 0) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry != nullptr) {
        entry->setValue(value);
    } else {
        entry = new Hashnode(key, value);
        if (prev == nullptr) { // empty slot
            table[index] = entry;
        } else {
            prev->setNext(entry); // end of linklist.
        }
    }
}

bool Hashtable::remove(const char* key)
{
	size_t index = getSlot(key);
    Hashnode* prev = nullptr;
    Hashnode* entry = table[index];

    while (entry != nullptr && strcmp(entry->getKey(), key) != 0) {
   		prev = entry;
        entry = entry->getNext();
    }

    if (entry == nullptr) { // not found
        return false;
    } else {
        if (prev == nullptr) {// remove the element in slot
            table[index] = entry->getNext();
        } else {
            prev->setNext(entry->getNext());
        }
        delete entry;
        --elemsz;
        return true;
    }
}

string Hashtable::print() const
{
    std::ostringstream os;
    os << "{\n";
    for (size_t i = 0; i < tablesz; ++i) {
        const Hashnode* entry = table[i];
        while (entry != nullptr) {
            os << "(" << string(entry->getKey())
               << ": " << entry->getValue().getString() << ")\n";
            entry = entry->getNext();
        }
    }
    os << "}";
    return os.str();
}