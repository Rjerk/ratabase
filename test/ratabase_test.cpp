#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "../ratabase.h"

using namespace std;

int main()
{
    Ratabase rb("num");

    {
        cout << "string cmd test: \n";

        cmd_v sset = {
            type : cmd_type::SSET,
            cmd_name : "sset",
            obj_name : "s1",
            params : { "hello" }
        };
        cout << rb.operate(sset);

        cmd_v slen = {
            type : cmd_type::SLEN,
            cmd_name : "slen",
            obj_name : "s1",
            params : { }
        };
        cout << rb.operate(slen); // 5

        cmd_v sapp = {
            type : cmd_type::SAPP,
            cmd_name : "sapp",
            obj_name : "s1",
            params : { ", world." }
        };
        cout << rb.operate(sapp); // hello, world.

        cmd_v sclr = {
            type : cmd_type::SCLR,
            cmd_name : "sclr",
            obj_name : "s1",
            params : { }
        };
        cout << rb.operate(sclr); // ""
    }


    {
        cout << "\nlist cmd test: \n";

        cmd_v lset = {
            type : cmd_type::LSET,
            cmd_name : "lset",
            obj_name : "l1",
            params : { "hello", "good", "new" }
        };
        cout << rb.operate(lset);

        cmd_v lpush = {
            type : cmd_type::LPUSH,
            cmd_name : "lpush",
            obj_name : "l1",
            params : { "index" }
        };
        cout << rb.operate(lpush); // [hello, good, new, index]

        cmd_v lpop = {
            type : cmd_type::LPOP,
            cmd_name : "lpop",
            obj_name : "l1",
            params : { }
        };
        cout << rb.operate(lpop); // hello

        cmd_v lsize = {
            type : cmd_type::LSIZE,
            cmd_name : "lsize",
            obj_name : "l1",
            params : { }
        };
        cout << rb.operate(lsize); // 3

        cmd_v lidx = {
            type : cmd_type::LIDX,
            cmd_name : "lidx",
            obj_name : "l1",
            params : { "hello" }
        };
        cout << rb.operate(lidx); // doesn't exist.

        cmd_v lput = {
            type : cmd_type::LPUT,
            cmd_name : "lput",
            obj_name : "l1",
            params : { "1", "movie"}
        };
        cout << rb.operate(lput); // [good, movie, new, index]

        cmd_v lget = {
            type : cmd_type::LGET,
            cmd_name : "lget",
            obj_name : "l1",
            params : { "1" }
        };
        cout << rb.operate(lget); // movie

        cmd_v ldel = {
            type : cmd_type::LDEL,
            cmd_name : "ldel",
            obj_name : "l1",
            params : { "movie"}
        };
        cout << rb.operate(ldel); // [good, new, index]
    }

    {
        cout << "\ndict cmd test: \n";

        cmd_v dset = {
            type : cmd_type::DSET,
            cmd_name : "dset",
            obj_name : "d1",
            params : { "1", "first", "2", "second" }
        };
        cout << rb.operate(dset);

        cmd_v dadd = {
            type : cmd_type::DADD,
            cmd_name : "dadd",
            obj_name : "d1",
            params : { "3", "third", "4", "four" }
        };
        cout << rb.operate(dadd); // { (2: second) (3: third) (4: four) (1: first) }
        cmd_v ddel = {
            type : cmd_type::DDEL,
            cmd_name : "ddel",
            obj_name : "d1",
            params : { "1"}
        };
        cout << rb.operate(ddel); // { (2: second) (3: third) (4: four) }

        cmd_v dsize = {
            type : cmd_type::DSIZE,
            cmd_name : "dsize",
            obj_name : "d1",
            params : { }
        };
        cout << rb.operate(dsize); // 3

        cmd_v dget = {
            type : cmd_type::DGET,
            cmd_name : "dget",
            obj_name : "d1",
            params : { "3" }
        };
        cout << rb.operate(dget); // ( 3: third )
    }
}
