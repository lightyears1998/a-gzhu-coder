-- 创建S表
create table "S"(
    "SNO" integer primary key,
    "SName" nvarchar2(16) not null,
    "City" nvarchar2(16) not null,
    "Status" nvarchar2(16) check("Status" in ('正常', '停工')) not null
);


-- 同一个城市不存在同名的两个工厂
create unique index "SName_City_UK" on "S" (
	"SName" DESC,
	"City" DESC
);


-- 创建P表
create table "P"(
    "PNO" integer primary key,
    "PName" nvarchar2(16) not null,
    "Weight" number not null,
    "Color" nvarchar2(16) not null,
    "City" nvarchar2(16) not null
);


-- 创建SP表
create table "SP"(
    "SNO" integer references "S"("SNO"),
    "PNO" integer references "P"("PNO"),
    "Qty" integer not null,
	primary key ("SNO", "PNO")
);


-- 用于产生ID的序列
create sequence "UIDSequence"
start with 1
increment by 1
nocycle;


-- 为插入语句绑定触发器
create trigger "AutoID_S" before insert
on "S" for each row
begin
	select "UIDSequence".nextval into :new."SNO" from dual;
end;

create trigger "AutoID_P" before insert
on "P" for each row
begin
	select "UIDSequence".nextval into :new."PNO" from dual;
end;


-- 插入S表数据
insert into "S" ("SName", "City", "Status") values ('广岭重工', '郑州', '正常');
insert into "S" ("SName", "City", "Status") values ('神奇化工', '郑州', '正常');
insert into "S" ("SName", "City", "Status") values ('恒阳一汽', '郑州', '正常');
insert into "S" ("SName", "City", "Status") values ('福安通化', '长沙', '正常');
insert into "S" ("SName", "City", "Status") values ('黑钢国际', '沈阳', '正常');
insert into "S" ("SName", "City", "Status") values ('碱叶五代', '天津', '停工');
insert into "S" ("SName", "City", "Status") values ('海口制造', '海口', '正常');


-- 插入P表数据
insert into "P" ("PName", "Weight", "Color", "City") values ('双铜', 34, '紫黑', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('双铜', 34, '紫黑', '广州');
insert into "P" ("PName", "Weight", "Color", "City") values ('赤金', 20, '金', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('RMA740', 99, '五颜六色', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('RMA740', 99, '五颜六色', '广州');
insert into "P" ("PName", "Weight", "Color", "City") values ('碱叶', 12, '白', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('黑钢', 86, '黑', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('硫酸', 100, '黄', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('硫酸', 100, '黄', '广州');
insert into "P" ("PName", "Weight", "Color", "City") values ('氮', 8, '无', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('氮', 8, '无', '广州');
insert into "P" ("PName", "Weight", "Color", "City") values ('龙币', 2, '蓝', '广州');
insert into "P" ("PName", "Weight", "Color", "City") values ('一律华尔钠', 35, '白', '康定');
insert into "P" ("PName", "Weight", "Color", "City") values ('达安', 22, '浅绿', '康定');


-- 插入SP表数据
insert into "SP" ("SNO", "PNO", "Qty") values (1, 8, 1);
insert into "SP" ("SNO", "PNO", "Qty") values (2, 9, 2);
insert into "SP" ("SNO", "PNO", "Qty") values (3, 10, 3);
insert into "SP" ("SNO", "PNO", "Qty") values (4, 11, 4);
insert into "SP" ("SNO", "PNO", "Qty") values (5, 12, 5);
insert into "SP" ("SNO", "PNO", "Qty") values (6, 13, 6);
insert into "SP" ("SNO", "PNO", "Qty") values (7, 14, 7);
insert into "SP" ("SNO", "PNO", "Qty") values (1, 15, 8);
insert into "SP" ("SNO", "PNO", "Qty") values (2, 16, 9);
insert into "SP" ("SNO", "PNO", "Qty") values (3, 17, 10);
insert into "SP" ("SNO", "PNO", "Qty") values (4, 18, 11);
insert into "SP" ("SNO", "PNO", "Qty") values (5, 19, 12);
insert into "SP" ("SNO", "PNO", "Qty") values (6, 20, 13);
insert into "SP" ("SNO", "PNO", "Qty") values (7, 21, 14);
insert into "SP" ("SNO", "PNO", "Qty") values (1, 9, 15);
insert into "SP" ("SNO", "PNO", "Qty") values (2, 10, 16);
insert into "SP" ("SNO", "PNO", "Qty") values (3, 11, 17);
insert into "SP" ("SNO", "PNO", "Qty") values (4, 12, 18);
insert into "SP" ("SNO", "PNO", "Qty") values (5, 13, 19);
insert into "SP" ("SNO", "PNO", "Qty") values (6, 14, 20);
insert into "SP" ("SNO", "PNO", "Qty") values (7, 15, 21);
insert into "SP" ("SNO", "PNO", "Qty") values (1, 16, 22);
insert into "SP" ("SNO", "PNO", "Qty") values (2, 17, 23);
insert into "SP" ("SNO", "PNO", "Qty") values (3, 18, 24);
insert into "SP" ("SNO", "PNO", "Qty") values (4, 19, 25);
insert into "SP" ("SNO", "PNO", "Qty") values (5, 20, 26);
insert into "SP" ("SNO", "PNO", "Qty") values (6, 21, 27);
insert into "SP" ("SNO", "PNO", "Qty") values (7, 8, 28);


-- SP表人类友好视图
create or replace view "FriendlySP" 
as
select "SName", "S"."City" "SCity", "Status" "SStatus", "PName", "Weight", "Color", "P"."City" "PCity", "Qty"
from "P", "S", "SP"
where "SP"."PNO"="P"."PNO" and "SP"."SNO"="S"."SNO"
with check option;


-- 正常运作的工厂一览视图
create or replace view "WokingSupplier"
as
select "SName", "City", "Status"
from "S"
where "S"."Status"='正常'
with check option;


-- 广州零件一览视图
create or replace view "PartsOfGuangzhou"
as 
select *
from "FriendlySP"
where "PCity"='广州'
with check option;


-- 康定零件一览视图
create or replace view "PartsOfKangding"
as 
select *
from "FriendlySP"
where "PCity"='康定'
with check option;
