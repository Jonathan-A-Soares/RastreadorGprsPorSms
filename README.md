# Rastreador Veicular Feito com Modulo Gprs, Gsm e SmS 
## Modulos Utilizados
- **Arduino Nano atmega328**
- **Neo-7m Gygpsv1-7m**
- **Sim800 Gprs Gsm Sim800l**
> ### Foi necesario modificar a blibioteca Sim800-master.

* Projeto Conclui em Mandar Sms para numero Do modulo sim800l, E modulo Retorna Sms Com localidade do veiculo Em Latitude Longitude e Link para mapa.
## Comandos
| Comando | Ação                      |
|---------|---------------------------|
| Location| Localização               |
| On      |  liga porta digita 2      |
| Off     |  desliga porta digita 2   |
| Reset   |   Reinicia Tudo           |

![](https://github.com/Jonathan-A-Soares/RastreadorGprsPorSms/blob/main/exemplo/smss.png?raw=true"heinght="150"width="150")
## Pinagem

### Sim800L
| Sim800L | Arduino                   |
|---------|---------------------------|
| Vcc     |  Alimentação Externa 3.7v |
| Tx      |            D10            |
| Rx      |            D9             |
| Reset   |            D7             |
| Gnd     |            Gnd            |

__Atenção o modulo Gprs (Sim800l) tem que ser Alimentado com ou mais de 3.7v é Menos de 4.2v Corrente de pico pode Chegar a 2A__
### Gps Neo-7M
| Gps Neo-6M | Arduino        |
|------------|----------------|
| Vcc        |  Vcc           |
| Tx         |            D5  |
| Rx         |            D4  |
| Gnd        |           Gnd  |

#### Blibioteca Modificada 
- [Sim800-master](https://github.com/Jonathan-A-Soares/RastreadorGprsPorSms/blob/main/Sim800l-master.zip)
- __Atenção so funciona com a blibioteca modificada__
#### Blibioteca Originais
- [Sim800-master](https://github.com/cristiansteib/Sim800l)
- [Wire](https://www.arduino.cc/en/reference/wire)
- [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial)
- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus/releases/tag/v1.0.2b)
