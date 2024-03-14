/*

  Programa para a mini estação meteriologica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), 
  Umidade com temperatura (DHT11), Pressão Atmosferica (BM_180) e Intensidade UV (GUVA-S12SD)
  com suporte extra ao Modulo Bluetooth (HC-06) 

  Autor: d4nkali
  Data: 14/03/2024

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

// Definindo os pinos e variaveis

  const int pinLDR = A0, pinUV = A1, pinDHT11 = A2; // Define o LDR no A0, UV no A1 e DHT11 no A2
  float umidade, temp, orvalho, sen_termica, pressao; // Define as variaveis de valores flutuantes
  int valor_uv, inten_uv, luz = 0;  // Define as variaveis de valores inteiros
 
// Chama as configurações das bibliotecas

  dht DHT; 
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

void medir_temperatura() { // Cria uma função para a medição da temperatura, ponto de orvalho e sensaçao termica do DHT_11

  umidade = DHT.humidity; // Armazena a umidade na variavel "umidade"
  temp = DHT.temperature; // Armazena a temperatura na variavel "temp"
  orvalho = temp - (100 - umidade) / 5; // Faz o calculo do Ponto de Orvalho e armazena na variavel
  sen_termica = 13.12 + 0.6215 * temp - 11.37 * pow(umidade, 0.16) + 0.3965 * temp * pow(umidade, 0.16); // Calculo da sensação termica e armazena na variavel

}

void medir_pressao() { // Cria uma função para a medição da pressão atmosferica do BMP_180

  pressao = bmp.readPressure() / 100.0; // Cria a variavel pressão e divida por 100 para converter para hPa
  pressao *= 10; // Converter hPa para mbar

}

void medir_uv() { // Cria uma função para a medição e converção do UV do GUVA-S12SD

  valor_uv = analogRead(pinUV); // Ler o sensor UV e armazena na variavel
  inten_uv = map(valor_uv, 0, 1023, 0, 20); // Converter a leitura do sensor para o padrão de medição da OMS

}

void print_serial () { // Cria a função para imprimir as informações no monitor serial

  Serial.print("Umidade: ");  // Imprime o texto "Umidade"
  Serial.print(umidade); // Imprime no monitor o valor de umidade 
  Serial.print("%"); // Imprime o "%"

  Serial.print(" / Temperatura: "); // Imprime o texto "Temperatura"
  Serial.print(temp, 0); // imprime no monitor o valor de temperatura 
  Serial.print("*C");  // Imprime o "*C"

  Serial.print(" / Orvalho: "); // Imprime o texto "Orvalho"
  Serial.print(orvalho, 0); // 
  Serial.print("*C"); // Imprime o "*C"

  Serial.print(" / Sensação Termica: "); // Imprime o texto "Sensação Termica"
  Serial.print(sen_termica, 0);
  Serial.print("*C"); // Imprime o "*C"

  Serial.print(" / Pressão: "); // Imprime o texto "Pressão"
  Serial.print(pressao, 0); // Lê as informações da variavel "pressao"
  Serial.print(" mbar");  // Imprime o "mbar"

  Serial.print(" / Nivel UV: "); // Imprime a frase "Nivel UV: "
  Serial.print(inten_uv); // Imprime o valor convertido

  Serial.print(" / Luz: "); // Imprime o texto "Luz"
  Serial.print(luz); // Ler e imprime o valor do LDR
  Serial.println("L"); // Imprime o "L"

  delay(3000); // Aguarda 3 segundos. 
  //OBS: Não diminuir esse valor até 2000

}

void loop() { 

  luz=analogRead(pinLDR); // Lê as informações do sensor de luminozidade
  DHT.read11(pinDHT11); // Lê as informações do sensor de temperatura

  // Chama e executa as funções

    medir_temperatura();
    medir_pressao();
    medir_uv();
    print_serial();
    
}

// FIM!