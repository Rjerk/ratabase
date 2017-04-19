#include "../hash.h"

#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    {
        Value v1;
        v1.set(STRING, "123");

        Hashtable htable(10);
        htable.put("123", v1);

        Value v2;
		bool ret = htable.get("123", v2);
		assert(ret == true);

		htable.remove("123");
		ret = htable.get("123", v2);
		assert(ret == false);
    }
}
