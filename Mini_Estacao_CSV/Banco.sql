CREATE DATABASE arduino;

USE arduino;

CREATE TABLE `arduino`.`metereologia` (
  `Data e Hora` VARCHAR(45) NOT NULL,
  `Umidade` VARCHAR(45) NOT NULL,
  `Temperatura` VARCHAR(45) NOT NULL,
  `Orvalho` VARCHAR(45) NOT NULL,
  `Sensacao Termica` VARCHAR(45) NOT NULL,
  `Pressao Atmosferica` VARCHAR(45) NOT NULL,
  `Indice UV` VARCHAR(45) NOT NULL,
  `Nivel de Luz` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Data e Hora`));

SELECT * FROM arduino.metereologia;
