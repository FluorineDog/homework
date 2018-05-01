create table Student(
  stu_no char(9) primary key,
  stu_name char(20) unique, 
  stu_sex char(2), 
  stu_age smallint, 
  stu_dept char(20)
);


create table Course(
  crs_no char(4) primary key, 
  crs_name char(40) not null,
  crs_pno char(4),
  crs_credit smallint, 
  foreign key (crs_pno) references Course(crs_no)
);

create table SC(
  stu_no char(9),
  crs_no char(4),
  grade smallint, 
  primary key (stu_no, crs_no),
  foreign key (stu_no) references Student(stu_no),
  foreign key (crs_no) references Course(crs_no)
);