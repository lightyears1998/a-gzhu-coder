## 概念

row, record, table, database

DBMS Database Management System
DBA

redundance 冗余
integrity 完整性

Normal Formate 范式

- 1NF 第一范式 每个字段的原子性
- 2NF 第二范式 每列与主键相关，即其他字段依赖于主键
- 3NF 第三范式 每列与主键**直接相关**

SQL

1. DML *Data Manipulation Language* 数据操作语言 插入、删除和修改数据库中的数据
2. DDL *Data Definiton Language* 数据定义语言 建立数据库，定义字段等
3. DQL *Data Query Language* 数据查询语言 查询数据等
4. DCL *Data Control Language* 数据控制语言 控制数据库组件的存取权限等

系统数据库、用户数据库

- information_schema
- performance_schema
- mysql
- test..

默认字符集是latin1（西欧语言），默认字符集是latin1_swedish_ci；可更改为utf8, utf8_general_ci。

## 指令

`mysql -u root -p`

`SELECT VERSION(), USER()` 查看版本和登陆用户名

编码问题临时解决

```shell
SET NAMES gbk;
# 相当于下面三条语句
SET character_set_client=gbk;
SET character_set_results=gbk;
SET character_set_connection=gbk;
```

修改默认编码 `/etc/my.cnf`

`HELP contents`
`SHOW ENGINES`
`SHOW VARIABLES LIKE 'storage_engine'`

## 数据类型和运算符

- *=* 赋值 / 等于（关系比较符）
- *<\>* *!=*（非标准） 不等于

数值数据类型

- [TINY | SMALL | MEDIUM ]INT[(M)] 有符号，分别占用1、2、3和4字节储存，其中M表示显示宽度，与实际占用的空间大小无关
- FLOAT(M), DOUBLE(M, D), DECIMAL(M, D)
- CHAR(M), VARCHAR(M), TINYTEXT, TEXT
- DATE, DATETIME, TIME, TIMESTAMP, YEAR

`NOW()`的类型是`DATETIME`

`CURRENT_TIMESTAMP`

如果不指定CHAR的宽度，默认值是灾难性的1。

## DDL

### 操作数据库

- `SHOW DATABASES;`
- `USE 数据库名;`
- `CREATE DATABASE 数据库名;`
- `DROP DATABASE 数据库名;`

### 操作数据表

“//”用于单行注释，“/* ... */”用于多行注释

创建表，注意CREATE TABLE命令的最后一个参数（即最后一行）不要附加逗号

```sql
CREATE TABLE [IF NOT EXISTS] 'tbname' (
	'colName' INT(4) PRIMARY KEY COMMENT '这里前面没有等号',
	字段名 数据类型 [字段属性 | 约束] [索引] [注释],
	...,
) [COMMENT='这里前面有等号'] [CHARSET=...];

```

对于多字段主键，可以先定义完字段，再定义主键`PRIMARY KEY(id, name)`

表的维护

- `SHOW TABLES` 
- `DESCRIBE 表名` 查看表的定义（表中定义的字段），不能查看数据库的“定义”
- `DROPE TABLE [IF EXISTS] 表名`

表的重命名和字段的修改

- `ALTER TABLE 旧表名 RENAME [TO] 新表名;` [TO]可省略无影响
- `ALTER TABLE 表名 ADD 字段名 数据类型 [属性]`
- `ALTER TABLE 表名 CHANGE 原字段名 新字段名 数据类型（不能为空） [属性]`
- `ALTER TABLE 表名 DROP 字段名`

添加主键约束 `ALTER TABLE 表名 ADD CONSTRAINT 字段名（形如，pk_表名） PRIMARY KEY 表名(字段名)`

添加字段约束 `ALTER TABLE 表名 ADD CONSTRAINT 字段名（形容，fk_从表名_主表名） FOREIGN KEY(外键字段) REFERENCES 主标名（主表字段） `

### 字段约束

