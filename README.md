# Estação Metrológica Arduino Uno/Nano

Mini Estação Meteorológica Usando **Arduino Nano/Uno**.

### Programa 1: Padrão

Mini estação metrológica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), Umidade com temperatura (DHT11), Pressão Atmosférica (BMP_180) e Intensidade UV (GUVA-S12SD).

### Programa 2: Relógio
Mini estação metrológica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), Umidade com temperatura (DHT11) e Pressão Atmosférica (BMP_180), Intensidade UV (GUVA-S12SD) e Relógio (RTC_1407).

### Programa 3: CSV
Programa para a mini estação meteorológica usando o Arduino Uno ou Nano, os sensores de medição de luz (LDR), Umidade com temperatura (DHT11), Pressão Atmosférica (BM_180), Intensidade UV (GUVA-S12SD) e o Relógio (RTC DS1307) com suporte a salvar os dados no computador via arquivo CSV.

Ambos possuem a comunicação via monitor serial 9600 band e os programas 1 e 2 possuem suporte extra com o Modulo Bluetooth (HC-06 ou HC-05).

## Bibliotecas Usadas no Arduino:

- [Adafruit BMP_085](https://github.com/adafruit/Adafruit-BMP085-Library)
- [dht](https://github.com/RobTillaart/DHTlib)
- [RTClib](https://github.com/adafruit/RTClib)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

## Bibliotecas Usadas no Python:

- [serial](https://pypi.org/project/serial/)
- [csv](https://docs.python.org/3/library/csv.html)
