# MariaDB笔记

## Chapter 0 概念

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

### 安装

#### 在CentOS7上安装

```sh
yum install mariadb-server
sudo systemctl start mariadb
sudo systemctl status mariadb
sudo systemctl enable mariadb
sudo mysql_secure_installation
mysqladmin -u root -p version
```

## Chapter 1 命令行指令

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

数据表的行数由最小的行数决定

## Chapter 2 数据类型和运算符

- *`=`* 赋值 / 等于（关系比较符）
- *`<>`* *`!=`*（非标准） 不等于

数值数据类型

- [TINY | SMALL | MEDIUM ]INT[(M)] 有符号，分别占用1、2、3和4字节储存，其中M表示显示宽度，与实际占用的空间大小无关
- FLOAT(M), DOUBLE(M, D), DECIMAL(M, D)
- CHAR(M), VARCHAR(M), TINYTEXT, TEXT
- DATE, DATETIME, TIME, TIMESTAMP, YEAR

`NOW()`的类型是`DATETIME`

`CURRENT_TIMESTAMP`

如果不指定CHAR的宽度，默认值是灾难性的1。

## Chpater 3 用户管理

创建用户

```sql
CREATE USER 'user' IDENTIFIED BY 'password';
```

管理权限

```sql
GRANT ALL PRIVILEGES ON dbname.* TO uesr;
```

## Chapter 4 DDL

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

`SHOW CREATE TABLE 表名[\G]` 查看创建表的语句

对于多字段主键，可以先定义完字段，再定义主键`PRIMARY KEY(id, name)`

定义外键 `FOREIGN KEY(col1, col2) REFERENCES 主表名 (col1, col2)`

`ALTER TABLE DROP FOREIGN KEY 外键约束名称`

表的维护

- `SHOW TABLES`
- `DESCRIBE 表名` `DESC 表名` 查看表的定义（表中定义的字段），不能查看数据库的“定义”
- `DROPE TABLE [IF EXISTS] 表名`

表的重命名和字段的修改

- `ALTER TABLE 旧表名 RENAME [TO] 新表名;` [TO]可省略无影响
- `ALTER TABLE 表名 ADD 字段名 数据类型 [属性]`
- `ALTER TABLE 表名 MODIFY 字段名 数据类型` 改变字段数据类型
- `ALTER TABLE 表名 MODIFY 字段名 数据类型 FIRST | AFTER 字段名` 改变字段的排列顺序
- `ALTER TABLE 表名 CHANGE 原字段名 新字段名 数据类型（不能为空） [属性]` 改变字段名或字段数据类型
- `ALTER TABLE 表名 DROP 字段名`

添加主键约束 `ALTER TABLE 表名 ADD CONSTRAINT 字段名（形如，pk_表名） PRIMARY KEY 表名(字段名)`

添加字段约束 `ALTER TABLE 表名 ADD CONSTRAINT 字段名（形容，fk_从表名_主表名） FOREIGN KEY(外键字段) REFERENCES 主标名（主表字段）`

### 字段约束

- 非空约束 NOT NULL
- 默认约束 DEFAULT 如：DEFAULT '男'
- 唯一约束 UNIQUE KEY
- 主键约束 PRIMARY KEY
- 外键约束 FOREIGN KEY 从表某数据项在主表中必须存在
- 自动增长 AUTO_INCREMENT

InnoDB支持外键，MyISAM不支持外键；外键关联的表要求都是InnoDB。

UNSIGNED也是一种约束

## Chpater 5 DML

### 表的储存引擎

InnoDB, MyISAM, Memory, Archive

```sql
CREATE TABLE tbname (
    # 省略代码
) ENGINE=InnoDB;
```

`ALTER TABLE 表名 ENGINE=<引擎名>`

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

## Chapter 6 DQL

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

`LIMIT [[位置偏移量offset], 行数row_count]`

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

### IN

如果子查询返回的值多于一个，可以使用`IN`

```sql
SELECT 'studentName' FROM 'student' WHERE 'studentNo' IN (
    SELECT 'studentNo' FROM 'result'
        INNER JOIN 'subjcet' ON result.subjectNO = subject.subjectNo
        WHERE 'studentResult'=60 AND 'subjectName'='LogicJava'
);
```

还有`NOT IN`。

### BETWEEN AND

`SELECT name FROM student WHERE id BETWEEN 1706300001 AND 1806300001`

还有`NOT BETWEEN AND`

### LIKE

匹配查询，`%`任意多个字符（包括0个），`_`任意一个字符

`SELECT * FROM books WHRER name LIKE '%大全'`

### DISTINCT

`DISTINCT`必须放在查询语句的开头，可以与`COUNT()`结合使用，返回不重复的字段；反义词是`ALL`

`SELECT DISTINCT author FROM books WHRER name LIKE '%大全'`

### SOME

`SOME`亦作`ANY`，表示为满足任意一个条件

`SELECT * FROM books WHRER price > SOME(5, 15, 20)` 表示查询价格大于5的数据

### EXISTS

`SELECT FROM 表名 WHRER EXISTS(子查询)`

如果子查询的结果具有返回行，则执行父查询

#### 常见错误

