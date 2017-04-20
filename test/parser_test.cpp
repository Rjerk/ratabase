#include "../parser.h"
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    Parser parser;
    char* s = "create movie goodname";
    parser.addData(s, strlen(s));

    cmd_v cmd;
    parser.parse(cmd);
    cout << cmd.cmd_name << endl;
    cout << cmd.obj_name << endl;
}
