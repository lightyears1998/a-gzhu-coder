/* 创建新用户并授权 */
CREATE USER "exp2" IDENTIFIED BY "exp2pwd";
GRANT RESOURCE, CONNECT TO "exp2";

/* 初始数据 */

-- 删去同名的旧数据表
-- 注意传递给EXECUTE IMMEDIATE的SQL语句中不要使用分号结尾，
-- 否则容易报出误导性的“非法标识符”错误。
DECLARE
    "counter" INT DEFAULT 0;
BEGIN
    SELECT COUNT(*) INTO "counter" FROM user_tables WHERE table_name='RB';
    IF ("counter" > 0) THEN
        EXECUTE IMMEDIATE 'DROP TABLE "RB"';
    END IF;
    SELECT COUNT(*) INTO "counter" FROM user_tables WHERE table_name='Reader';
    IF ("counter" > 0) THEN
        EXECUTE IMMEDIATE 'DROP TABLE "Reader"';
    END IF;
    SELECT COUNT(*) INTO "counter" FROM user_tables WHERE table_name='Book';
    IF ("counter" > 0) THEN
        EXECUTE IMMEDIATE 'DROP TABLE "Book"';
    END IF;
END;

-- 创建Reader表并插入初始数据
CREATE TABLE "Reader"
(
    "RNO"	VARCHAR2(4 CHAR) PRIMARY KEY,
    "Rname"	VARCHAR2(5 CHAR) NOT NULL,
    "Rsex"	VARCHAR2(1 CHAR),
    "Rage"	INTEGER,
    "Rboss"	VARCHAR2(10),
    "Raddress"	VARCHAR2(30)
);

INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R001', '张三', 20, '男', '李四', '416');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R002', '张三', 35, '女', NULL, '417');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R003', '李四', 30, '男', NULL, '416');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R004', '王五', 20, '男', NULL, '417');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R005', '马六', 40, '男', NULL, '416');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R006', '刘三', 20, '男', NULL, '417');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R007', '王四', 40, '男', '李四', '416');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R008', '李小龙', 20, '男', '李四', '417');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R009', '王小倩', 40, '男', '李四', '416');
INSERT INTO "Reader" ("RNO", "Rname", "Rage", "Rsex", "Rboss", "Raddress") VALUES('R010', '王一小', 20, '男', '李四', '417');

-- 创建Book表并插入初始数据
CREATE TABLE "Book"
(
    "BNO"	VARCHAR2(4 CHAR) PRIMARY KEY,
    "Bname"	VARCHAR2(25 CHAR) NOT NULL,
    "Bauthor"	VARCHAR2(25 CHAR),
    "Bpress"	VARCHAR2(25 CHAR),
    "Bprice"	NUMERIC(6, 2)
);

INSERT INTO "Book" ("BNO", "Bauthor", "Bname", "Bpress", "Bprice") values('B001', '严蔚敏', '数据结构', '清华大学出版社', NULL);
INSERT INTO "Book" ("BNO", "Bauthor", "Bname", "Bpress", "Bprice") values('B002', '唐发根', '数据结构', '北航出版社', 24);
INSERT INTO "Book" ("BNO", "Bauthor", "Bname", "Bpress", "Bprice") values('B003', '王珊', '数据库原理', '高等教育出版社', 40);
INSERT INTO "Book" ("BNO", "Bauthor", "Bname", "Bpress", "Bprice") values('B004', '张飞', '数据库原理', '清华大学出版社', 30);
INSERT INTO "Book" ("BNO", "Bauthor", "Bname", "Bpress", "Bprice") values('B005', '王珊', '数据库原理', '清华大学出版社', NULL);

-- 创建RB表并插入数据
CREATE TABLE "RB"
(
    "RNO" VARCHAR2(4 CHAR),
    "BNO" VARCHAR2(4 CHAR),
    "RBdate" DATE DEFAULT SYSDATE,
    PRIMARY KEY("RNO", "BNO"),
    FOREIGN KEY("RNO") REFERENCES "Reader"("RNO"),
    FOREIGN KEY("BNO") REFERENCES "Book"("BNO")
);

INSERT INTO "RB" ("RNO", "BNO") VALUES ('R001', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R001', 'B002');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R001', 'B004');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R002', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R003', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R004', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R004', 'B002');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R005', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R006', 'B001');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R006', 'B003');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R006', 'B005');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R006', 'B002');
INSERT INTO "RB" ("RNO", "BNO") VALUES ('R006', 'B004');

/* 单表查询 */

-- 1. 查询全体员工的姓名和出生年份
SELECT "Rname" AS "员工姓名", EXTRACT(YEAR FROM SYSDATE)-"Rage" AS "出生年份" FROM "Reader";

-- 2. 查询工作在416房间的员工的所有信息
SELECT * FROM "Reader" WHERE "Raddress"='416';

