#include "ratabase.h"

const int HASH_TABLE_SLOT = 15;

Ratabase::Ratabase(const string& name):
    dbname(name)
{
    htable = new Hashtable(HASH_TABLE_SLOT);
}

Ratabase::~Ratabase()
{
    delete htable;
}

bool Ratabase::operate(const cmd_v& cmd)
{
	switch (cmd.type) {
		case cmd_type::SSET:
			return sset(cmd);
		case cmd_type::SAPP:
			return sapp(cmd);
		case cmd_type::SLEN:
			return slen(cmd);
		case cmd_type::SCLR:
			return sclr(cmd);
		case cmd_type::LSET:
			return lset(cmd);
		case cmd_type::LPUSH:
			return lpush(cmd);
		case cmd_type::LPOP:
			return lpop(cmd);
		case cmd_type::LSIZE:
			return lsize(cmd);
		case cmd_type::LIDX:
			return lidx(cmd);
		case cmd_type::LPUT:
			return lput(cmd);
		case cmd_type::LGET:
			return lget(cmd);
		case cmd_type::LDEL:
			return ldel(cmd);
		case cmd_type::DSET:
			return dset(cmd);
		case cmd_type::DADD:
			return dadd(cmd);
		case cmd_type::DDEL:
			return ddel(cmd);
		case cmd_type::DSIZE:
			return dsize(cmd);
		case cmd_type::DGET:
			return dget(cmd);
		default:
			return false;
	}
}

// used to insert value to hash table.
bool Ratabase::addVal(const char* key, const Value& val)
{
    htable->put(key, val);
    return true;
}

// used to fetch a value.
bool Ratabase::getVal(const char* key, Value& val)
{
    return htable->get(key, val);
}

// used to delete a value.
bool Ratabase::delVal(const char* key)
{
    return htable->remove(key);
}

bool Ratabase::sset(const cmd_v& cmd)
{
	Value v;
	v.set(STRING, cmd.params.front().c_str());
	return addVal(cmd.obj_name.c_str(), v);
}

bool Ratabase::sapp(const cmd_v& cmd)
{

}

bool Ratabase::slen(const cmd_v& cmd)
{

}

bool Ratabase::sclr(const cmd_v& cmd)
{

}

bool Ratabase::lset(const cmd_v& cmd)
{

}

bool Ratabase::lpush(const cmd_v& cmd)
{

}

bool Ratabase::lpop(const cmd_v& cmd)
{

}

bool Ratabase::lsize(const cmd_v& cmd)
{

}

bool Ratabase::lidx(const cmd_v& cmd)
{

}

bool Ratabase::lput(const cmd_v& cmd)
{

}

bool Ratabase::lget(const cmd_v& cmd)
{

}

bool Ratabase::ldel(const cmd_v& cmd)
{

}

bool Ratabase::dset(const cmd_v& cmd)
{

}

bool Ratabase::dadd(const cmd_v& cmd)
{

}

bool Ratabase::ddel(const cmd_v& cmd)
{

}

bool Ratabase::dsize(const cmd_v& cmd)
{

}

bool Ratabase::dget(const cmd_v& cmd)
{

}


