-- MySQL dump 10.13  Distrib 5.7.18, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: homework
-- ------------------------------------------------------
-- Server version	5.7.18-1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `J`
--

DROP TABLE IF EXISTS `J`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `J` (
  `JNO` char(5) NOT NULL,
  `JNAME` char(20) DEFAULT NULL,
  `CITY` char(20) DEFAULT NULL,
  PRIMARY KEY (`JNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `J`
--

INSERT INTO `J` (`JNO`, `JNAME`, `CITY`) VALUES ('J1','三建','北京'),('J2','一汽','长春'),('J3','弹簧厂','天津'),('J4','造船厂','天津'),('J5','机车厂','唐山'),('J6','无线电厂','常州'),('J7','半导体厂','南京');

--
-- Table structure for table `P`
--

DROP TABLE IF EXISTS `P`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `P` (
  `PNO` char(5) NOT NULL,
  `PNAME` char(20) DEFAULT NULL,
  `COLOR` char(10) DEFAULT NULL,
  `WEIGHT` int(11) DEFAULT NULL,
  PRIMARY KEY (`PNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `P`
--

INSERT INTO `P` (`PNO`, `PNAME`, `COLOR`, `WEIGHT`) VALUES ('P1','螺母','红',12),('P2','螺栓','绿',17),('P3','螺丝刀','蓝',14),('P4','螺丝刀','红',14),('P5','凸轮','蓝',40),('P6','齿轮','红',30);

--
-- Table structure for table `S`
--

DROP TABLE IF EXISTS `S`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `S` (
  `SNO` char(5) NOT NULL,
  `SNAME` char(20) DEFAULT NULL,
  `STATUS` int(11) DEFAULT NULL,
  `CITY` char(20) DEFAULT NULL,
  PRIMARY KEY (`SNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `S`
--

INSERT INTO `S` (`SNO`, `SNAME`, `STATUS`, `CITY`) VALUES ('S1','精益',20,'天津'),('S2','盛锡',10,'北京'),('S3','东方红',30,'北京'),('S4','丰泰盛',20,'天津'),('S5','为民',30,'上海');

--
-- Table structure for table `SPJ`
--

DROP TABLE IF EXISTS `SPJ`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `SPJ` (
  `SNO` char(5) DEFAULT NULL,
  `PNO` char(5) DEFAULT NULL,
  `JNO` char(5) DEFAULT NULL,
  `QTY` int(11) DEFAULT NULL,
  KEY `FK_SPJ_SNO` (`SNO`),
  KEY `FK_SPJ_PNO` (`PNO`),
  KEY `FK_SPJ_JNO` (`JNO`),
  CONSTRAINT `FK_SPJ_JNO` FOREIGN KEY (`JNO`) REFERENCES `J` (`JNO`),
  CONSTRAINT `FK_SPJ_PNO` FOREIGN KEY (`PNO`) REFERENCES `P` (`PNO`),
  CONSTRAINT `FK_SPJ_SNO` FOREIGN KEY (`SNO`) REFERENCES `S` (`SNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SPJ`
--

INSERT INTO `SPJ` (`SNO`, `PNO`, `JNO`, `QTY`) VALUES ('S1','P1','J1',200),('S1','P1','J3',100),('S1','P1','J4',700),('S1','P2','J2',100),('S2','P3','J1',400),('S2','P3','J4',500),('S2','P3','J5',400),('S2','P5','J1',400),('S2','P5','J2',100),('S3','P1','J1',200),('S3','P3','J1',200),('S4','P5','J1',100),('S4','P6','J3',300),('S4','P6','J4',200),('S5','P2','J4',100),('S5','P3','J1',200),('S5','P6','J2',200),('S5','P6','J4',500),('S2','P3','J2',200);
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-05-01 22:28:01
