# Chapter 5
## 5.6

```sql 
-- 
create table Department(
  dpid char(20) primary key,
  dname char(20),
  manager char(20),
  phone char(20)
);

create table Staff(
  sid char(20) primary key, 
  sname char(20), 
  age char(20), 
  title char(20), 
  salary int, 
  dpid char(20) REFERENCES Department(dpid), 
  CONSTRAINT CK_AGE_LE_60 check(age <= 60)
);
```

## 5.7 

违反实体完整性时, 一般直接拒绝操作
违反参照完整性时, 根据不同的constraint配置, 可能会拒绝操作或者级联更新删除
违反用户定义的完整性时, 可能拒绝操作, 或者使用触发器解决. 
