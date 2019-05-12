/* 创建新用户并授权 */
CREATE USER "exp3" IDENTIFIED BY "exp3pwd";
GRANT RESOURCE, CONNECT TO "exp3";

/* 基本数据 */

-- 创建Reader表并插入初始数据。
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

-- 创建Book表并插入初始数据。
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

-- 创建RB表并插入数据。
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

/* 基本操作  */

-- 5. 查询记录：在Reader表中查询直接上司是“李四”的员工的名字。
SELECT "Rname" FROM "Reader"
WHERE "Rboss"='李四';

-- 6.修改记录：在Reader表中把直接上司是“李四”的员工的办公地点统一改为“420”。
UPDATE "Reader" SET "Raddress"='420'
WHERE "Rboss"='李四';

-- 8. 删除记录：在Reader表中把直接上司未赋值（NULL）的记录删去。
DELETE FROM "Reader" WHERE "Rboss" IS NULL;

-- 9. 删去数据表：把整个Reader表删去。
DROP TABLE "Reader";

-- 11. 创建表格Reader2，比较Reader2和Reader中的记录和结构是否相同。
CREATE TABLE "Reader2" AS SELECT * FROM "Reader";
DESC "Reader"; 
DESC "Reader2";

-- 11+. 从多个数据源复制数据到新表。
CREATE TABLE "Reader" AS
SELECT * FROM "Reader1"
UNION ALL
SELECT * FROM "Reader2";

-- 12. 分别执行下面的每行语句，查看语句是否执行成功，分析为什么？
UPDATE "Reader" SET "RNO"='R001' WHERE "Rname"='张三';
UPDATE "Reader2" SET "RNO"='R001' WHERE "Rname"='张三';
INSERT INTO "Reader2" ("RNO", "Rname", "Rsex", "Rage", "Rboss", "Raddress") 
VALUES(NULL, 'Lisi', NULL, NULL, NULL, NULL);

-- 13. 删除Reader2表格。
DROP TABLE "Reader2";

/* 查询Reader表中创建的约束类型 */

-- 1. 向RB表中插入一条R010的借书记录
INSERT INTO "RB"("RNO", "BNO") VALUES('R010','B005');

-- 2. 尝试删除R010员工
DELETE FROM "Reader" WHERE "RNO"='R010';

-- 3. 设法删除Reader中的R010员工

-- 3.a) 先把RB中所有’R010’的借书记录都删掉
DELETE FROM "RB" WHERE "RNO"='R010';
DELETE FROM "Reader" WHERE "RNO"='R010';

-- 3.b) 修改RB表的结构中外键的定义，允许级联删除
-- 确认旧外键约束的名称
SELECT constraint_name FROM user_constraints
WHERE table_name='RB' AND constraint_type='R'
AND r_constraint_name=(
    SELECT constraint_name FROM user_constraints
    WHERE table_name='Reader' AND constraint_type='P'
);
-- 删除旧的外键约束
ALTER TABLE "RB"
DROP CONSTRAINT SYS_C007345;
-- 建立新的外键约束
ALTER TABLE "RB"
ADD FOREIGN KEY ("RNO") REFERENCES "Reader"("RNO")
ON DELETE CASCADE;
-- 删除记录
DELETE FROM "Reader" WHERE "RNO"='R010';

-- 注：不能修改约束，只能删除约束后重建

-- 4. 为Reader表添加一个属性列“出生年份”，名为Rbirthday，整数
ALTER TABLE "Reader"
ADD "Rbirthday" INT;

-- 5. 对于Reader表格，员工编号可以确定年龄，年龄又可以确定出生年份，因此存在传递函数依赖关系，删除Rbirthday列，使关系模式符合第三范式要求
ALTER TABLE "Reader"
DROP COLUMN "Rbirthday";  -- 注意添加列时不需要指明COLUMN但删除列时需要指明COLMN

-- 6. 修改Reader表格的Raddress属性，使其长度为50，数据类型不变
ALTER TABLE "Reader"
MODIFY "Raddress" VARCHAR2(50 CHAR);

-- 7. 修改book表的Bprice属性，使其值得范围在10到100之间
ALTER TABLE "Book"
ADD CHECK ("Bprice" BETWEEN 10 AND 100);

-- 8. 修改Reader表的Rage属性，使其值得范围为16到60之间。
ALTER TABLE "Reader"
ADD CHECK ("Rage" BETWEEN 16 AND 60);

