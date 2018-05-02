select sname, city from S;
select pname, color, `weight` from P;

select distinct jno from SPJ where sno='S1';

select distinct pname, weight from P, SPJ where 
  P.pno = SPJ.pno and 
  jno = 'J1' 

(select sno from S where city='上海')