-- 3. 查询年龄在30到50岁之间的员工姓名、年龄
-- 注意SQL BETWEEN操纵的区间为闭区间[30, 50]
SELECT "Rname", "Rage" FROM "Reader" WHERE "Rage" BETWEEN 30 AND 50;

-- 4. 查询借了书的员工的编号，排除相同的元素
SELECT DISTINCT "RNO" FROM "RB";

-- 5. 查询名字中包含字“小”的员工姓名、办公地点
SELECT "Rname", "Raddress" FROM "Reader" WHERE "Rname" LIKE '%小%';

-- 6. 查询姓名中第二个字为“小”的员工姓名、办公地点；(原题为名字中第二个字不为小)
SELECT "Rname", "Raddress" FROM "Reader" WHERE "Rname" LIKE '_小%';

-- 7. 查询所有不姓“李”的员工姓名、性别；
SELECT "Rname", "Rsex" FROM "Reader" WHERE "Rname" NOT LIKE '李%';

-- 8. 查询Book表中价格不为空值的书名、出版社；
SELECT "Bname", "Bpress", "Bprice" FROM "Book" WHERE "Bprice" IS NOT NULL;

-- 9. 查询清华大学出版社和高等教育出版社出版的所有书籍，按照出版社降序、书名升序排列；
-- 【验证语句】
SELECT * FROM "Book";

-- 【查询语句】
SELECT * FROM "Book" WHERE "Bpress" in ('清华大学出版社', '高等教育出版社')
ORDER BY "Bpress" DESC, "Bname" ASC;

-- 10. 查询员工的总人数
SELECT COUNT("RNO") FROM "Reader";

-- 11. 查询借了书的员工的人数
SELECT COUNT(DISTINCT "RNO") FROM "Reader" WHERE "Reader"."RNO" IN (SELECT "RNO" FROM "RB");
-- 或
SELECT COUNT(DISTINCT "RNO") FROM "RB";

-- 12. 查询“张三”所借图书的数量(注意，员工里有两个人叫张三)
SELECT "RNO", COUNT(*) FROM "RB" 
WHERE "RNO" IN (SELECT "RNO" FROM "Reader" WHERE "Rname"='张三')
GROUP BY "RNO";

-- 13. 查询最贵的书籍的作者姓名；
SELECT "Bname", "Bauthor", "Bprice" FROM "Book" 
WHERE "Bprice"=(
    SELECT MAX("Bprice") FROM "Book"
);

-- 14. 查询Book表中书籍的平均价格
-- 注意分组函数自动过滤掉了空值null
SELECT AVG("Bprice") FROM "Book";


-- 15. 查询Book中包含的各个出版社及其出版书籍的数量
SELECT "Bpress", COUNT("BNO") FROM "Book"
GROUP BY "Bpress";


/* 集合查询 */

-- 1. 查询每个员工及其借书情况，列出员工编号、姓名和借书日期
SELECT "Reader"."RNO", "Rname", "RBdate" From "Reader", "RB"
WHERE "Reader"."RNO"="RB"."RNO";

-- 2. 使用左外连接查询每个员工及其借书所有字段（没有借书的员工也列出来）
SELECT "Reader"."RNO", "Rname", "Rsex", "BNO", "RBdate" From "Reader"
LEFT JOIN "RB" ON "Reader"."RNO"="RB"."RNO";

-- 3. 查询与“李小龙”工作在同一个办公室的员工信息；
-- 自身连接
SELECT b."Rname" FROM "Reader" a, "Reader" b 
WHERE b."Raddress"=a."Raddress" AND a."Rname"='李小龙' 
AND a."Rname"!=b."Rname";
-- 子查询
SELECT "Rname" FROM "Reader" 
WHERE "Raddress"=(SELECT "Raddress" FROM "Reader" WHERE "Rname"='李小龙')
AND "Rname"!='李小龙';

-- 4. 查询借阅了“数据库原理”的员工所有信息（两种方法：连接查询、子查询）
-- 【连接查询】
SELECT DISTINCT "Reader"."RNO", "Rname", "Rsex", "Raddress" FROM "Reader", "Book", "RB"
WHERE "Reader"."RNO"="RB"."RNO" AND "Book"."BNO"="RB"."BNO"
AND "Book"."Bname"='数据库原理';

-- 【子查询】
SELECT DISTINCT "RNO", "Rname", "Rsex", "Raddress" FROM "Reader"
WHERE "RNO" IN (
    SELECT "RNO" FROM "RB" 
    WHERE "BNO" IN (  -- 此处注意不能使用相等判断“=”，因为有多本书名为“数据库原理”，而“=”只能用于单值
        SELECT "BNO" FROM "Book" WHERE "Bname"='数据库原理'
    )
);


-- 5. 查询小于或等于同一办公室中成员的平均年龄的员工编号、姓名、年龄
-- 【验证语句】
SELECT "RNO", "Rname", "Rage", "Raddress" FROM "Reader"
ORDER BY "Raddress";

