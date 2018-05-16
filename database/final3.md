# Chapter 3
## 3.3

```sql
drop table if exists S;
drop table if exists T;

create table S(
  A int, 
  B int, 
  C int, 
  D int
);

create table T(
  C int,
  D int,
  E int,
  F int
);

insert into S values
(1, 2, 3, 4),
(2, 2, 3, 4),
(3, 2, 4, 4),
(1, 2, 4, 4);

insert into T values
(3, 4, 3, 4),
(4, 4, 3, 4),
(3, 2, 4, 4),
(1, 2, 4, 4);

-- 1
select * from S where A=10;

-- 2
select A,B from S;

-- 3
select * from S inner join T on (S.C=T.C and S.D=T.D);

-- 4
select A, B, S.C as C1, S.D as D1, T.C as C2, T.D as D2, E, F 
  from S inner join T on (S.C=T.C);

-- 5
select A, B, S.C as C1, S.D as D1, T.C as C2, T.D as D2, E, F 
  from S, T where (A<E);

-- 6
select TMP.C as C1, TMP.D as D1, T.C as C2, T.D as D2, E, F 
  from (select distinct C, D from S) as TMP, T;
```
## 3.4


```sql
/* 1 */
select sno
from SPJ
where jno='J1';
/* 2 */
select sno
from SPJ
where jno='J1' and pno='P1';
/* 3 */
select sno
from SPJ
where 
  jno = 'J1' and pno in (select pno
  from P
  where color='红');
/* 4 */
-- tianjiSupplier <- select sno from S where city='天津';
-- redPart <- select pno from P where color='红';
select jno
from J
where not exists(
  select *
from SPJ
where 
    sno in (select sno
  from S
  where city='天津') and pno in (select pno
  from P
  where color='红') and J.jno = SPJ.jno
);
/* 5 */
select distinct SPJ.jno
from SPJ inner join (
    select distinct TMP.pno
  from SPJ as TMP
  where TMP.sno='S1'
  ) as REF on (SPJ.pno = REF.pno)
group by SPJ.jno
having count(SPJ.pno) in (
    select count(distinct TMP.pno)
from SPJ as TMP
where TMP.sno='S1'
  )
-- go
-- select * from SPJ inner join S1Part on (S1Part.pno=SPJ.pno);
```
## 3.5
```sql 
-- 1
select sname, city from S;

-- 2
select pname, color, weight from P;

-- 3
select distinct jno from SPJ where sno='S1';

-- 4
select pname, sum(qty) as sum_qty from P, SPJ where 
  P.pno = SPJ.pno and 
  jno = 'J2'
  group by pname;
  
-- 5
select distinct pno from S, SPJ where 
  city='上海' and 
  S.sno = SPJ.sno;
  
-- 6 
select distinct jname from S, SPJ, J where
  S.sno = SPJ.sno and
  J.jno = SPJ.jno and
  S.city = '上海';

-- 7
select J.jno from J where not exists(
  select * from SPJ, S where 
    J.jno = SPJ.jno and
    SPJ.sno = S.sno and 
    S.city = '天津'
);

-- 8
update P set color='蓝' where color='红';

-- 9
update SPJ set sno='S3' where sno='S5' and jno='J4' and pno='P6';

-- 10 /* on delete cascade */
delete from S where sno='S2';

-- 11 
insert into SPJ value('S2', 'P4', 'J6', 200);

```