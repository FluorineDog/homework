/* Supplier */
create table S( 
  sno char(10) primary key,
  sname char(20),
  status smallint, 
  city char(20)
);

/* Part */
create table P(
  pno char(10) primary key, 
  pname char(20), 
  color char(10),
  weight smallint
);

/* proJect */ 
create table J(
  jno char(10) primary key, 
  jname char(20),
  city char(20)
);

/* supplies = <S, P, J> */
create table SPJ(
  sno char(10),
  pno char(10), 
  jno char(10), 
  /* quantity */
  qty int
);

