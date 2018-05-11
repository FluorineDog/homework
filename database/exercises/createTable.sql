drop table if exists show;
drop table if exists theater;
drop table if exists actin;
drop table if exists actor;
drop table if exists film;

create table film
(
  fid int primary key,
  fname char(30),
  ftype char(10),
  dname char(30),
  length int,
  is3d char(1),
  grade int
  CONSTRAINT RG_film_grade check (grade >= 0 and grade <= 100)
);
create table actor
(
  actid int primary key,
  fid int,
  isleading char(1),
  grade int,
  CONSTRAINT RG_isleading check (isleading in ('y', 'n'))
);

create table actin
(
  actid int,
  fid int,
  isleading char(1),
  grade int,
  constraint PK_actid_fid primary key (actid, fid),
  CONSTRAINT FK_fid FOREIGN KEY(fid) REFERENCES film(fid),
  CONSTRAINT FK_actid FOREIGN KEY(actid) REFERENCES actor(actid),
  CONSTRAINT RG_actin_grade check (grade >= 0 and grade <= 100)
);
create table theater
(
  tid int primary key,
  tname char(20),
  tarea char(20),
  addr char(30)
);
create table show
(
  fid int,
  tid int,
  price int,
  year int,
  month int,
  constraint PK_fid_tid primary key (fid, tid)
);