SELECT "Raddress", AVG("Rage") FROM "Reader"
GROUP BY "Raddress";

-- 【查询语句】
SELECT a."RNO", a."Rname", a."Rage", a."Raddress" FROM "Reader" a
WHERE a."Rage" <= (
    SELECT AVG(b."Rage") FROM "Reader" b WHERE a."Raddress"=b."Raddress"
);

-- 6. 查询比所有数据库原理价格都低、并且不是清华大学出版社出版的书籍的信息
-- 【验证语句】
SELECT * FROM "Book" WHERE "Bname"='数据库原理';
SELECT MIN("Bprice") FROM "Book" WHERE "Bname"='数据库原理';
SELECT * FROM "Book";

-- 【查询语句】
SELECT * FROM "Book"
WHERE "Bprice" < (
    SELECT MIN("Bprice") FROM "Book" WHERE "Bname"='数据库原理'
)
AND "Bpress"!='清华大学出版社';

-- 7. 查询借阅了B001的员工的编号、姓名、办公室
-- 【验证语句】
SELECT "Reader"."RNO", "Rname", "Raddress" FROM "Reader";
SELECT * FROM "RB" WHERE "BNO"='B001';

-- 【查询语句】
SELECT "Reader"."RNO", "Rname", "Raddress" FROM "Reader", "RB" 
WHERE "Reader"."RNO"="RB"."RNO" AND "RB"."BNO"='B001';

-- 8. 查询没有借阅B001的员工的编号、姓名、办公室
SELECT "Reader"."RNO", "Rname", "Raddress" FROM "Reader"
WHERE "Reader"."RNO" NOT IN (
    SELECT "RNO" FROM "RB" WHERE "BNO"='B001'
);


-- 9. 查询借阅了所有书籍的员工的姓名
-- 【验证语句】
SELECT "BNO" FROM "Book";
SELECT "Reader"."RNO", "Rname", "RB"."BNO" FROM "RB"
LEFT OUTER JOIN "Reader"  ON ("Reader"."RNO"="RB"."RNO");

-- 【查询语句】
SELECT "Rname" FROM "Reader"
WHERE NOT EXISTS (
    SELECT "BNO" FROM "Book"
    WHERE NOT EXISTS (
        SELECT * FROM "RB"
        WHERE "RB"."RNO"="Reader"."RNO" AND "RB"."BNO"="Book"."BNO"
    )
);
-- 或借助集合查询
SELECT "Rname" FROM "Reader"
WHERE NOT EXISTS (
    SELECT "BNO" FROM "Book"
    MINUS
    SELECT "BNO" FROM "RB" WHERE "RB"."RNO"="Reader"."RNO"
);
-- 或借助COUNT()
SELECT "Rname" FROM "Reader"
WHERE 
(SELECT COUNT(*) FROM "Book")=
(SELECT COUNT(*) FROM "RB" WHERE "RB"."RNO"="Reader"."RNO");

-- 10. 查询至少借阅了编号为R004的员工借阅的全部书籍的员工姓名、性别、办公室
SELECT * FROM "RB" WHERE "RNO"='R004';
SELECT "Reader"."RNO", "Rname", "RB"."BNO" FROM "RB" 
LEFT OUTER JOIN "Reader" ON ("Reader"."RNO"="RB"."RNO");

-- 【查询语句】
SELECT "RNO", "Rname" FROM "Reader"
WHERE NOT EXISTS (
    SELECT "BNO" FROM "RB" a WHERE a."RNO"='R004'
    AND NOT EXISTS (
        SELECT * FROM "RB" b
        WHERE b."RNO"="Reader"."RNO" AND b."BNO"=a."BNO"
    )
);
-- 或借助集合查询
SELECT "Rname", "Rsex", "Raddress" FROM "Reader"
WHERE NOT EXISTS (
    SELECT "BNO" FROM "RB" WHERE "RNO"='R004'
    MINUS
    SELECT "BNO" FROM "RB" WHERE "RB"."RNO"="Reader"."RNO"
);

-- 11. 查询年龄大于30岁或者工作在416的员工信息（用集合查询完成）
SELECT * FROM "Reader" WHERE "Rage">30
UNION
SELECT * FROM "Reader" WHERE "Raddress"='416';

-- 12. 查询年龄大于30岁并且工作不在416的员工信息（用集合查询完成）
SELECT * FROM "Reader" WHERE "Rage">30
MINUS
SELECT * FROM "Reader" WHERE "Raddress"='416';

/* Oracle与MariaDB的差异 */

-- 使用AS关键词创建别名
SELECT COLUMN_NAME AS col FROM TABLE_NAME tb;  -- Oracle
SELECT COLUMN_NAME AS col FROM TABLE_NAME AS tb;  -- MariaDB
