#include "ratabase.h"
#include "list.h"

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

string Ratabase::operate(const cmd_v& cmd)
{
	switch (cmd.type) {
		case cmd_type::SSET:
			sset(cmd); break;
		case cmd_type::SAPP:
			sapp(cmd); break;
		case cmd_type::SLEN:
			slen(cmd); break;
		case cmd_type::SCLR:
			sclr(cmd); break;
		case cmd_type::LSET:
			lset(cmd); break;
		default:
			listOperate(cmd); break;
		case cmd_type::DSET:
			dset(cmd); break;
		case cmd_type::DADD:
		case cmd_type::DDEL:
		case cmd_type::DSIZE:
		case cmd_type::DGET:
			dictOperate(cmd); break;
	}
	return msg;
}

inline void Ratabase::setMsg(const string& str)
{
	msg = str + "\n";
}

// used to insert value to hash table.
inline void Ratabase::addVal(const char* key, const Value& val)
{
    htable->put(key, val);
}

// used to fetch a value.
inline bool Ratabase::getVal(const char* key, Value& val)
{
    return htable->get(key, val);
}

// used to delete a value.
inline bool Ratabase::delVal(const char* key)
{
    return htable->remove(key);
}

void Ratabase::sset(const cmd_v& cmd)
{
	Value v;
	v.set(STRING, cmd);
	addVal(cmd.obj_name.c_str(), v);
	setMsg("sset ok.");
}

void Ratabase::sapp(const cmd_v& cmd)
{
	Value v;
	getVal(cmd.obj_name.c_str(), v);
	v.appString(cmd.params.front());
	setMsg(v.getString());
}

void Ratabase::slen(const cmd_v& cmd)
{
	Value v;
	getVal(cmd.obj_name.c_str(), v);
	setMsg(std::to_string(v.getString().size()));
}

void Ratabase::sclr(const cmd_v& cmd)
{
	Value v;
	getVal(cmd.obj_name.c_str(), v);
	v.clearString();
	setMsg("\"\"");
}

void Ratabase::lset(const cmd_v& cmd)
{
	Value v;
	v.set(LIST, cmd);
	addVal(cmd.obj_name.c_str(), v);
	setMsg("lset ok.");
}

void Ratabase::listOperate(const cmd_v& cmd)
{
	Value v;
	getVal(cmd.obj_name.c_str(), v);
	switch (cmd.type) {
		case cmd_type::LPUSH:
			lpush(v, cmd.params.front()); break;
		case cmd_type::LPOP:
			lpop(v); break;
		case cmd_type::LSIZE:
			lsize(v); break;
		case cmd_type::LIDX:
			lidx(v, cmd.params.front()); break;
		case cmd_type::LPUT:
			lput(v, (size_t)std::stoi(cmd.params.front()), cmd.params[1]); break;
		case cmd_type::LGET:
			lget(v, (size_t)std::stoi(cmd.params.front())); break;
		case cmd_type::LDEL:
			ldel(v, cmd.params.front()); break;
		default:
			break;
	}
}

void Ratabase::lpush(Value& v, const string& s)
{
	v.pushList(s);
	setMsg(v.printList());
}

void Ratabase::lpop(Value& v)
{
	ListNode node = v.popList();
	setMsg(v.printList());
}

void Ratabase::lsize(const Value& v)
{
	setMsg(std::to_string(v.sizeList()));
}

void Ratabase::lidx(const Value& v, const string& elem)
{
	int idx = v.indexList(elem);
	if (idx != -1)
		setMsg(std::to_string(idx));
	else
		setMsg(elem+" doesn't exist.");
}

void Ratabase::lput(Value& v, size_t pos, const string& elem)
{
	v.putList(pos, elem);
	setMsg(v.printList());
}

void Ratabase::lget(const Value& v, size_t pos)
{
	setMsg(v.getList(pos));
}

void Ratabase::ldel(Value& v, const string& elem)
{
	if (v.deleteList(elem))
		setMsg(v.printList());
	else
		setMsg(elem+" doesn't exist.");
}

void Ratabase::dset(const cmd_v& cmd)
{
	Value v;
	v.set(DICT, cmd);
	addVal(cmd.obj_name.c_str(), v);
	setMsg("dset ok.");
}

void Ratabase::dictOperate(const cmd_v& cmd)
{
	Value v;
	getVal(cmd.obj_name.c_str(), v);
	switch (cmd.type) {
		case cmd_type::DADD:
			dadd(v, cmd.params); break;
		case cmd_type::DDEL:
			ddel(v, cmd.params.front()); break;
		case cmd_type::DSIZE:
			dsize(v); break;
		case cmd_type::DGET:
			dget(v, cmd.params.front()); break;
		default:
			return ;
	}
}

void Ratabase::dadd(Value& v, const vector<string>& params)
{
	v.addDict(params);
	setMsg(v.printDict());
}

void Ratabase::ddel(Value& v, const string& key)
{
	if (v.deleteDict(key))
		setMsg(v.printDict());
	else
		setMsg(key+" doesn't exist.");
}

void Ratabase::dsize(const Value& v)
{
	setMsg(std::to_string(v.sizeDict()));
}

void Ratabase::dget(Value& v, const string& key)
{
	Value elem;
	if (v.getDict(key, elem)) {
		setMsg("(" + key + ", " + elem.getString() + ")");
	} else {
		setMsg(key+" doesn't exist.");
	}
}