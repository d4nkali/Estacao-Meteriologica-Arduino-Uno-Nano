/*

 Programa para a mini estação meteriologica usando os sensores de medição de luz(LDR), 
 Umidade com temperatura(DHT11) e Pressão Atmosferica(BM_180) com o Modulo Bluetooth(HC-06)

 Localização dos pinos no Arduino (usando modelo NANO)
 
  Alimentação +: VIN
  Alimentação -: GND

  LDR Primeira Perna: 5V
  LDR Depois do resistor na segunda perna do LDR: A0
  LDR Segunda perna do resistor: GND
  
  DHT11 Perna Esquerda(-): GND
  DHT11 Perna do Meio: 5V
  DHT11 Perna Direita(S): A2

  BMP180 VIN: 3V3
  BMP180 GND: GND
  BMP180 SCL: A5
  BMP180 SDA: A4

  HC-06 VCC: 5V
  HC-06 GND: GND
  HC-06 TXD: RX
  HC-06 RXD: Depois do Resistor de 10k e do de 20K
  Primeira Perna Resistor de 10k: TX
  Segunda Perna Resistor de 20K: GND

  OBS *1: Coloca um resistor ou potenciometro na segunda perna do LDR.

  OBS *2: Para usar o pino RX corretamente deve fazer um divisor de tensão para não queimar o modulo.
  Então para isso deve colocar o fio do arduino em um resistor 10k e na outra ponta ligar outro resistor de 20 ou 22k, 
  no meio deles vai o fio do sensor e na outra ponta do de 22k vai um fio ao GND da placa.

*/ 

// Inclusão das bibliotecas

 #include "dht.h"
 #include <Wire.h>
 #include <Adafruit_BMP085.h>

// Definir os pinos

 const int pinDHT11 = A2; //Pino A2 sera o do sensor de temperatura
 const int pinLDR = A0; //Pino A0 sera o do sensor de luminozidade
 int luz = 0; //Cria a variavel luz
 
// Traz a variavel da biblioteca

 dht DHT; 

// Chama a configuração da biblioteca

 Adafruit_BMP085 bmp; 

void setup(){ // Programação inicial

  Serial.begin(9600); //Inicia a comunicação serial

 if (!bmp.begin()) {
    Serial.println("Não foi possível inicializar o BMP180");
    while (1);
 }
 
  pinMode(pinLDR, INPUT); //Coloca o LDR como entrada de informação

  delay(2000); // Aguarda de 2 segundos para carregar as informações
  
}

void loop(){ // Programação principal

 // Medição da pressão atmosferica do BMP_180

  float pressao = bmp.readPressure() / 100.0; // Cria a variavel pressão e divida por 100 para converter para hPa
  pressao *= 10; // Converter hPa para mbar

 // Impressão no monitor serial

  DHT.read11(pinDHT11); // Lê as informações do sensor de temperatura
  Serial.print("Umidade: ");  // Imprime o texto "Umidade"
  Serial.print(DHT.humidity); // Imprime no monitor o valor de umidade medido
  Serial.print("%"); // Imprime o "%"
  Serial.print(" / Temperatura: "); // Imprime o texto "Temperatura"
  Serial.print(DHT.temperature, 0); // imprime no monitor o valor de temperatura medido e remove a parte decimal
  Serial.print("*C"); // IMPRIME O TEXTO NA SERIAL
  Serial.print(" / Pressão: "); // Imprime o texto "Pressão"
  Serial.print(pressao); // Lê as informações da variavel "pressao"
  Serial.print(" mbar");  // Imprime o "mbar"
  luz=analogRead(pinLDR); // Lê as informações do sensor de luminozidade
  Serial.print(" / Luz: "); // Imprime o texto "Luz"
  Serial.print(luz); // Ler e imprime o valor do LDR
  Serial.println("L"); // Imprime o "L"
  delay(5000); // intervalo de 5 segundos. 
  //OBS: Não diminuir esse valor até 2000
  
}

// FIM!