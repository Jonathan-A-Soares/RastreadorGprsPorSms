/*
  Author : https : //github.com/Jonathan-A-Soares
  20:57
  02/03/2021
*/
#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Sim800l.h>
#define ARDUINO_GPS_RX 5 // GPS TX, Arduino RX pin
#define ARDUINO_GPS_TX 4 // GPS RX, Arduino TX pin
#define gpsPort ssGPS
#define SerialMonitor Serial
#define GPS_BAUD 9600

SoftwareSerial ssGPS(ARDUINO_GPS_TX, ARDUINO_GPS_RX);
TinyGPSPlus tinyGPS;
Sim800l Sim800l;

float lat, lon, vel;
unsigned long data, hora;
unsigned short sat;
String textSms, numberSms;
char *number, text;
bool error, msgg, link, loca;
int estate;
int dell = 0;
int hor, minn, seg;

void setup()
{

  //GPS
  analogReference(DEFAULT);
  gpsPort.begin(GPS_BAUD);
  SerialMonitor.begin(9600);
  smartDelay(1000);

  //sms
  text = "oi";

  Sim800l.begin();
  // Serial.print("Limpando SMS antigos...");
  // error = Sim800l.delAllSms();
  //Serial.println(" Apagados!");
  Serial.println("\nAguardando comandos por SMS...");
  number = "35000000000";
  pinMode(2, OUTPUT);
}

void loop()
{
  printInfo();
  smartDelay(1000);
  ResSms();
  printInfo();
  smartDelay(5000);
  ResSms();
  printInfo();
  smartDelay(5000);
  ResSms();
  printInfo();
  smartDelay(5000);
  ResSms();
  printInfo();
  smartDelay(1000);
  asm volatile("jmp 0x0000");
}
void ResSms()
{

  textSms = Sim800l.readSms(1);

  if (textSms.indexOf("OK") != -1)
  {

    if (textSms.length() > 7)
    {
      numberSms = Sim800l.getNumberSms(1);
      numberSms.remove(0, 1);
      Serial.println(numberSms);
      textSms.toUpperCase();

      numberSms.toCharArray(number, 20);

      if (textSms.indexOf("LOCATION") != -1)
      {
        Serial.println("Opçao 1");

        float lattt = tinyGPS.location.lat();
        float lottt = tinyGPS.location.lng();
        link = Sim800l.sendLinkSms(number, lattt, lottt);
        //         error = Sim800l.sendSms(number, lattt ); //latitude
        //         error = Sim800l.sendSms(number, lottt ); //longitude
        loca = Sim800l.sendLocationSms(number, lattt, lottt, hor, minn, seg);
      }
      else if (textSms.indexOf("ON") != -1)
      {
        digitalWrite(2, HIGH);
        Serial.println("Opçao 2");
        msgg = Sim800l.sendtextSms(number, "Ligado");
        estate = 10;
      }
      else if (textSms.indexOf("OFF") != -1)
      {
        digitalWrite(2, LOW);
        Serial.println("Opçao 3");
        msgg = Sim800l.sendtextSms(number, "Desligado");
        estate = 0;
      }
      Sim800l.delAllSms();
    }
  }
}
void printInfo()
{
  //====================================== Localização ======================================
  SerialMonitor.print("Lat: ");
  SerialMonitor.println(tinyGPS.location.lat(), 6);
  SerialMonitor.print("Long: ");
  SerialMonitor.println(tinyGPS.location.lng(), 6);
  SerialMonitor.print("Alt: ");
  SerialMonitor.println(tinyGPS.altitude.meters());
  SerialMonitor.print("Speed: ");
  SerialMonitor.println(tinyGPS.speed.kmph());
  SerialMonitor.print("Sats: ");
  SerialMonitor.println(tinyGPS.satellites.value());

  //====================================== Data ======================================
  SerialMonitor.print(tinyGPS.date.day());
  SerialMonitor.print("/");
  SerialMonitor.print(tinyGPS.date.month());
  SerialMonitor.print("/");
  SerialMonitor.println(tinyGPS.date.year());

  //====================================== Hora ======================================
  SerialMonitor.print(tinyGPS.time.hour());
  SerialMonitor.print(":");
  if (tinyGPS.time.minute() < 10)
    SerialMonitor.print('0');
  SerialMonitor.print(tinyGPS.time.minute());
  SerialMonitor.print(":");
  if (tinyGPS.time.second() < 10)
    SerialMonitor.print('0');
  SerialMonitor.println(tinyGPS.time.second());

  hor = tinyGPS.time.hour();
  minn = tinyGPS.time.minute();
  seg = tinyGPS.time.second();

  //==================================================================================
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {

    while (gpsPort.available())
      tinyGPS.encode(gpsPort.read());
  } while (millis() - start < ms);
}
