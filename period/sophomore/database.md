# 数据库原理

## 数据库系统基本概念

- 数据库

    1. **数据** 描述事物的符号记录。
    2. **数据库** 永久储存、有组织、可共享的数据的集合。
    3. **数据库管理系统** DBMS，如MySQL、Oracle Database等。
    4. **数据库系统** 包括数据库、数据库管理系统、应用程序和数据库管理员。

- 数据独立性

    1. **物理独立性** 用户的应用程序和数据库中数据的物理储存分离。
    2. **逻辑独立性** 用户的应用程序与数据库的逻辑结构是相互独立的。

- **数据模型** 对现实世界数据特征的抽象，一般包括数据结构、数据操作和数据完整性约束条件：

    1. 概念模型 按用户的观点对信息进行建模。

        1. 实体
        2. 属性
        3. 码 唯一标志实体的**最小**属性集合。
        4. 超码 能够唯一标志实体的属性集合。

    2. 逻辑模型 包括层次模型、网状模型、关系模型、面向对象数据模型等。
    3. 物理模型 底层的储存结构。

- 数据库系统的模式

    1. 模式（逻辑模式）数据库中全体数据的逻辑结构和特征的描述。
    2. 外模式（子模式、用户模式） 数据库用户所看见和使用的局部数据的逻辑结构和特征的描述。
    3. 内模式（存储模式） 数据物理结构和存储方式的描述。

- 在模式的基础上建立的数据库的二级映像

    1. 外模式/模式映像
    2. 模式/内模式映像

## 关系基本概念

- **域** 具有相同数据类型的值的集合。

- **属性名** 对关系的一个列附加属性名以取消关系元组的有序性质。

- **关系模式** 对关系的描述

    1. 候选码 能唯一标志一个关系的最小集合（对应概念模型中“码”的概念）。
    2. 主码 选定的一个候选码。
    3. 全码 关系模式的所有属性都是这个关系的候选码。
    4. 主属性/非主属性/非码属性 候选码的所有属性称为主属性。
    5. 外码 参照关系中与被参照关系主码对应的属性（不一定是参照关系的码）。

- **关系的基本操作**

    1. 查询（选择、投影、并、差、交、笛卡尔积）
    2. 插入
    3. 修改
    4. 删除

- **关系的完整性**

    1. 实体完整性
    2. 参照完整性 A → B（参照关系 → 被参照关系，或称目标关系；A中与被参照关系的主码对应的属性称为A的外码）
    3. 用户定义的完整性

- **关系代数**

  - 传统的集合运算
    1. 并 ∪
    2. 差 -
    3. 交 ∩
    4. 笛卡尔积 X
  - 专门的关系运算
    1. 选择 σ
    2. 投影 Π
    3. 连接（θ连接） ⋈
        - 等值连接 算子为“=”的连接。
        - 自然连接 要求算子为“=”且进行比较的分量同名。
        - 悬浮元组 在操作时因为`NULL`而被舍弃的元组。
        - 外连接 将悬浮元组保留在结果集中，而将其他属性填`NULL`。
            - 左外连接/右外连接 只保留左边/右边的悬浮元组的连接。
    4. 除 A ÷ B（取A、B的公共属性集x，要求x在B上的象集是x在A上的象集的子集）

## 结构化查询语言SQL

四大分类

1. DDL *Data Definiton Language* 数据定义语言
2. DML *Data Manipulation Language* 数据操作语言
3. DQL *Data Query Language* 数据查询语言
4. DCL *Data Control Language* 数据控制语言

九个动词

1. 数据定义 `CREATE`, `DROP`, `ALTER`
2. 数据操纵 `INSERT`, `UPDATE`, `DELETE`
3. 数据查询 `SELECT`
4. 数据控制 `GRANT`, `REVOKE`

### 数据类型

1. CHAR(n), VARCHAR(n)
2. CLOB, BLOB 字符串/二级制大对象
3. INT(EGER), SMALLINT, BIGINT
4. NUMERIC(p, d), DECIMAL(p, d), DEC(p, d) p位整数，d位小数的定点数
5. REAL, DOUBLE PRECISION 单精度/双精度浮点数
6. FLOAT(n) 精度至少为n的浮点数
7. BOOLEAN
8. DATE, TIME, TIMESTAMP, INTERVAL

### SHOW/SET

- 搜索路径 `SHOW search_path`, `SET search_path TO <新路径>`

### 数据定义 DDL

1. 模式
    - 定义模式
        - `CREATE SCHEMA <模式名> AUTHORIZATION <用户名>;` 如果没有用户名，模式名隐含为用户名
        - `CREATE SCHEMA <模式名> AUTHORIZATION <用户名> [<表定义字句>|<视图定义子句>|<授权定义子句>];`
    - 删除模式 `DROP SCHEMA <模式名> <RESTRICT | CASCADE>;`
        - CASCADE 在删除模式时删除模式下的数据库对象。
        - RESTRICT 在模式下没有数据库对象时才能删除模式。

