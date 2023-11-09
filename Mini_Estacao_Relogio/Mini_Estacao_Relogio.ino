/*

 Programa para a mini estação meteriologica usando os sensores de medição de luz(LDR), Umidade com temperatura(DHT11) e Pressão Atmosferica(BM_180) com o Modulo Bluetooth(HC-06) e o Relogio (RTC DS1307) por d4n


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

  RTC DS1307 ou RTC 3231:

  VCC = 5V
  GND = GND
  SDA = A4 ou SDA
  SCL = A5 ou SCL

  OBS *1: Coloca um resistor ou potenciometro na segunda perna do LDR.

  OBS *2: Para usar o pino RX corretamente deve fazer um divisor de tensão para não queimar o modulo.
  Então para isso deve colocar o fio do arduino em um resistor 10k e na outra ponta ligar outro resistor de 20 ou 22k, 
  no meio deles vai o fio do sensor e na outra ponta do de 22k vai um fio ao GND da placa.

*/ 

// Inclusão das bibliotecas

 #include "dht.h"
 #include <Wire.h>
 #include <Adafruit_BMP085.h>
 #include "RTClib.h"

// Definir os pinos

 const int pinDHT11 = A2; // Pino A2 sera o do sensor de temperatura
 const int pinLDR = A0; // Pino A0 sera o do sensor de luminozidade
 int luz = 0; // Cria a variavel luz
 
// Traz a variavel da biblioteca

 dht DHT; 

// Chama a configuração da biblioteca

 Adafruit_BMP085 bmp; 

// Chama qual modulo vai ser usado 

 RTC_DS1307 rtc; // Modulo rtc DS1307
 //RTC_DS3231 rtc; // Modulo rtc DS3132

void setup(){ // Programação inicial

  Serial.begin(9600); //Inicia a comunicação serial

 if (!bmp.begin()) {
    Serial.println("Não foi possível inicializar o BMP180");
    while (1);
 }
 
  pinMode(pinLDR, INPUT); //Coloca o LDR como entrada de informação

  Wire.begin(); // Inicia a comunicação I2C no arduino  

  rtc.begin(); // Inicia a comunicação do relogio

  if (! rtc.isrunning()) { // Se o rtc iniciar, então:
  
    Serial.println("MODULO RTC NÃO INICIOU CORRETAMENTE!"); // Caso não inicie imprimir no serial: "MODULO RTC NÃO INICIOU CORRETAMENTE!"
    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajuste automatico do RTC
    
    //rtc.adjust(DateTime(2023, 9, 11, 27, 12, 00)); // Ajuste manual do RTC para a data e hora definida pelo usuario sendo o formato AAAA/MM/DD HH/mm/SS.
    //OBS: Quando for a primeira vez ou quando acabar a bateria, configure o RTC para data e hora atual descomentando a linha; quando terminar comnte na linha novamente
    
  }
  
  delay(2000); // Aguarda de 2 segundos para carregar as informações
  
}

void loop(){ // Programação principal

 // Medição da pressão atmosferica do BMP_180

  float pressao = bmp.readPressure() / 100.0; // Cria a variavel pressão e divida por 100 para converter para hPa
  pressao *= 10; // Converter hPa para mbar

 // Impressão no monitor serial
  DateTime now = rtc.now(); // Ler a hora e a data do modulo para imprimir no serial
  Serial.print("Data e hora atual: ");  // Imprime a mensagem: "Data e hora atual: "
  Serial.print(now.day(), DEC); // Imprime o dia
  Serial.print('/'); // Imprime (/)
  Serial.print(now.month(), DEC); // Imprime o mes
  Serial.print('/'); // Imprime (/)
  Serial.print(now.year(), DEC);  // Imprime o ano
  Serial.print(' ');  // Da espaço
  Serial.print(now.hour(), DEC);  // Imprime a hora
  Serial.print(':');  // Imprime (:)
  Serial.print(now.minute(), DEC); // Imprime o minuto
  Serial.print(':'); // Imprime (:)
  Serial.print(now.second(), DEC);  // Imprime os segundos
  Serial.print( " / " ); // Imprime uma barra
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
  Serial.println(" L"); // Imprime o "L"
  delay(3000); // intervalo de 3 segundos. 
  //OBS: Não diminuir esse valor até 2000
  
}

// FIM!