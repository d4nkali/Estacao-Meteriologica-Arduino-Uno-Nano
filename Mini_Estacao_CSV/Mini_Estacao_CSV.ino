/*

  Programa para a mini estação meteorológica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), 
  Umidade com temperatura (DHT11), Pressão Atmosférica (BM_180), Intensidade UV (GUVA-S12SD) e o Relógio (RTC DS1307) 
  com suporte a salvar os dados no computador via arquivo CSV.

  Autor: d4nkali
  Data: 22/04/2024

*/

/*

  Localização dos pinos no Arduino:

    Alimentação e Comunicação Serial: USB para o Computador

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

    RTC DS1307 ou RTC 3231:

      VCC = 5V
      GND = GND
      SDA = A4 ou SDA
      SCL = A5 ou SCL

  OBS *1: Coloca um resistor ou potenciômetro na segunda perna do LDR.

  OBS *2: Para salvar os dados, precisa conectar a placa no computador e executar o arquivo python.

*/ 

// Inclusão das bibliotecas

 #include "dht.h"
 #include <Wire.h>
 #include <Adafruit_BMP085.h>
 #include "RTClib.h"

// Definindo os pinos e variáveis

  const int pinLDR = A0, pinUV = A1, pinDHT11 = A2; // Define o LDR no A0, UV no A1 e DHT11 no A2
  float umidade, temp, orvalho, sen_termica, pressao; // Define as variáveis de valores flutuantes
  int valor_uv, inten_uv, luz = 0;  // Define as variáveis de valores inteiros

// Chama a configuração da biblioteca

  dht DHT; 
  Adafruit_BMP085 bmp; 

  // Chama qual modulo vai ser usado

    RTC_DS1307 rtc; // Modulo rtc DS1307
    //RTC_DS3231 rtc; // Modulo rtc DS3132

void setup() { 

  Serial.begin(9600); // Inicia a comunicação serial

  if (!bmp.begin()) { // Se o BMP iniciar, então:

    // Caso não inicie:
    Serial.println("Não foi possível inicializar o BMP180"); // Imprimir no serial: "Não foi possível inicializar o BMP180"
    while (1); // Trava o programa

  }

  Wire.begin(); // Inicia a comunicação I2C no arduino  
  rtc.begin(); // Inicia o modulo do relógio

  pinMode(pinLDR, INPUT); //Coloca o LDR como entrada
  pinMode(pinUV, INPUT); // Coloca o sensor UV como entrada

  if (! rtc.isrunning()) { // Se o RTC iniciar, então:
  
    Serial.println("O modulo RTC não iniciou corretamente"); // Caso não inicie imprimir no serial: "O modulo RTC não iniciou corretamente"
    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajuste automático do RTC
    
    //rtc.adjust(DateTime(2023, 11, 13, 18, 00, 00)); // Ajuste manual do RTC para a data e hora definida pelo usuário sendo o formato AAAA/MM/DD HH/mm/SS.
    //OBS: Quando for a primeira vez ou quando acabar a bateria, configure o RTC para data e hora atual descomentando a linha; quando terminar comente na linha novamente
    
  }
  
  delay(2000); // Aguarda de 2 segundos para carregar as informações
  
}

void medir_temperatura() { // Cria uma função para a medição da temperatura, ponto de orvalho e sensação térmica do DHT_11

  umidade = DHT.humidity; // Armazena a umidade na variável "umidade"
  temp = DHT.temperature; // Armazena a temperatura na variável "temp"
  orvalho = temp - (100 - umidade) / 5; // Faz o calculo do Ponto de Orvalho e armazena na variável
  sen_termica = 13.12 + 0.6215 * temp - 11.37 * pow(umidade, 0.16) + 0.3965 * temp * pow(umidade, 0.16); // Calculo da sensação térmica e armazena na variável

}

void medir_pressao() { // Cria uma função para a medição da pressão atmosférica do BMP_180

  pressao = bmp.readPressure() / 100.0; // Cria a variável pressão e divida por 100 para converter para hPa
  pressao *= 10; // Converter hPa para mbar

}

void medir_uv() { // Cria uma função para a medição e converção do UV do GUVA-S12SD

  valor_uv = analogRead(pinUV); // Ler o sensor UV e armazena na variável
  inten_uv = map(valor_uv, 0, 1023, 0, 20); // Converter a leitura do sensor para o padrão de medição da OMS

}

void print_serial() { // Cria a função para imprimir as informações no monitor serial

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

  Serial.print("Umidade: ");  // Imprime o texto "Umidade"
  Serial.print(umidade); // Imprime no monitor o valor de umidade medido
  Serial.print("%"); // Imprime o "%"

  Serial.print(" / Temperatura: "); // Imprime o texto "Temperatura"
  Serial.print(temp, 0); // Imprime no monitor o valor de temperatura medido e remove a parte decimal
  Serial.print("*C"); // Imprime o "*C"

  Serial.print(" / Orvalho: "); // Imprime o texto "Orvalho"
  Serial.print(orvalho, 0); // Imprime o valor em "orvalho"
  Serial.print("*C"); // Imprime o "*C"

  Serial.print(" / Sensação Termica: "); // Imprime o texto "Sensação Termica"
  Serial.print(sen_termica, 0); // Imprime a sensação termica
  Serial.print("*C"); // Imprime o "*C"

  Serial.print(" / Pressão: "); // Imprime o texto "Pressão"
  Serial.print(pressao, 0); // Lê as informações da variável "pressao"
  Serial.print(" mbar");  // Imprime o "mbar"

  Serial.print(" / Nivel UV: "); // Imprime a frase "Nível UV: "
  Serial.print(inten_uv); // Imprime o valor convertido

  Serial.print(" / Luz: "); // Imprime o texto "Luz"
  Serial.print(luz); // Ler e imprime o valor do LDR
  Serial.println(" L"); // Imprime o "L"

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