"""

Programa em Python que ler o Monitor Serial da Estação Meteorológica e armazena os dados em um arquivo CSV.

Autor: d4nkali
Data: 17/03/2024

"""

# Importa as bibliotecas
import csv, serial, os
import sqlite3 as db
from dotenv import load_dotenv
import pandas as pd

#? Carrega o arquivo dotenv e resgata as variáveis 
load_dotenv() 
BANCO = os.getenv("BANCO")

#* Mudar para o nome do banco de dados ou usar dotenv
banco_conectar = db.connect(BANCO)

# Pergunta e armazena nas variáveis frequência e porta da conexão da placa no PC
porta = input("Qual a porta que o Arduino está conectado? Exp: COM12 ")
freq = int(input("Qual a frequência estabelecida no Arduino? "))

ser = serial.Serial(porta, freq) #! Conecta ao Arduino

selecao = input("Olá você deseja salvar as informações em um arquivo CSV ou inserir os dados de um arquivo CSV no Banco de Dados SQLite? (csv/sqlite)")


#? Cria definições para cada banco

def csv_mysql():

	w_csv.writerow(["Data e Hora", "Umidade", "Temperatura", "Orvalho", "Sensacao Termica", "Pressao Atmosferica", "Indice UV", "Nivel de Luz"])  # Escreve os títulos das colunas

def csv_sqlite_postgre():

	w_csv.writerow(["data_hora", "umidade", "temperatura", "orvalho", "sensacao_termica", "pressao_atmosferica", "indice_uv", "nivel_de_luz"])

if selecao == "csv": #* Se selecionar opção 'csv'

	selecao_banco = input("Qual o banco que voce deseja salvar as informações no CSV? (mysql/postgre/sqlite)")

	#* Abra o arquivo csv em modo de escrita
	with open("log.csv", "w", newline="") as arq_csv:

		print("Para parar o programa, finalize a tarefa ou se for no terminal clique CTRL + C.")
		w_csv = csv.writer(arq_csv, delimiter=",")  # Definindo a vírgula como delimitador

		if selecao_banco == "mysql":

			csv_mysql()

		if selecao_banco == "postgre" or "sqlite":

			csv_sqlite_postgre()

		else:

			print("Digite uma das alternativas corretas")

		while True: #* Cria um loop infinito

			linha = ser.readline().decode("utf-8").strip() # Copia a linha do monitor serial
			val = linha.split(',') # Divide os valores com ','
			w_csv.writerow(val) # Escreve as mudanças no csv

elif selecao == "sqlite": #* Se selecionar opção 'csv'

	#* Ler o arquivo e envia as informações para o banco de dados
	informacoes = pd.read_csv("log.csv")
	informacoes.to_sql("metereologia", banco_conectar, if_exists="append", index=False)

	#! Envia as informações para o banco e fecha a conexão
	banco_conectar.commit()
	banco_conectar.close()

	print("Dados inseridos com sucesso!")

else:

	print("Digite uma das alternativas corretas")

# FIM!
