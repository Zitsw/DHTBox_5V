/* 09.25.2020
   DHT_logger to measure temperature and humidity with a real time and save it to micro sd card..
   SD                                    DHT                                            Bulb
   CS-4(or any other)          DAT-D2(or any other)                 Long leg-D3(or any other) + resister depend on bulb(small one 100 ОМ) 
   SCK-13                                VCC-5V                                         Short leg-GND
   MOSI-11                               GND-GND
   MISO-12                               
   VCC-5V
   GND-GND
*/
#define delay_time 2000  //(Delay time in millisec)
#define LIGHT PD5  //(Bulb Pin)
#define DHTPIN PD2  //(DHT Pin)
#define DHTTYPE DHT22


#include <iarduino_RTC.h>
#include "DHT.h"
//#include <Wire.h>
//#include <SPI.h>
#include <SD.h>

//iarduino_RTC time(RTC_DS1302, 8, 6, 7);
iarduino_RTC time(RTC_DS3231);
DHT dht(DHTPIN, DHT22);

const int chipSelect = PD4;
File myFile;


void setup() {
    delay(300);
  
    if (!SD.begin(chipSelect)) {
     for(int sd_not = 0;sd_not<=26;sd_not++){
      digitalWrite(LIGHT,HIGH);
      delay(300);
      digitalWrite(LIGHT,LOW);
      delay(300);
     }
     
   }
    time.begin();
     myFile = SD.open("File.csv", FILE_WRITE);
    if (myFile) {
      myFile.print("Дата");
      myFile.print(";");
      myFile.print("Время");
      myFile.print(";");
      myFile.print("ID");
      myFile.print(";");
      myFile.print("Версия");
      myFile.print(";");
      myFile.print("Канал");
      myFile.print(";");
      myFile.print(";");
      myFile.print("Результат");
      myFile.print(";");
      myFile.println();
    }
    myFile.close();
    

}
void loop() {
  dht.begin();
     float h = dht.readHumidity(); //Измеряем влажность
     float t = dht.readTemperature(); //Измеряем температуру
//      Serial.print(h);
//      Serial.println();
      
      myFile = SD.open("File.csv", FILE_WRITE);
      if (myFile){
        digitalWrite(LIGHT,HIGH);
        myFile.print(time.gettime("d.m.Y;H:i:s;"));
        myFile.print("01");
        myFile.print(";");
        myFile.print("1.0");
        myFile.print(";");
        myFile.print("1");
        myFile.print(";");
        myFile.print("H");
        myFile.print(";");
        myFile.print(h);
        myFile.print(";");
        myFile.println();

      }
      myFile.close();
      

     
          myFile = SD.open("File.csv", FILE_WRITE);
          if (myFile){
        digitalWrite(LIGHT,HIGH);
        myFile.print(time.gettime("d.m.Y;H:i:s;"));
        myFile.print("01");
        myFile.print(";");
        myFile.print("1.0");
        myFile.print(";");
        myFile.print("2");
        myFile.print(";");
        myFile.print("T");
        myFile.print(";");
        myFile.print(t);
        myFile.print(";");
        myFile.println();

      }
          myFile.close();
     delay(delay_time);
  }