2. 表

    - 定义表

        ```sql
        CREATE TABLE <表名> (
            <列名> <数据类型> [<列级数据完整性约束条件>]
            [, ...]
            [, <表级数据完整性约束条件>]
        );
        ```

        列级数据完整性约束条件
            1. `PRIMARY KEY`
            2. `NOT NULL`
            3. `UNIQUE`

        表级数据完整性约束条件
            1. `FOREIGN KEY (<列名>) REFERENCES <表名>(<列名>)`

        表属于一个模式，定义表时可以指定表所属的模式`CREATE TABLE <模式名>.<表名> ...;`；没有显式给出模式名的表定义，由搜索路径决定归属。

    - 修改表

        ```sql
        ALTER TABLE <表名> [
            [ADD COLUMN <列名> <数据类型> <完整性约束>]
            [ADD 表级别完整性约束]
            [DROP COLUMN <列名> [RESTRICT | CASCADE]]
            [DROP CONSTRAINT <完整性约束名> [RESCRICT | CASCADE]]
            [ALTER COLUMN <列名> <数据类型>]
        ];
        ```

    - 删除表 `DROP TABLE <表名> [RESTRICT | CASCADE]`

3. 索引

    - 建立索引 `CREATE [UNIQUE] [CLUSTER] INDEX <索引名> ON <表名>([<列名> [<ASC | DESC>], ...]);`
    - 修改索引 `ALTER INDEX <索引名> RENAME TO <新索引名>;`
    - 删除索引 `DROP INDEX <索引名>;`

