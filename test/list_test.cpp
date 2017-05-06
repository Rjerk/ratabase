#include "../list.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
    List list("list");
    list.push("1"); // [1]
    list.push("2"); // [1, 2]
    cout << list.print() << endl;

    cout << list.pop().s << endl; // 1
    cout << list.print() << endl; // [2]

    list.put(0, "3"); // [3, 2]
    list.put(2, "4"); // [3, 2, 4]
    cout << list.print() << endl;

    cout << list.index("3") << endl; // 0

    list.del("3"); // [2, 4]
    cout << list.print() << endl;

    string s;
    list.get(0, s);
    cout << s << endl; // 2
    cout << list.print() << endl; // [2, 4]
}
