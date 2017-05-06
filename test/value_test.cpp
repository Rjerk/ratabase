#include "../value.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    Value v;
    v.set(STRING, vector<string>{"123"});
    cout << v.getString() << endl;

    return 0;
}
