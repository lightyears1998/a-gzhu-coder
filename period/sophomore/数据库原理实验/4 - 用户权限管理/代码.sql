-- 创建新用户
CREATE USER alice IDENTIFIED BY "alicepwd";
GRANT CONNECT, RESOURCE, DBA TO alice;


-- 查询当前用户拥有的权限
SELECT * from user_role_privs;


-- 创建数据表并插入数据
CREATE TABLE READER
(
    RNO	VARCHAR2(4 CHAR) PRIMARY KEY,
    RNAME	VARCHAR2(10 CHAR) NOT NULL,
    RSEX	VARCHAR2(1 CHAR),
    RAGE	INTEGER,
    RBOSS	VARCHAR2(10 CHAR),
    RADDRESS	VARCHAR2(30 CHAR)
) ;
INSERT INTO READER (RNO,RNAME,RAGE,RSEX,RBOSS, RADDRESS) VALUES('R001','张三',20,'男','李四','416');

CREATE TABLE BOOK
(
    BNO	VARCHAR2(4 CHAR),
    BNAME	VARCHAR2(50 CHAR) NOT NULL,
    BAUTHOR	VARCHAR2(50 CHAR),
    BPRESS	VARCHAR2(50 CHAR),
    BPRICE	NUMERIC(6,2), 
    PRIMARY KEY(BNO)
);
INSERT INTO BOOK (BNO,BAUTHOR,BNAME, BPRESS, BPRICE) VALUES('B001','严蔚敏','数据结构','清华大学出版社',NULL);

CREATE TABLE RB
(
    RNO VARCHAR2(4 CHAR),
    BNO VARCHAR2(4 CHAR),
    RBDATE DATE DEFAULT SYSDATE,
    PRIMARY KEY(RNO,BNO),
    FOREIGN KEY (RNO) REFERENCES READER(RNO),
    FOREIGN KEY (BNO) REFERENCES BOOK(BNO)
);
INSERT INTO RB (RNO,BNO) VALUES ('R001','B001');


-- 查询权限信息
SELECT * FROM dba_role_privs;
SELECT * FROM dba_sys_privs;
SELECT * FROM role_sys_privs;


-- 查询用户创建的表
SELECT table_name FROM user_tables;


-- 删除RB表
DROP TABLE RB;
SELECT table_name FROM user_tables;


-- SYS：回收Alice的部分权限
REVOKE dba, RESOURCE FROM alice;


-- Alice：尝试创建数据表
CREATE TABLE aa(cola INT);


-- SYS：将Resource权限授予Alice
GRANT RESOURCE TO alice;


-- Alice：尝试创建表
SELECT * FROM user_role_privs;
CREATE TABLE aa(cola INT);


-- SYS：尝试删除用户Alice
DROP USER alice;
DROP USER alice CASCADE;


-- SYS：重新创建用户Alice和Bob
CREATE USER alice IDENTIFIED BY alicepwd;
CREATE USER bob IDENTIFIED BY bobpwd; 
GRANT RESOURCE, CONNECT, DBA TO alice, bob;

-- 只有DBA才能执行下面这条查询
SELECT * FROM dba_role_privs WHERE grantee IN ('ALICE','BOB');


-- Alice
CREATE TABLE from_alice(message CHAR(1));
INSERT INTO from_alice VALUES('a');
SELECT * FROM from_alice;

-- Bob
-- 显示FROM_ALICE表的创建者和表名
SELECT OWNER, table_name FROM all_tables WHERE table_name='FROM_ALICE';
-- 此时可见alice创建的表from_alice

-- 尝试查询FROM_ALICE表中的数据
SELECT * FROM from_alice;  -- ORA-00942: 表或视图不存在

-- Alice
GRANT ALL ON from_alice TO bob;

-- Bob
-- 显示FROM_ALICE表的创建者和表名
SELECT OWNER, table_name FROM all_tables WHERE table_name='FROM_ALICE';
-- 可以查询到from_alice表

SELECT * FROM from_alice;  -- ORA-00942: 表或视图不存在
SELECT * FROM alice.from_alice;  -- 显示Alice在表中插入的信息‘a’

INSERT INTO alice.from_alice VALUES('d');
SELECT * FROM alice.from_alice;  -- 验证上面的操作插入成功


-- Alice
REVOKE INSERT ON from_alice FROM bob;

-- Bob
SELECT * FROM alice.from_alice;
-- 可以显示表中的内容

INSERT INTO alice.from_alice VALUES('y');
SELECT * FROM alice.from_alice;
-- 插入成功

-- SYS
REVOKE DBA, RESOURCE FROM bob;

-- Bob
SELECT * FROM alice.from_alice;
-- 能显示表中的内容

INSERT INTO alice.from_alice VALUES('z');
SELECT * FROM alice.from_alice;
-- 插入成功

-- Alice
REVOKE ALL ON from_alice FROM bob;
SELECT * FROM alice.from_alice;
-- 没有显示前面成功插入的记录'd'、'y'、'z'

-- Bob
SELECT * FROM alice.from_alice;
-- 显示前面成功插入的记录'd'、'y'、'z'

commit;  -- 成功提交

-- Alice
SELECT * FROM alice.from_alice;
-- 显示前面成功插入的记录'd'、'y'、'z'


-- Bob（重新连接）
SELECT * FROM alice.from_alice;
-- ORA-00942: table or view does not exist

SELECT * FROM user_role_privs;
-- 当前用户只有Connect权限

CREATE TABLE from_bob(message CHAR(1 CHAR));
-- 不能执行
-- ORA-01031: insufficient privileges

-- SYS
GRANT RESOURCE TO bob;

-- Bob（不重新连接Bob）
CREATE TABLE from_bob(message CHAR(1 CHAR));
-- 不能执行
-- ORA-01031: insufficient privileges

-- 重新连接Bob
CREATE TABLE from_bob(message CHAR(1 CHAR));
INSERT INTO from_bob VALUES('甲');
SELECT * FROM from_bob;  -- 可以查询到记录‘甲’

-- Alice
SELECT * FROM bob.from_bob;
-- 不能看到记录‘甲’

-- Bob
GRANT SELECT ON from_bob TO alice;  -- 允许Alice查看from_bob表中的数据
GRANT INSERT, DELETE, UPDATE ON from_bob TO alice;  -- 允许Alice插入、修改和删除from_bob表中的数据


/* 查询数据库系统中对当前用户可见的所有用户 */
-- https://docs.oracle.com/cd/B19306_01/server.102/b14237/statviews_2114.htm#REFRN20302
SELECT * FROM all_users;
