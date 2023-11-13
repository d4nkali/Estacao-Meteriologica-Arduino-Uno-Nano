/*

  Programa para a mini estação meteriologica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), 
  Umidade com temperatura (DHT11), Pressão Atmosferica (BM_180) e Intensidade UV (GUVA-S12SD)
  com suporte extra ao Modulo Bluetooth (HC-06) 

  Autor: d4nkali
  Data: 13/11/2023

*/

/*

  Localização dos pinos no Arduino:
 
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

    GUVA-S12SD VCC: 5V
    GUVA-S12SD GND: GND
    GUVA-S12SD S: A1

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
  const int pinUV = A1; // Pino A1 sera o sensor de UV 

// Definir as variaveis

  int luz = 0; // Cria a variavel luz
  int valor_uv; // Cria a variavel inicial do UV
  int inten_uv; // Cria a variavel final do UV
 
// Traz a variavel da biblioteca

  dht DHT; 

// Chama a configuração da biblioteca

  Adafruit_BMP085 bmp; 

void setup() {

  Serial.begin(9600); // Inicia a comunicação serial

  if (!bmp.begin()) { // Se o BMP iniciar, então:

    // Caso não inicie:
    Serial.println("Não foi possível inicializar o BMP180"); // Imprimir no serial: "Não foi possível inicializar o BMP180"
    while (1); // Trava o programa

  }
 
  Wire.begin(); // Inicia a comunicação I2C no arduino

  pinMode(pinLDR, INPUT); //Coloca o LDR como entrada de informação
  pinMode(pinUV, INPUT); // Coloca o sensor UV como entrada

  delay(2000); // Aguarda de 2 segundos para carregar as informações
  
}

void loop() { 

  // Medição da pressão atmosferica do BMP_180

    float pressao = bmp.readPressure() / 100.0; // Cria a variavel pressão e divida por 100 para converter para hPa
    pressao *= 10; // Converter hPa para mbar

  // Medição e converção do UV do GUVA-S12SD

    valor_uv = analogRead(pinUV); // Ler o sensor UV e armazena na variavel
    inten_uv = map(valor_uv, 0, 1023, 0, 20); // Converter a leitura do sensor para o padrão de medição da OMS

  luz=analogRead(pinLDR); // Lê as informações do sensor de luminozidade

  // Impressão no monitor serial

    DHT.read11(pinDHT11); // Lê as informações do sensor de temperatura
    Serial.print("Umidade: ");  // Imprime o texto "Umidade"
    Serial.print(DHT.humidity); // Imprime no monitor o valor de umidade medido
    Serial.print("%"); // Imprime o "%"

    Serial.print(" / Temperatura: "); // Imprime o texto "Temperatura"
    Serial.print(DHT.temperature, 0); // imprime no monitor o valor de temperatura medido e remove a parte decimal
    Serial.print("*C");  // Imprime o "*C"

    Serial.print(" / Pressão: "); // Imprime o texto "Pressão"
    Serial.print(pressao); // Lê as informações da variavel "pressao"
    Serial.print(" mbar");  // Imprime o "mbar"

    Serial.print(" / Nivel UV: "); // Imprime a frase "Nivel UV: "
    Serial.print(inten_uv); // Imprime o valor convertido

    Serial.print(" / Luz: "); // Imprime o texto "Luz"
    Serial.print(luz); // Ler e imprime o valor do LDR
    Serial.println("L"); // Imprime o "L"

    delay(3000); // Aguarda 3 segundos. 
    //OBS: Não diminuir esse valor até 2000
  
}

// FIM!