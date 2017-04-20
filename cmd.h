#ifndef CMD_H
#define CMD_H

#include <string>
#include <vector>
#include <unordered_map>
using std::string;

enum class cmd_type {
    CREATE, SELECT, DELETE, DISPLAY,
    SSET,   SAPP,   SLEN,   SCLR,
    LSET,   LPUSH,  LPOP,   LSIZE,   LIDX,   LPUT,   LGET,   LDEL,
    DSET,   DADD,   DDEL,   DSIZE,   DGET
};

struct cmd_v {
    cmd_type type;
    string cmd_name;
    string obj_name;
    std::vector<string> params;
};

static std::unordered_map<string, cmd_type> cmd_map = {
    {"create", cmd_type::CREATE}, {"select", cmd_type::SELECT},
    {"delete", cmd_type::DELETE}, {"display", cmd_type::DISPLAY},

    {"sset", cmd_type::SSET},     {"sapp", cmd_type::SAPP},
    {"slen", cmd_type::SLEN},     {"sclr", cmd_type::SCLR},

    {"lset", cmd_type::LSET},     {"lpush", cmd_type::LPUSH},
    {"lsize", cmd_type::LSIZE},   {"lidx", cmd_type::LIDX},
    {"lput", cmd_type::LPUT},     {"lget", cmd_type::LGET},
    {"ldel", cmd_type::LDEL},

    {"dset", cmd_type::DSET},     {"dadd", cmd_type::DADD},
    {"ddel", cmd_type::DDEL},     {"dsize", cmd_type::DSIZE},
    {"dget", cmd_type::DGET}
};

#endif
