# Estação Meteriologica Arduino Uno/Nano

Mini Estação Meteorológica Usando **Arduino Nano/Uno**.

### Programa 1: Padrão

Mini estação meteriologica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), Umidade com temperatura (DHT11), Pressão Atmosferica (BMP_180) e Intensidade UV (GUVA-S12SD).

### Programa 2: Relogio
Mini estação meteriologica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), Umidade com temperatura (DHT11) e Pressão Atmosferica (BMP_180), Intensidade UV (GUVA-S12SD) e Relogio (RTC_1407).

Ambos possuem a comunicação via monitor serial 9600 baund e suporte extra com o Modulo Bluetooth (HC-06 ou HC-05).

## Bibliotecas Usadas:

- [Adafruit BMP_085](https://github.com/adafruit/Adafruit-BMP085-Library)
- [dht](https://github.com/RobTillaart/DHTlib)
- [RTClib](https://github.com/adafruit/RTClib)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)
