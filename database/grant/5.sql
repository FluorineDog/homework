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
  CONSTRAINT CK_AGE check(age <= 60)
);

