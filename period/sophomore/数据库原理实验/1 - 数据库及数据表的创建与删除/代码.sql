/* 创建用户 */
CREATE USER "light" IDENTIFIED BY "lightpwd";
GRANT RESOURCE, CONNECT TO "light";

/* 查询用户 */
SELECT * FROM all_users;
-- 其他系统表：https://www.techonthenet.com/oracle/sys_tables/index.php

/* 创建数据表 */
CREATE TABLE "Student"(
    "SNO" VARCHAR2(10 CHAR) PRIMARY KEY,
    "Sname" VARCHAR2(5 CHAR) NOT NULL,
    "Sage" INTEGER,
    "Ssex" VARCHAR2(1 CHAR),
    "Sdept" VARCHAR2(20 CHAR)
);

CREATE TABLE "Course"(
    "CNO" VARCHAR2(5 CHAR) PRIMARY KEY,
    "Cname" VARCHAR2(10 CHAR) NOT NULL,
    "CPNO" VARCHAR2(5 CHAR),
    "Ccredit" INTEGER,
    FOREIGN KEY ("CPNO") REFERENCES "Course" ("CNO")
);

CREATE TABLE "SC"(
    "SNO" VARCHAR2(10 CHAR),
    "CNO" VARCHAR2(5 CHAR),
    "Grade" NUMERIC(5, 2),
    PRIMARY KEY ("SNO", "CNO"),
    FOREIGN KEY ("SNO") REFERENCES "Student" ("SNO"),
    FOREIGN KEY ("CNO") REFERENCES "Course" ("CNO")
);

/* 向数据表中插入数据 */
INSERT INTO "Course" ("CNO", "Cname", "CPNO", "Ccredit")
VALUES ('CS0', '计算机科学概论', NULL, 4);
INSERT INTO "Course" ("CNO", "Cname", "CPNO", "Ccredit")
VALUES ('CS10', '计算机图形学', 'CS0', 5);
INSERT INTO "Course" ("CNO", "Cname", "CPNO", "Ccredit")
VALUES ('CS1', 'C++', 'CS0', 5);


INSERT INTO "Student" ("SNO", "Sname", "Sage", "Ssex", "Sdept")
SELECT '1706300001', '杜新知', 21, '男', '软件工程' FROM dual UNION ALL
SELECT '1706300002', '庄梓洁', 20, '女', '计算机科学' FROM dual UNION ALL
SELECT '1706300003', '司浩轩', 22, '男', '网络工程' FROM dual;


INSERT INTO "SC" ("SNO", "CNO", "Grade")
VALUES ('1706300001', 'CS0', 100.00);
INSERT INTO "SC" ("SNO", "CNO", "Grade")
VALUES ('1706300002', 'CS0', 60.52);
INSERT INTO "SC" ("SNO", "CNO", "Grade")
VALUES ('1706300003', 'CS0', 80.899);  -- 80.899被四舍五入为80.90

/* 修改数据表的定义 */
ALTER TABLE "Student"
ADD "Senrollment" DATE DEFAULT SYSDATE;

ALTER TABLE "Student"
ADD CHECK("Ssex" in ('男', '女'));

ALTER TABLE "Course"
ADD "Cdesc" VARCHAR2(200 CHAR);

ALTER TABLE "Course"
MODIFY "Cdesc" VARCHAR2(500 CHAR);

ALTER TABLE "Course"
DROP COLUMN "Cdesc";

/* 添加外键约束 */
ALTER TABLE "Course"
ADD FOREIGN KEY ("CPNO") REFERENCES "Course" ("CNO");
-- 报错：Self-evident
-- 因为在第5步创建表时已经添加了外键约束

/* 对比Oracle与MariaDB */
-- 创建表
CREATE TABLE ORACLE 
(
  COLUMN1 VARCHAR2(20) 
);
COMMENT ON TABLE ORACLE IS '这是一张表';
COMMENT ON COLUMN ORACLE.COLUMN1 IS '这是一个字段';

CREATE TABLE `maria` (
	`col` INT NULL COMMENT '这是一个字段'
)
COMMENT='这是一张表';

-- 插入多行数据
INSERT INTO `maria` (`col1`, `col2`) VALUES
(1, 2),
(3, 4),
(5, 6);

-- 查询系统时间
SELECT sysdate FROM dual;  -- Oracle
SELECT NOW();  -- MariaDB
