# Teste de importar dados do Arduino via monitor serial para o computador por um arquivo csv

# Importa as bibliotecas
import serial, csv

# Pergunta e armazena nas variáveis
porta = input("Qual a porta que o Arduino esta conectado? Exp: COM12 ")
freq = int(input("Qual a frequência estabelecida no Arduino? "))

ser = serial.Serial(porta, freq) #! Conecta ao Arduino

#* Abra o arquivo csv em modo de escrita
with open("log.csv", "w", newline="") as arq_csv:

  w_csv = csv.writer(arq_csv, delimiter=",")  # Definindo a vírgula como delimitador
  w_csv.writerow(["Data e Hora", "Umidade", "Temperatura", "Orvalho", "Sensacao Termica", "Pressao Atmosferica", "Indice UV", "Nivel de Luz"])  # Escreve os títulos das colunas

  while True: #* Cria um loop infinito

    linha = ser.readline().decode("utf-8").strip() # Copia a linha do monitor serial
    val = linha.split(',') # Divide os valores com ','
    w_csv.writerow(val) # Escreve as mudanças no csv

# FIM!