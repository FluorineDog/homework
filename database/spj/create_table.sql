/* Supplier */

drop table if exists SPJ;
drop table if exists S;
create table S( 
  sno char(10) primary key,
  sname char(20),
  status smallint, 
  city char(20)
);

/* Part */
drop table if exists P;
create table P(
  pno char(10) primary key, 
  pname char(20), 
  color char(10),
  weight smallint
);

/* proJect */ 
drop table if exists J;
create table J(
  jno char(10) primary key, 
  jname char(20),
  city char(20)
);

/* supplies = <S, P, J> */
drop table if exists SPJ;
create table SPJ(
  sno char(10),
  pno char(10), 
  jno char(10), 
  /* quantity */
  qty int,
  constraint fk_spj_sno foreign key(sno) references S(sno) on delete cascade,
  constraint fk_spj_pno foreign key(pno) references P(pno) on delete cascade,
  constraint fk_spj_jno foreign key(jno) references J(jno) on delete cascade
);

'J6','J6',
INSERT INTO S (sno, sname, status, city) VALUES 
('S1', '精益', 20, '天津'), 
('S2', '盛锡', 10, '北京'), 
('S3', '东方红', 30, '北京'), 
('S4', '丰泰盛', 20, '天津'), 
('S5', '为民', 30, '上海');

INSERT INTO P (pno, pname, color, weight) VALUES 
('P1', '螺母', '红', 12), 
('P2', '螺栓', '绿', 17), 
('P3', '螺丝刀', '蓝', 14), 
('P4', '螺丝刀', '红', 14), 
('P5', '凸轮', '蓝', 40), 
('P6', '齿轮', '红', 30);

insert into J values 
('J1', '三建', '北京'), 
('J2', '一汽', '长春'), 
('J3', '弹簧厂', '天津'), 
('J4', '造船厂', '天津'), 
('J5', '机车厂', '唐山'), 
('J6', '无线电厂', '常州'), 
('J7', '半导体厂', '南京');

INSERT INTO SPJ (sno, pno, jno, qty) VALUES 
('S1', 'P1', 'J1', 200), 
('S1', 'P1', 'J3', 100), 
('S1', 'P1', 'J4', 700), 
('S1', 'P2', 'J2', 100), 
('S2', 'P3', 'J1', 400), 
('S2', 'P3', 'J2', 200),
('S2', 'P3', 'J4', 500), 
('S2', 'P3', 'J5', 400), 
('S2', 'P5', 'J1', 400), 
('S2', 'P5', 'J2', 100), 
('S3', 'P1', 'J1', 200), 
('S3', 'P3', 'J1', 200), 
('S4', 'P5', 'J1', 100), 
('S4', 'P6', 'J3', 300), 
('S4', 'P6', 'J4', 200), 
('S5', 'P2', 'J4', 100), 
('S5', 'P3', 'J1', 200), 
('S5', 'P6', 'J2', 200), 
('S5', 'P6', 'J4', 500);
