#ifndef RATABASE_MANAGER_H
#define RATABASE_MANAGER_H

#include "ratabase.h"
#include "cmd.h"
#include <sstream>

class RatabaseManager {
public:
    RatabaseManager();
    ~RatabaseManager();
    bool manageDB(const cmd_v& cmd);
    string getMsg() { return log.str(); }
private:
    bool createDB(const string& dbname);
    bool selectDB(const string& dbname);
    bool deleteDB(const string& dbname);
    bool displayDB() const;
    bool otherOperation(const cmd_v& cmd);
    bool searchDB(const string& dbname, size_t& id);
    void resetMsg()
    {
        msg.str(string());
        msg.clear();
    }
private:
    Ratabase** dbtable;
    Ratabase* current_db;
    size_t dbcount;
    std::ostringstream msg;
};

#endif
