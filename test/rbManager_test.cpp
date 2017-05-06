#include "../ratabaseManager.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main()
{
    RatabaseManager manager;

    cout << "create movie" << endl;
    cmd_v create = {
        type : cmd_type::CREATE,
        cmd_name : "create",
        obj_name : "movie",
        params : { }
    };
    bool ret = manager.manageDB(create);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "select movie" << endl;
    cmd_v select = {
        type : cmd_type::SELECT,
        cmd_name : "select",
        obj_name : "movie",
        params : { }
    };
    ret = manager.manageDB(select);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "display db" << endl;
    cmd_v display = {
        type : cmd_type::DISPLAY,
        cmd_name : "",
        obj_name : "",
        params : { }
    };
    ret = manager.manageDB(display);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "delete movie" << endl;
    cmd_v delet = {
        type : cmd_type::DELETE,
        cmd_name : "delete",
        obj_name : "movie",
        params : { }
    };
    ret = manager.manageDB(delet);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "select movie" << endl;
    ret = manager.manageDB(select);
    cout << manager.getMsg() << endl;
    assert(ret == false);

    cout << "display db" << endl;
    ret = manager.manageDB(display);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "delete default_db" << endl;
    delet.obj_name = "default_db";
    ret = manager.manageDB(delet);
    cout << manager.getMsg() << endl;
    assert(ret);

    cout << "display db" << endl;
    ret = manager.manageDB(display);
    cout << manager.getMsg() << endl;
    assert(ret == false);

}