4. 视图

    将子查询的作为一个视图保存在数据字典中。

    ```sql
    CREATE VIEW 视图名
    [列名, ...]
    AS <子查询>
    [WITH CHECK OPTION]
    ```

    在可更新的视图中，若使用`WITH CHECK OPTION`，则不能通过视图来插入/修改定义视图的子查询的`WHERE`子句中过滤掉的字段，
    即只能插入/修改/删除已经存在或可以存在于视图中的数据。

    [WITH CHECK OPTION](http://www.oracletutorial.com/oracle-view/oracle-with-check-option/)

### 数据查询

```sql
SELCET [ALL | DISTINCT] <目标列或表达式>, [<目标列或表达式>, ...]
FROM <表名或视图名>, [<表名或视图名>, ...]
[WHERE <条件表达式>]
[GROUP BY <列名或表达式名> [HAVING <条件表达式>]]
[ORDER BY <列名或表达式名> [ASC | DESC]]
```

#### Having子句

先对查询的结果无条件进行分组，然后按`HAVING`子句中的条件对每个分组进行检查，从而筛除掉不符合`HAVING`子句条件的分组。

#### 关于SELECT DISTINCT的去重

SELECT DISTINCT去除逻辑上的重复行。即信息与其他行相同的行。

具体来说：

```text
MariaDB [test]> SELECT * FROM sc;
+------+-------+
| sno  | grade |
+------+-------+
|    1 |   100 |
|    1 |    50 |
| NULL |  NULL |
| NULL |  NULL |
|   12 |   100 |
+------+-------+
5 rows in set (0.01 sec)

MariaDB [test]> SELECT DISTINCT * FROM sc;
+------+-------+
| sno  | grade |
+------+-------+
|    1 |   100 |
|    1 |    50 |
| NULL |  NULL |
|   12 |   100 |
+------+-------+
4 rows in set (0.01 sec)

MariaDB [test]> SELECT DISTINCT sno FROM sc;
+------+
| sno  |
+------+
|    1 |
| NULL |
|   12 |
+------+
3 rows in set (0.01 sec)

```

#### 子查询

有相关子查询和不相关子查询之分。子查询若从主查询处取得参数，从而与主查询相关，则为“相关子查询”。

使用`=`连接的子表只能是单值。

#### GROUP BY [列名列表]

按列名列表依次分组，细化聚集函数的作用对象。

一个分组永远只有一个输出，无论“看上去它应该是多行输出”。

注意ORDER BY子句对GROUP BY子句是没有影响的，因为GROUP BY子句先于ORDER BY作用，而ORDER BY只能调整输出结果的次序。

#### 外连接和内连接

外连接

```sql
SELECT ...
FROM 左表名 [LEFT | RIGHT | FULL] OUTER JOIN 右表名 ON (连接条件);
```

内连接使用`WHRER`子句来实现。

#### 集合运算

集合的交并差。

- `INTERSECT` 交
- `UNION` 并
- `EXCEPT`, Oracle `MINUS` 差

#### UNION子句

UNION用于连接两个SELECT的查询结果，注意UNION合并表之后表中没有重复的行。（可以看成是先使用UNION ALL合并表，然后将表中的冗余项目去除。）

使用UNION ALL来避免去重。

注意UNION在去重上的默认行为与SELECT相反。

### 数据更新

```sql
UPDATE 表名 SET 列名=值
WHERE 条件子句;
```

### 数据删除

```sql
DELETE FROM 表名
WHERE 条件子句;
```

### 条件表达式

通常在`WHRER`子句中出现。

1. `NOT`
2. `IS NULL`
3. `BETWEEN ... AND ...`
4. 字符串 `LIKE "字符串"` 任意长度通配符`%` 单字符通配符`_` 转义序列 `LIKE <"待转义的字符串"> [ESCAPE <"转义序列">]`
5. 正则表达式匹配 `regexp_like("正则表达式")`

在使用复合的条件连接时，注意使用括号来阐明运算符的优先级。

#### 带ANY(SOME)/ALL谓词的子查询

需要配合比较运算符使用。

- `ANY (SOME) 集合`
- `ALL 集合`

#### 带EXISTS谓词的子查询

EXISTS即存在量词∃。

带有EXISTS的子查询不返回数据，只返回逻辑真假，因此SELECT子句通常使用通配符*。当子查询的结果不为空时返回`true`。

使用EXISTS来实现全称量词∀。
`∀x: P ⇔ ¬(∃x: ¬P)`
可以通过使用数量相等来避免全称量词的使用。

使用EXISTS来实现逻辑蕴含→。
`∀x: (P→Q) ⇔ ∀x: (¬P∨Q) ⇔ ¬(∃x: P∨¬Q)`

### 辅助函数

- `LOWER()`
- `TO_CHAR(数值, '格式字符串')`

    [格式字符串][]形如`FM999.00`。FM为去除前导和后导零。

[格式字符串]: https://docs.oracle.com/cd/B19306_01/server.102/b14200/sql_elements004.htm

### 聚集函数

在有`GROUP BY`字句时对分组起作用，无`GROUP BY`子句时将查询结果作为一组对全组起作用。
常出现于`HAVING`和`SELECT`子句中对分组中来对分组进行条件约束的筛选或输出结果。
注意聚集函数不能在`WHERE`子句中使用。

除COUNT以外的聚集函数都自动过滤掉`NULL`值。

使用不同的参数时，`COUNT`统计的结果不同。

- `COUNT(*)` 总是返回表的行数。
- `COUNT(NULL)` 总是返回0。
- `COUNT(0)`, `COUNT(false)`, `COUNT(任意非NULL常量)` 返回表的行数。
- `COUNT("列名")` `COUNT`对列中的每一行将值代入，如果非NULL则增加1，NULL则和不变。
- 实际上，上述结论是`COUNT`计数原理的统一。

## 数据安全性

通过权限和角色来保证数据的安全性。

## 约束

```sql
CONSTRAINT <约束名称> <约束条件>
```

常用约束

```sql
CHECK "Column" IN ('OptionA', 'OptionB');
CHECK <表达式A> OR <表达式B>;
```

## 触发器

由事件驱动的特殊过程，基于一个表创建，但是可以操作多个表。

缺点在于平台迁移难度大，并存在后端资源的占用。

```sql
CREATE TRIGGER <触发器名>
[BEFORE | AFTER] <触发事件> ON <表名>
REFENCING [NEW | OLD] ROW AS <变量名>
```

// 待补充
// AFTER触发器、BEFORE触发器

### 触发器被触发的顺序

1. 语句级 BEFORE INSERT
2. 行级 BEFORE INSERT
3. 行级 AFTER INSERT
4. 行级 AFTER INSERT

在BEFORE INSERT中操作NEW ROW，会实际上改变插入数据库中的数据。

## 区块未知

- 函数依赖 自变量x在确定之后f(x)的值也能被确定。
- 非规范 表中有表、变量可分。

范式

- 1NF 关系模式中所有属性都是不可再分的数据项目。（可能存在的问题有：更新异常、插入异常和删除异常等等）
- 2NF 消除了非主属性对主属性的部分函数依赖（函数依赖于码中的部分属性而不是码的整体）。（非主属性对码是完全函数依赖。）
- 3NF 非主属性对码不存在传递函数依赖。
- BCNF

    1. 所有非主属性对每一个码都是完全函数依赖。
    2. 所有主属性对不包含其码的属性都是完全函数依赖。

### ArmStrong公理系统

用于推证函数依赖，包括自反律、增广律和传递律。

## 数据库恢复技术

1. 静态转储
2. 登记日记文件

Oracle查看日志

故障类型

1. 事务故障
2. 系统故障
3. 介质故障

并发控制
