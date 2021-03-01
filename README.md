# Rastreador Veicular Feito com Modulo Gprs, Gsm e SmS 
## Modulos Utilizados
- **Arduino Nano atmega328**
- **Neo-7m Gygpsv1-7m**
- **Sim800 Gprs Gsm Sim800l**
> ### Foi necesario modificar a blibioteca sim800-master.

* Projeto Conclui em Mandar Sms para numero Do modulo sim800l, E modulo Retorna Sms Com localidade do veiculo Em Latitude Longitude.
* ### Pinagem

### Sim800L
| Sim800L | Arduino                   |
|---------|---------------------------|
| Vcc     |  Alimentação Externa 4.7v |
| Tx      |            D10            |
| Rx      |            D9             |
| Reset   |            D7             |
| Gnd     |            Gnd            |
### Gps Neo-6M
| Gps Neo-6M | Arduino        |
|------------|----------------|
| Vcc        |  Vcc           |
| Tx         |            D5  |
| Rx         |            D4  |
| Gnd        |           Gnd  |
