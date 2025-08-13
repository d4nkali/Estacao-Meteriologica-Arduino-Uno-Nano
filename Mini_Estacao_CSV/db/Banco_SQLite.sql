/*

Script SQL para criar o banco de dados da Estação Meteorológica no SQLite.

Autor: d4nkali
Data: 09/09/2024

*/

CREATE TABLE meteorologia (
  data_hora TEXT NOT NULL,
  umidade TEXT NOT NULL,
  temperatura TEXT NOT NULL,
  orvalho TEXT NOT NULL,
  sensacao_termica TEXT NOT NULL,
  pressao_atmosferica TEXT NOT NULL,
  indice_uv TEXT NOT NULL,
  nivel_luz TEXT NOT NULL,
  PRIMARY KEY (data_hora)
);

SELECT * FROM meteorologia;

-- FIM!
