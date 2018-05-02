-- 1
select sname, city from S;

-- 2
select pname, color, `weight` from P;

-- 3
select distinct jno from SPJ where sno='S1';

-- 4
select pname, sum(qty) from P, SPJ where 
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
-- update P set color='蓝' where color='红';

-- 9
-- update SPJ set sno='S3' where sno='S5' and jno='J4' and pno='P6';

-- 10 /* on delete cascade */
-- delete from S where sno='S2';

-- 11 
-- insert into SPJ value('S2', 'P4', 'J6', 200);