-- 9. 尝试不带CASCADE的和带CASCADE选项的语句删除READER表
DROP TABLE "Reader";  -- 无法删除，表中的属性被其他表的外键所引用。
DROP TABLE "Reader" CASCADE CONSTRAINTS;

/* 索引的建立与删除 */

-- 2. 为Reader表的Rname建立Unique索引
CREATE UNIQUE INDEX "Rname" ON "Reader"("Rname");

-- 2+. 可以建立普通索引
CREATE INDEX "Rname" ON "Reader"("Rname");

-- 2+. 删除重复的Rname键后建立唯一索引
-- 在删除Reader表中Rname重复的记录前，先删除与之以外键约束关联的RB表中的记录
DELETE FROM "RB"
WHERE "RNO" IN (
    SELECT "RNO" FROM "Reader" a
    WHERE ROWID > (
        SELECT MIN(ROWID) FROM "Reader" b
        WHERE b."Rname"=a."Rname"
    )
);

-- 删除Reader表中Rname重复的记录
DELETE FROM "Reader" a
WHERE ROWID > (
    SELECT MIN(ROWID) FROM "Reader" b
    WHERE b."Rname"=a."Rname"
);

-- 建立唯一索引
CREATE UNIQUE INDEX "Rname" ON "Reader"("Rname");

-- 3. 删除索引
DROP INDEX "Rname";

/* 视图 */

-- 1. 授权
GRANT RESOURCE, CONNECT, DBA TO exp3;

-- 2. 建立在416办公室工作的视图V416
CREATE VIEW "V416" AS SELECT "RNO", "Rname", "Rage" FROM "Reader" WHERE "Raddress"='416';

-- 3. 从视图中查询年龄大于30的员工的信息
SELECT * FROM "V416" WHERE "Rage">30;

-- 4. 向视图V416中插入一条新的员工记录，然后从V416中查找该条记录，测试是否可以找到
INSERT INTO "V416" ("RNO", "Rname", "Rage") VALUES('R999', '新人', 99);
SELECT * FROM "Reader";
SELECT * FROM "V416";  -- 向Reader表中插入成功，但由于新人的Raddress不是416，因此不会在V416中出现。

-- 5. 建立在417办公室工作的视图V417，视图包括员工的编号、姓名、性别、年龄等信息，视图定义带with check option选项
CREATE VIEW "V417" AS 
SELECT "RNO", "Rname", "Rsex", "Rage", "Raddress" FROM "Reader" WHERE "Raddress"='417'
WITH CHECK OPTION;

-- 6. 向视图V417中插入一条新的员工记录，然后从V417中查找该条记录，测试是否可以找到
INSERT INTO "V417" ("RNO", "Rname", "Rage")
VALUES('R777', '417新人', 66);  -- 违反了With Check Option选项，插入失败

INSERT INTO "V417" ("RNO", "Rname", "Rage", "Raddress")
VALUES('R777', '417新人', 66, '417');  -- 插入成功

-- 7. 通过视图删除刚插入的员工记录
DELETE FROM "V417" WHERE "RNO"='R777';

-- 8. 在视图V417上建立所有女员工信息的视图FV417，查询视图结果
CREATE VIEW "FV417" AS
SELECT * FROM "V417"
WHERE "Rsex"='女';

SELECT * FROM "FV417";

-- 9. 删除视图V417中没有借阅图书的员工信息
DELETE FROM "V417" where "V417"."RNO" NOT IN (SELECT "RNO" FROM "RB");

-- 10. 建立视图GV，数据包括每本图书的编号及其借阅数量
CREATE VIEW "GV" AS
SELECT "BNO", COUNT(*) "Bcount" FROM "RB"
GROUP BY "BNO";  -- 注意必须为视图中的列创建别名

-- 11. 删除前几步中创建的视图
DROP VIEW "GV";
DROP VIEW "FV417";
DROP VIEW "V417";
DROP VIEW "V416";

/* 触发器 */
-- 在用户执行删除某个员工的时候触发，功能是先删除RB中该员工的借书记录，然后删除Reader中该员工记录
CREATE TRIGGER "REMOVE_RELATED_RECORDS"
BEFORE DELETE ON "Reader"
FOR EACH ROW
BEGIN
   DELETE FROM "RB"
   WHERE "RNO"=:old."RNO";
END;
