/* 1 */
select sno from SPJ where jno='J1'; 
/* 2 */
select sno from SPJ where jno='J1' and pno='P1';
/* 3 */
select sno from SPJ where 
  jno = 'J1' and 
  pno in (select pno from P where color='红');
/* 4 */
-- tianjiSupplier <- select sno from S where city='天津';
-- redPart <- select pno from P where color='红';
select jno from J where not exists(
  select * from SPJ where 
    sno in (select sno from S where city='天津') and
    pno in (select pno from P where color='红') and
    J.jno = SPJ.jno
);

/* 5 */
select jno from (select distinct SPJ.jno, count(SPJ.pno) from SPJ inner join (
    select distinct TMP.pno from SPJ as TMP where TMP.sno='S1'
  ) as REF on (SPJ.pno = REF.pno)
  group by SPJ.jno
  having count(SPJ.pno) = (
    select count(distinct TMP.pno) 
    from SPJ as TMP 
    where TMP.sno='S1'
  )) as final;
-- select * from SPJ inner join S1Part on (S1Part.pno=SPJ.pno);