- 非空约束 NOT NULL
- 默认约束 DEFAULT 如：DEFAULT '男'
- 唯一约束 UNIQUE KEY
- 主键约束 PRIMARY KEY
- 外键约束 FOREIGN KEY 从表某数据项在主表中必须存在
- 自动增长 AUTO_INCREMENT

InnoDB支持外键，MyISAM不支持外键；外键关联的表要求都是InnoDB。

UNSIGNED也是一种约束

## DML

### 表的储存引擎

InnoDB, MyISAM

```sql
CREATE TABLE tbname (
	# 省略代码
) ENGINE=InnoDB;
```

### INSERT

- `INSERT INTO 表名 [字段名列表] VALUES (值列表);`
- `INSERT INTO 表名 [字段名列表] VALUES (值列表1), (值列表2), ...;`

将查询结果插入到新表

```sql
CREATE TABLE 新表 (
	SELECT 字段1, 字段2, ... FROM 原表
);
```

### UPDATE

- `UPDATE 表名 SET 字段名 = 更新值`

### DELETE

- `DELETE FROM 表名 [WHRER ... ]`
- `TRUNCATE TABLE 表名` 标志列会重新开始编号

## DQL

```sql
SELECT <字段名 | 表达式 | 函数 | 常量>
FROM 表名
[WHERE <查询条件>]
[ORDER BY <排序的列名> [ASC(默认) | DESC]]
```

### SELECT

- `SELECT 字段名 AS 别名`
- `SELECT 字段1+字段2 AS 别名`
- `WHERE 字段名 IS NULL` 查询空值
- `SELECT 常量 AS 字段名`

### ORDER BY

`ORDER BY 字段1 [排序], 字段2[排序]`

### LIMIT

`LIMIT [[位置偏移量], 行数]`

第1条记录的位置偏移量是0。

### 子查询

使用等号的子查询作为WHERE语句的一部分，需要保证子查询返回的值为空或者只有一个

```sql
SELECT 'studentName' FROM 'student' WHERE 'studentNo' = (
	SELECT 'studentNo' FROM 'result'
		INNER JOIN 'subjcet' ON result.subjectNO = subject.subjectNo
		WHERE 'studentResult'=60 AND 'subjectName'='LogicJava'
);
```

#### IN

如果子查询返回的值多于一个，可以使用`IN`

```sql
SELECT 'studentName' FROM 'student' WHERE 'studentNo' IN (
	SELECT 'studentNo' FROM 'result'
		INNER JOIN 'subjcet' ON result.subjectNO = subject.subjectNo
		WHERE 'studentResult'=60 AND 'subjectName'='LogicJava'
);
```

还有`NOT IN`。

#### EXISTS

`SELECT FROM 表名 WHRER EXISTS(子查询)`

如果子查询的结果具有返回行，则执行父查询

#### 常见错误

嵌套在FROM子句中的SELECT语句需要为derived table指定别名

- 错误：`SELCET * FROM (SELECT * FORM 表名)`
- 正确：`SELCET * FROM (SELECT * FORM 表名 AS 别名)`

### 函数 

聚合函数

- `AVG()`
- `COUNT()`
- `MAX()`, `MIN()`
- `SUM()`

字符串函数，注意下标从1开始

- `CONCAT(str1, str2, ...)`
- `INSERT(str, pos, len, newstr)`
- `LOWER(str)`, `UPPER(str)`
- `SUBSTRING(str, pos, len)`

时间日期函数

- `CURDATE()` 当前日期
- `CURTIME()` 当前时间
- `NOW()` 当前日期和时间
- `WEEK(date)`, `YEAR(date)`, `HOUR(date)`, `MINUTE(date)`
- `DATEDIFF(date1, date2)` 返回日期相隔的天数
- `ADDDATE(date, n)` 返回date

数学函数

- `CEIL(x)`, `FLOOR(x)`
- `RAND()`

## 源

- [Example](https://github.com/lightyears1998/quiet-space/tree/master/playground/mysql)
- 中国水利水电出版社 2017 《MySQL数据库开发实战》 课工场
