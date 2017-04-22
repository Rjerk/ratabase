# Ratabase

a simple in-memory key-value database.

## Build

```
sh build.sh
./server &
./client
```

## Data Structure Store

ratabase supports these data structures: string, list, dictory.

- string
string consists of characters.

- list
list consists of same type elements, but only string, number, temporarily.

- dictory
dictory supports unordered, unique key, with string or number type value.

## Implement Detail

- [server.h | client.h | parser.h]

In this project, I use client-server model. Client uses command to operating databaes, server parses
the command, run and return the result to client.

- [ratabaseManager.h]

Ratabase Manager use array to store different databases, and supports
create, switch, delete, display all databases.

- [ratabase.h]

It uses hash table to store different data, and index data by searching
variable name.

- [value.h]

class Value wraps each data structure and store its type and data.

- [list.h]

As for list, I use double linked list to insert, delete elements expediently.

- [hash.h | hashnode.h]

Hash table, use separate chaing with linked lists to resolve collision.

## Operatring Command

### database

- create [db-name]

create a new database.

- select [db-name]

switch a created database.

- delete [db-name]

delete a created database.

- dispaly

display all databases' name and created time.

### string

- sset [str-name] [string]

create a string-object with string.

- sapp [str-name] [append-string]

append new string to a string-object.

- slen [str-name]

return string-object's length.

- sclr [str-name]

empty a string-object.

### list

- lset [lst-name] [new-elem]+

create a list-object with one or more elements, elements are same type.

- lpush [lst-name] [new-elem]

push a new element to list's tail.

- lpop [lst-name]

pop a element from list's head.

- lsize [lst-name]

return list-object's size.

- lidx [lst-name] [elem]

return index for a element in list.

- lput [lst-name] [index] [new-elem]

insert a new element to list in index.

- lget [lst-name] [index]

return a element at index in list.

- ldel [lst-name] [index]

delete a element at index in list.

### dict

- dset [dict-name] {[key] [value]}+

create a dictory with one or more key-value pairs.

- dadd [dict-name] {[key] [value]}+

add one or more key-value pairs to a created dictory, if key has existed, update its value.

- ddel [dict-name] [key]

delete a key-value pair in dictory.

- dsize [dict-name]

return a created dictory's size.

- dget [dict-name] [key]

return key's key-value pair.
