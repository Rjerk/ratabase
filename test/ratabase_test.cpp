#include <iostream>
#include <cassert>
#include "../ratabase.h"

using namespace std;

int main()
{
    Value v;
    v.set(STRING, "123");

    Ratabase rb;
    rb.dbAdd("123", v);

    Value v2;
    bool ret = rb.dbGet("123", v2);
    assert(ret == true);

    ret = rb.dbDelete("123");
    assert(ret == true);

    ret = rb.dbGet("123", v);
    assert(ret == false);
}