嵌套在FROM子句中的SELECT语句需要为derived table指定别名 `(子查询) AS 别名`

- 错误：`SELCET * FROM (SELECT * FORM 表名)`
- 正确：`SELCET * FROM (SELECT * FORM 表名) AS 别名`

### GROUP BY

分组查询：根据字段分组查询后合并结果

- `SELECT subjectNo, AVG(studentResult) from result group by subjectNo`
- `SELECT COUNT(*), gradeId FROM student GROUP BY gradeId;`

使用`HAVING`对分组后的数据进行筛选，无法使用`WHERE`对分组后的数据进行筛选

```sql
SELECT COUNT(*) '人数', gradeId '年级', sex '性别'
FROM student
GROUP BY gradeId
HAVING COUNT(*) > 2;
```

执行顺序：`WHERE` -\> `GROUP BY` -\> 聚合函数 -\> `HAVING`

### UNION

`UNION`合并多个查询的结果并去除重复项目，合并时表对应的字段和数据类型必须相同

`UNION ALL`不去除重复

### 连接查询

- **内连接** 根据表中共同的列来进行匹配
- **外连接** 至少返回一个表中的所有记录，根据匹配条件有选择地从另一个表中返回记录

#### 内连接

使用`WHERE`的内连接

```sql
SELECT student.studentName, result.subjectNo, result.studentResult
FROM student, result
WHERE student.studentNo = result.studentNo;  
```

使用`[INNER] JOIN ... ON ..`的内连接

```sql
SELECT studentName, subjectNo, studentResult
FROM student
INNER JOIN result ON student.studentNo = result.studentNo;
```

或使用别名，其中若连接中的两个表或多个表中查询的字段不重复则不需要对这一列不需要指定别名。

```sql
SELECT S.studentName, R.subjectNo, R.studentResult
FROM student as S
INNER JOIN result as R ON S.studentNo = R.studentNo;
```

可以对多个表使用内连接

```sql
SELECT S.studentName, SU.subjectName, R.studentResult
FROM student AS S
INNER JOIN result AS R ON S.studentNo = R.studentNo
INNER JOIN subject AS SU ON SU.subjectNo = R.subjectNo;
```

### 外连接

`<LEFT | RIGHT> OUTER JOIN ... ON`

```sql
SELECT S.studentName, R.studentResult
FROM student AS S
LEFT OUTER
JOIN result AS R ON S.studentNo = R.studentNo;
```

LEFT OUTTER JOIN返回结果包含左表的所有行

## Chapter 7 函数

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

## Chapter 8 事务 Transaction

将一系列数据操作左为整体处理，如果某一事务提交成功则该事务的所有数据更改均会提交，成为数据库中的永久组成部分；如果事务执行时遇到错误且必须去取消或回滚，则数据将全部恢复到操作前的状态，所有数据的更改均被清除。

- 原子性 事务的各个元素是不可分割的
- 一致性 事务完成时数据处于一致状态，事务不能使数据储存处于不稳定的状态
- 隔离性 所有并发事务彼此隔离；事务不应该以任何方式依赖或影响其他事务
- 持久性 一旦事务提交，对数据库的影响是永久的

InnoDB对事物的支持：REDO日志、UNDO日志

```sql
BEGIN;  // 或 START TRANSACTION;

COMMIT;
ROLLBACK;
```

未显式开启事务时，每条SQL语句都作为单独的事务执行完毕自动提交。

MySQL设置自动提交 `SET autocommit = 0 | 1;`

## Chpater 9 视图

- 创建视图 `CREATE VIEW 视图名（形如view_xxx或v_xxx）AS <SELECT 语句>`
- 删除视图 `DROP VIEW [IF EXISTS] 视图名`
- 查看视图 `SELECT * FROM 视图名`

视图可以嵌套另一个视图，对视图数据的添加修改和查询直接影响表中的数据。

## Chapter 10 索引

- 普通索引 允许重复和空值
- 唯一索引 不允许重复，允许空值
- 主键索引 单一主键时自动创建主键索引，主键索引非空不重复
- 复合索引 将多个列组合作为索引；在查询中只有使用了组合索引中最左边的字段时，索引才会被使用
- 全文索引 主要用于在CAHR, TEXT等数据中全文检索数据
- 空间索引 MyISAM only，对空间数据类型建立的索引

创建和使用索引

- 创建索引 `CREATE [UNQIUE | FULLTEXT | SPATIAL |] INDEX 索引名 ON 表名(字段名[字符串类型可以指定索引长度])`
- 删除索引 `DROP INDEX 表名.索引名`
- 查看索引 `SHOW INDEX FROM 表名`

## Chapter 11 备份

备份

- `mysqldump -u usrname -h host -p dbname[tbname1, ...] > filename.sql`

或保存到外部文件

```sql
SELECT * FROM ...
INTO OUTFILE 'filename' [OPTIONS]
```

恢复

- `mysql -u -p [dbname] < filename.sql`
- 登陆MySQL后，`source filename`

## 源

- [Example](https://github.com/lightyears1998/quiet-space/tree/master/playground/mysql)
- 中国水利水电出版社 2017 《MySQL数据库开发实战》 课工场
