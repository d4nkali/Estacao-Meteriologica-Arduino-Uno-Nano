/*

Script SQL para criar o banco de dados da Estação Meteorológica no PostgreSQL.

OBS: Executar os Scripts individualmente.

Autor: d4nkali
Data: 22/04/2024

*/

CREATE DATABASE arduino;

CREATE TABLE meteorologica (
  data_hora VARCHAR(45) NOT NULL,
  umidade VARCHAR(45) NOT NULL,
  temperatura VARCHAR(45) NOT NULL,
  orvalho VARCHAR(45) NOT NULL,
  sensacao_termica VARCHAR(45) NOT NULL,
  pressao_atmosferica VARCHAR(45) NOT NULL,
  indice_uv VARCHAR(45) NOT NULL,
  nivel_de_luz VARCHAR(45) NOT NULL,
  PRIMARY KEY (data_hora)
);

SELECT * FROM meteorologica;

-- FIM!
