/* 25.09.2020
   Датчик по считыванию температуры и влажности на модуле DHT с micro-sd.
   SD                                    DHT                                            Лампочка
   CS-4(или настроить свой пин)          DAT-D2(или настроить свой пин)                 Длинная нога-D3(Или свой пин) + резистор взависимости от лампочки(обычнная маленькая лампочка 100 ОМ) 
   SCK-13                                VCC-5V                                         Короткая нога-GND
   MOSI-11                               GND-GND
   MISO-12                               
   VCC-5V
   GND-GND
*/
#define delay_time 2000  //(время между записью в миллисекундах)
#define LIGHT 3   //(Пин светодиода)
#define DHTPIN 2  //(Пин DHT)


#include <iarduino_RTC.h>
#include "DHT.h"
#include <SPI.h>
#include <SD.h>


iarduino_RTC time(RTC_DS1307);
DHT dht(DHTPIN, DHT22);

const int chipSelect = 4;
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
      myFile.print("Режим");
      myFile.print(";");
      myFile.print("Результат");
      myFile.print(";");
      myFile.println();
    }
    myFile.close();
    dht.begin();


}
void loop() {

     float h = dht.readHumidity(); //Измеряем влажность
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


     float t = dht.readTemperature(); //Измеряем температуру
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
