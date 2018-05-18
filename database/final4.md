#Chapter 4

## 4.6

```sql
-- 4.6.1
grant all priviledges on table Student to U1;
with
grant option;
-- 4.6.2 
grant select, update(addr) on table Student to U2;
-- 4.6.3 
grant select on table Class to public;
-- 4.6.4
grant update, select on table Student to R1;
-- 4.6.5
grant R1 to U1 with grant option;
```

## 4.7

```sql
-- 4.7.1
grant select on table Staff, Department to WangMing;
-- 4.7.2
grant insert, delete on table Staff, Department to LiYong;
-- 4.7.3
---- BUGGY
grant select on Staff when User()=name to public;
go
---- Worked
create view hole
as
  select *
  from Staff
  where OWNER=user;
go
grant select on hole to public;
-- 4.7.4
grant select, update(Salary) on table Staff to LiuXing;
-- 4.7.5
grant references on table Staff, Department to ZhangXin;
-- 4.7.6
grant all priviledges on table Staff, Department to ZhouPing with grant option;
go
-- 4.7.7
create view stat as
  select depart_id, max(Salary), min(Salary), average(Salary) 
  from Staff 
  group by depart_id;
go
grant select on stat to YangLan;
go
```
