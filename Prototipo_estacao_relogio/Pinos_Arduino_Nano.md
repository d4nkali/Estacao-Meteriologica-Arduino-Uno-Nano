# Localização dos pinos no Arduino NANO
 
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

  RTC DS1307 ou RTC 3231:
  VCC = 5V
  GND = GND
  SDA = A4
  SCL = A5

  HC-06 VCC: 5V
  HC-06 GND: GND
  HC-06 TXD: RX
  HC-06 RXD: Depois do Resistor de 10k e do de 20K
  Primeira Perna Resistor de 10k: TX
  Segunda Perna Resistor de 20K: GND

  OBS *1: Coloca um resistor ou potenciometro na segunda perna do LDR.

  OBS *2: Para usar o pino RX corretamente deve fazer um divisor de tensão para não queimar o modulo.Então para isso deve colocar o fio do arduino em um resistor 10k e na outra ponta ligar outro resistor de 20 ou 22k, no meio deles vai o fio do sensor e na outra ponta do de 22k vai um fio ao GND da placa.