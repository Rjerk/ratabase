# Ratabase

a simple in-memory key-value database.

## Build

```
make
./server
```

run client.

```
./client
```

## Data Structure Store

ratabase supports these data structures: string, list, dictory.

- string

string consists of characters.

- list

list consists of different elements, such as [123, "abc"].

- dictory
dictory supports unordered, unique key, with string or number type value.

## Implement Detail

- [server.h | client.h | parser.h]

In this project, I use client-server model. Client uses command to operating databaes, server parses the command, run and return the result to client.

- [ratabaseManager.h]

Ratabase Manager use array to store different databases, and supports create, switch, delete, display all databases.

- [ratabase.h]

It uses hash table to store different data, and index data by searching variable name.

- [value.h]

class Value wraps each data structure and store its type and data.

- [list.h]

As for list, I use double linked list to insert, delete elements expediently.

- [hash.h | hashnode.h]

Hash table, use separate chaing with linked lists to resolve collision.

## Operatring Command

### database

create a new database.
```
create [db-name]
```

switch a created database.
```
select [db-name]
```

delete a created database.
```
delete [db-name]
```

display all databases' name and created time.
```
dispaly
```

### string

create a string-object with string.
```
sset [str-name] [string]
```

append new string to a string-object.
```
sapp [str-name] [append-string]
```

return string-object's length.
```
slen [str-name]
```

empty a string-object.
```
sclr [str-name]
```

### list

create a list-object with one or more elements, elements are same type.
```
lset [lst-name] [new-elem]+
```

push a new element to list's tail.
```
lpush [lst-name] [new-elem]
```

pop a element from list's head.
```
lpop [lst-name]
```

return list-object's size.
```
lsize [lst-name]
```

return index for a element in list.
```
lidx [lst-name] [elem]
```

insert a new element to list in index.
```
lput [lst-name] [index] [new-elem]
```

return a element at index in list.
```
lget [lst-name] [index]
```

delete a element in list.
```
ldel [lst-name] [elem]
```

### dict

create a dictory with one or more key-value pairs.
```
dset [dict-name] {[key] [value]}+
```

add one or more key-value pairs to a created dictory, if key has existed, update its value.
```
dadd [dict-name] {[key] [value]}+
```

delete a key-value pair in dictory.
```
ddel [dict-name] [key]
```

return a created dictory's size.
```
dsize [dict-name]
```

return key's key-value pair.
```
dget [dict-name] [key]
```

## Undo

- support on-disk persistent key-value store.
- add more command and data structure.
- fix bugs in ./test.
