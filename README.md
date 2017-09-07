# Ratabase

使用哈希表实现的基于内存的键值数据库

## 运行

先运行数据库服务器，默认端口为9999：

```
make
./server
```

用客户端进行访问：

```
./client
```

## 设计

可以创建，管理和删除数据库。

数据库内支持三种结构的存储：

- 字符串

ASCII 字符

- 列表

可以存储不同类型元素，如 [123, "abc"]

- 字典

存储一个或多个键值对

## 操作

### 数据库操作

创建数据库
```
create [db-name]
```

切换到某数据库
```
select [db-name]
```

删除数据库
```
delete [db-name]
```

显示数据库和创建时间
```
dispaly
```

### 字符串操作

创建一个字符串
```
sset [str-name] [string]
```

在字符串尾部添加字符
```
sapp [str-name] [append-string]
```

返回字符串长度
```
slen [str-name]
```

清除该字符串内容
```
sclr [str-name]
```

### 列表操作

创建一个列表，创建之初必须为同一类型
```
lset [lst-name] [new-elem]+
```

表尾添加元素，可以是任意类型
```
lpush [lst-name] [new-elem]
```

表头删除元素
```
lpop [lst-name]
```

返回某表的大小
```
lsize [lst-name]
```

表中寻找一个元素，返回其索引
```
lidx [lst-name] [elem]
```

在表中某位置插入元素
```
lput [lst-name] [index] [new-elem]
```

返回某位置上的元素
```
lget [lst-name] [index]
```

在表中删除删除某个元素
```
ldel [lst-name] [elem]
```

### 字典操作

创建一个或多个键值对作为字典内容
```
dset [dict-name] {[key] [value]}+
```

添加一个键值对，如果键存在，则更新它的值
```
dadd [dict-name] {[key] [value]}+
```

删除某个键值对
```
ddel [dict-name] [key]
```

返回字典大小
```
dsize [dict-name]
```

查找某个键值对
```
dget [dict-name] [key]
```

## Undo

- 支持磁盘持久化存储
- 按名称查找和打印内容
- 添加更多数据结构
