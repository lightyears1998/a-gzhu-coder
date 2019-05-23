/* 1 */
SELECT COUNT(object_name) FROM all_objects WHERE OWNER = 'SYSTEM';
-- 查询得共有502个数据库对象


/* 3 序列 */
SELECT COUNT(*) FROM all_objects WHERE OWNER = 'SYSTEM';
-- 显示502行。

SELECT object_name, OWNER FROM all_objects WHERE OWNER = 'light';
-- 显示6行，均为此用户在过往的实验中创建的表和约束。

CREATE SEQUENCE my_seq_01 INCREMENT BY 1 START WITH 1 NOMAXVALUE NOCYCLE;
CREATE SEQUENCE my_seq_02 INCREMENT BY 2 START WITH 1;

SELECT object_name, OWNER FROM all_objects WHERE OWNER = 'light';
-- 显示8行，新增2个序列对象。

SELECT object_name,object_type, OWNER FROM all_objects WHERE OWNER = 'SYSTEM' AND object_type='SEQUENCE';
-- 共有20行。

SELECT object_name, object_type, OWNER FROM all_objects WHERE OWNER = 'light' AND object_type='SEQUENCE';
-- 显示2行。

SELECT my_seq_01.NEXTVAL FROM dual;
-- 重复执行上述语句得到序列：1, 2, 3, 4, ...

ALTER SEQUENCE my_seq_01 INCREMENT BY 10;

SELECT my_seq_01.NEXTVAL FROM dual;
-- 重复执行上述语句得到序列：14（从上一个值继续）, 24, 34, 44, ...

SELECT my_seq_02.NEXTVAL FROM dual;
-- 重复执行上述语句得到序列：1, 3, 5, 7, ...

DROP SEQUENCE my_seq_02;

SELECT my_seq_02.NEXTVAL FROM dual; 
-- ORA-02289: 序列不存在

CREATE SEQUENCE my_seq_02 INCREMENT BY 3 START WITH 100;

SELECT my_seq_02.NEXTVAL FROM dual;
-- 重复执行上述语句得到序列：100, 103,106, 109, ...


/* 4 储存过程 */

-- 删除旧表和旧过程。
DECLARE
tmp INTEGER DEFAULT 0;
BEGIN
SELECT COUNT(*) INTO tmp FROM user_tables WHERE table_name='SC';
IF(tmp>0) THEN
EXECUTE IMMEDIATE 'drop table SC ';
END IF;
SELECT COUNT(*) INTO tmp FROM user_tables WHERE table_name='STUDENT';
IF(tmp>0) THEN
EXECUTE IMMEDIATE 'drop table STUDENT ';
END IF;
SELECT COUNT(*) INTO tmp FROM user_tables WHERE table_name='COURSE';
IF(tmp>0) THEN
EXECUTE IMMEDIATE 'drop table COURSE ';
END IF;
SELECT COUNT(*) INTO tmp FROM all_objects WHERE object_name='SC_INS' AND object_type='PROCEDURE';
IF(tmp>0) THEN
EXECUTE IMMEDIATE 'drop PROCEDURE SC_INS ';
END IF;
SELECT COUNT(*) INTO tmp FROM all_objects WHERE object_name='STUDENT_NO' AND object_type='SEQUENCE';
IF(tmp>0) THEN
EXECUTE IMMEDIATE 'drop SEQUENCE STUDENT_NO ';
END IF;
END;

-- 重新创建数据表。
CREATE TABLE student(sno INT PRIMARY KEY, sname VARCHAR2(8 CHAR));
CREATE TABLE course(cno INT PRIMARY KEY, cname VARCHAR2(10 CHAR));
CREATE TABLE sc(sno INT, cno INT, grade INT, 
      PRIMARY KEY(sno,cno), 
      FOREIGN KEY (sno) REFERENCES student(sno), FOREIGN KEY (cno) REFERENCES course(cno)
);
      

SELECT object_name, object_type, OWNER FROM all_objects WHERE OWNER = 'light';
-- 显示8行。

/** 索引因创建表的主键约束而产生。
 *
 * 例如SC表的索引由SNO, CNO产生。
 *
**/ 

CREATE SEQUENCE student_no INCREMENT BY 1 START WITH 2012001;

INSERT INTO student VALUES(student_no.NEXTVAL, 'aaaaaa');
INSERT INTO student VALUES(student_no.NEXTVAL, 'bbbbbbb');
INSERT INTO student VALUES(student_no.NEXTVAL, 'ccccccc');
INSERT INTO student VALUES(student_no.NEXTVAL, 'ddddddd');
COMMIT;
SELECT * FROM student;


