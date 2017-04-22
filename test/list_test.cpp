#include "../list.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
    List list("list");
    list.push("1"); // [1]
    list.push("2"); // [1, 2]
    list.print();

    cout << list.pop().s << endl; // 1
    list.print(); // [2]

    list.put(0, "3"); // [2, 3]
    list.put(2, "4"); // [2, 3, 4]
    list.print();

    cout << list.index("3") << endl;

    list.del("3"); // [2, 4]
    list.print();

    string s;
    list.get(0, s);
    cout << s << endl; // 2
    list.print(); // [2, 4]
}
