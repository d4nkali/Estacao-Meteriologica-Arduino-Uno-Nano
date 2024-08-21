"""

Programa em Python que ler o Monitor Serial da Estação meteorológica e armazena os dados em um arquivo CSV.

OBS: Para parar o programa encerre a tarefa ou se for no terminal clique CTRL + C.

Autor: d4nkali
Data: 22/04/2024

"""

# Importa as bibliotecas
import serial, csv

# Pergunta e armazena nas variáveis
porta = input("Qual a porta que o Arduino está conectado? Exp: COM12 ")
freq = int(input("Qual a frequência estabelecida no Arduino? "))

ser = serial.Serial(porta, freq) #! Conecta ao Arduino

#* Abra o arquivo csv em modo de escrita
with open("log.csv", "w", newline="") as arq_csv:

  w_csv = csv.writer(arq_csv, delimiter=",")  # Definindo a vírgula como delimitador
  w_csv.writerow(["Data e Hora", "Umidade", "Temperatura", "Orvalho", "Sensacao Termica", "Pressao Atmosferica", "Indice UV", "Nivel de Luz"])  # Escreve os títulos das colunas

  while True: #* Cria um loop infinito

    print("Para parar o programa encerre a tarefa ou se for no terminal clique CTRL + C.")
    linha = ser.readline().decode("utf-8").strip() # Copia a linha do monitor serial
    val = linha.split(',') # Divide os valores com ','
    w_csv.writerow(val) # Escreve as mudanças no csv

# FIM!