INSERT INTO course VALUES (105, '程序设计');
INSERT INTO course VALUES (908, '大学英语');
INSERT INTO course VALUES (433, '数据结构');
COMMIT;
SELECT * FROM course;


CREATE PROCEDURE sc_ins(ino INT,cno INT,grade INT) IS
BEGIN
  IF(grade>=0) THEN INSERT INTO sc VALUES (ino,cno,grade);
  ELSE INSERT INTO sc VALUES (ino,cno,NULL);
END IF;
END;
-- Procedure SC_INS 已编译。

SELECT object_name, object_type, OWNER FROM all_objects WHERE OWNER = 'light' AND object_type='PROCEDURE';
-- 显示1行：SC_INS。

EXEC sc_ins (2012001,105,60);
EXEC sc_ins (2012001,908,0);
EXEC sc_ins (2012001,433,98);
EXEC sc_ins (2012002, 105,75);
EXEC sc_ins (2012002, 433,-1);
EXEC sc_ins (2012003, 105,64);
EXEC sc_ins (2012003, 908,90);
EXEC sc_ins (2012003, 433,-100);
-- PL/SQL 过程已成功完成。

SELECT student.sno,sname,cname,grade 
  FROM student,course,sc 
  WHERE student.sno=sc.sno AND course.cno=sc.cno;
/**
 * 如果成绩为负数的话，在数据表中为NULL值。
 * 成绩为0在表中的储存结果为0，成绩为负数在表中的储存结果为NULL。
 * 使用储存过程有简化操作、降低失误的可能性的好处。
**/


/* 5 触发器 */
ALTER TABLE sc ADD (gradelevel CHAR(1 CHAR));

UPDATE sc SET gradelevel='A' WHERE grade>=85;
UPDATE sc SET gradelevel='B' WHERE grade>=75 AND grade<85;
UPDATE sc SET gradelevel='C' WHERE grade>=60 AND grade<75;
UPDATE sc SET gradelevel='D' WHERE grade<60;

SELECT student.sno, sname, cname, grade, gradelevel
  FROM student,course,sc 
  WHERE student.sno=sc.sno AND course.cno=sc.cno;
-- 新增了四级评价的GradeLevel列。

CREATE OR REPLACE TRIGGER sc_ins BEFORE INSERT OR UPDATE ON sc
FOR EACH ROW
BEGIN
  IF :NEW.grade>=85 THEN :NEW.gradelevel:='A';
  ELSE IF :NEW.grade>=75 THEN :NEW.gradelevel:='B';
      ELSE IF :NEW.grade>=60 THEN :NEW.gradelevel:='C';
           ELSE IF :NEW.grade>=60 THEN :NEW.gradelevel:='D';
 END IF;
  END IF;
   END IF;
    END IF;
 END;
-- Trigger SC_INS 已编译。

SELECT * FROM sc WHERE sno=2012002;
INSERT INTO sc(sno, cno, grade) VALUES (2012002, 908, 80);
SELECT * FROM sc WHERE sno=2012002;
-- 对于新插入的行，GradeLevel列由触发器计算和生成。


ALTER TABLE course ADD (maxgrade INT);

UPDATE course SET maxgrade=0;
SELECT * FROM course;
-- 成功修改了COURSE表的结构，并将MaxGrade设置为0。

CREATE OR REPLACE TRIGGER course_ins BEFORE INSERT OR UPDATE ON sc
FOR EACH ROW
DECLARE oldg INT;
BEGIN
 SELECT maxgrade INTO oldg FROM course WHERE cno=:NEW.cno;
 IF oldg<:NEW.grade THEN UPDATE course SET maxgrade=:NEW.grade WHERE cno=:NEW.cno;
 END IF;
 END course_ins;
-- Trigger COURSE_INS 已编译。
-- 目前共有2个用户创建的触发器。

SELECT * FROM course;
-- 当前各科的最高分数均为0。

INSERT INTO sc(sno,cno,grade) VALUES (2012004,908,99);
INSERT INTO sc(sno,cno,grade) VALUES (2012004,433,88);
INSERT INTO sc(sno,cno,grade) VALUES (2012004,105,59);
SELECT * FROM sc;
SELECT * FROM course;
-- 插入成功。各科最高分也得到更新。

SELECT * FROM sc  WHERE sno=2012003 AND cno=105;
-- 2012003号同学的105号课程的分数为64，级别为C。

UPDATE sc SET grade=100 WHERE sno=2012003 AND cno=105;
SELECT * FROM sc WHERE sno=2012003 AND cno=105;
SELECT * FROM course;
-- 2012003号同学的105号课程的分数修改成功。
-- GradeLevel变化为A，各科的最高分(course.maxgrade)得到更新。
-- 单个修改语句，可以同时触发多个触发器。
