#include <Wire.h>
#include<SoftwareSerial.h>
#include <TinyGPS++.h> // Include the TinyGPS++ library
#include <Sim800l.h>
#define ARDUINO_GPS_RX 5 // GPS TX, Arduino RX pin
#define ARDUINO_GPS_TX 4 // GPS RX, Arduino TX pin
#define gpsPort ssGPS  // Alternatively, use Serial1 on the Leonardo
#define SerialMonitor Serial
#define GPS_BAUD 9600

SoftwareSerial ssGPS(ARDUINO_GPS_TX, ARDUINO_GPS_RX); // Create a SoftwareSerial
TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object
Sim800l Sim800l;



/*
sim800l 
tx >>> 10
rx >>> 9
reset >>> 7
vcc >>> 4.7v

gps
rx >>> 5
tx >>> 4
vcc >>> 5v




*/






float lat, lon, vel;
unsigned long data, hora;
unsigned short sat;
String textSms, numberSms;
char* number , text  ;
bool error;

void setup()
{
 
  //GPS
  analogReference(DEFAULT);
  gpsPort.begin(GPS_BAUD);
  SerialMonitor.begin(9600);
  smartDelay(1000);
   //sms
  text = "oi";
  Serial.begin(9600);
  Sim800l.begin();
  Serial.print("Limpando SMS antigos...");
  error = Sim800l.delAllSms(); //Apaga SMS
  Serial.println(" Apagados!");
  Serial.println("\nAguardando comandos por SMS...");
  number = "35000000000";


}


void loop()
{

  
  ResSms();
  printInfo();

}
void ResSms() {

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

      if (textSms.indexOf("KDTU") != -1)
      {
        Serial.println("Opçao 1");



        float lattt = tinyGPS.location.lat();
        float lottt = tinyGPS.location.lng();
        error = Sim800l.sendSms(number, lattt ); //latitude
        error = Sim800l.sendSms(number, lottt ); //longitude


        

      }




      Sim800l.delAllSms();
    }
  }
}
void printInfo()
{
  //====================================== Localização ======================================
  SerialMonitor.print("Lat: "); SerialMonitor.println(tinyGPS.location.lat(), 6);
  SerialMonitor.print("Long: "); SerialMonitor.println(tinyGPS.location.lng(), 6);
  SerialMonitor.print("Alt: "); SerialMonitor.println(tinyGPS.altitude.meters());
  SerialMonitor.print("Speed: "); SerialMonitor.println(tinyGPS.speed.kmph());
  SerialMonitor.print("Sats: "); SerialMonitor.println(tinyGPS.satellites.value());

  //====================================== Data ======================================
  SerialMonitor.print(tinyGPS.date.day());
  SerialMonitor.print("/");
  SerialMonitor.print(tinyGPS.date.month());
  SerialMonitor.print("/");
  SerialMonitor.println(tinyGPS.date.year());

  //====================================== Hora ======================================
  SerialMonitor.print(tinyGPS.time.hour());
  SerialMonitor.print(":");
  if (tinyGPS.time.minute() < 10) SerialMonitor.print('0');
  SerialMonitor.print(tinyGPS.time.minute());
  SerialMonitor.print(":");
  if (tinyGPS.time.second() < 10) SerialMonitor.print('0');
  SerialMonitor.println(tinyGPS.time.second());

  //==================================================================================
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {

    while (gpsPort.available())
      tinyGPS.encode(gpsPort.read());
  }   while (millis() - start < ms);
}
