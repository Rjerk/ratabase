#include "ratabaseManager.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

const size_t DB_NUM_MAX = 10;

RatabaseManager::RatabaseManager()
{
    dbtable = new Ratabase*[DB_NUM_MAX];
    for (size_t i = 0; i < DB_NUM_MAX; ++i)
        dbtable[i] = nullptr;
    dbtable[0] = new Ratabase("default_db");
    dbcount = 1;
    current_db = dbtable[0];
}

RatabaseManager::~RatabaseManager()
{
    for (size_t i = 0; i < DB_NUM_MAX; ++i) {
        if (dbtable[i] != nullptr)
            delete dbtable[i];
    }
    delete [] dbtable;
}

bool RatabaseManager::manageDB(const cmd_v& cmd)
{
    string dbname = cmd.obj_name;
    switch (cmd.type) {
        case cmd_type::CREATE:
            return createDB(dbname);
        case cmd_type::SELECT:
            return selectDB(dbname);
        case cmd_type::DELETE:
            return deleteDB(dbname);
        case cmd_type::DISPLAY:
            return displayDB();
        default:
            return otherOperation(cmd);
    }
}

bool RatabaseManager::createDB(const string& dbname)
{
    size_t id;
    if (searchDB(dbname, id)) {
        cerr << "\"" << dbname << "\"[" << id << "] have existed." << endl;
        return false;
    }
    if (dbcount == DB_NUM_MAX) {
        cerr << "The Number of databases limited in "
             << DB_NUM_MAX << "."<< endl;
        return false;
    }
    dbtable[dbcount] = new Ratabase(dbname);
    current_db = dbtable[dbcount];
    ++dbcount;
    return true;
}

bool RatabaseManager::selectDB(const string& dbname)
{
    size_t id;
    if (searchDB(dbname, id)) {
        current_db = dbtable[id];
        return true;
    } else {
        cerr << "\"" << dbname << "\" doesn't exist." << endl;
        return false;
    }
}

bool RatabaseManager::deleteDB(const string& dbname)
{
    size_t id;
    if (searchDB(dbname, id)) {
        if (current_db == dbtable[id])
            current_db = dbtable[0];
        delete dbtable[id];
        dbtable[id] = nullptr;
        --dbcount;
        return true;
    } else {
        cerr << "\"" << dbname << "\" doesn't exist." << endl;
        return false;
    }
}

bool RatabaseManager::displayDB() const
{
    if (dbcount == 0) {
        cerr << "There is no database, use 'create [db-name]' build a new one." << endl;
        return false;
    } else {
        cout << "db count: " << dbcount << endl;
        cout << "[id]  db-name " << endl;
        for (size_t i = 0; i < dbcount; ++i) {
            cout << "[ " << i << "]"
                 << "  " << dbtable[i]->getName() << endl;
        }
        return true;
    }
}

bool RatabaseManager::otherOperation(const cmd_v& cmd)
{
    if (current_db == nullptr) {
        cerr << "Select or create a database to use." << endl;
        return false;
    }
    return current_db->operate(cmd);
}

bool RatabaseManager::searchDB(const string& dbname, size_t& id)
{
    for (size_t i = 0; i < dbcount; ++i) {
        if (dbtable[i] != nullptr && dbtable[i]->getName() == dbname) {
            id = i;
            return true;
        }
    }
    id = -1;
    return false;
}
