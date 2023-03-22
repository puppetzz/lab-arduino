#include <SPI.h>
#include <SD.h>
#include "Arduino.h"
#include "uRTCLib.h"
#include <DHT.h>

File myFile;

const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
float m =0;

const int chipSelect = 10;

// uRTCLib rtc;
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  
   pinMode(SS, OUTPUT);
   
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  dht.begin();

  URTCLIB_WIRE.begin();

  // Comment out below line once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set January 13 2022 at 12:56 you would call:
   rtc.set(0, 20, 16, 5, 16, 3, 23);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday)
}

void loop()
{

  rtc.refresh();
	// nothing happens after setup
  
  doiNhietDo();

  delay(1000);
}

void ghiThem() {
  float t = dht.readTemperature();

  if (SD.begin(chipSelect)) {
    if (rtc.second() % 10 == 0) {
      myFile = SD.open("test.txt", FILE_WRITE);
    
      // if the file opened okay, write to it:
      if (myFile) {
        Serial.print("Writing to test.txt...");
        myFile.print("Nhiet Do: ");
        myFile.print(t);
        myFile.print(" ");
        
        myFile.print(rtc.hour());
        myFile.print(':');
        myFile.print(rtc.minute());
        myFile.print(':');
        myFile.println(rtc.second());

        Serial.print("Nhiet Do: ");
        Serial.print(t);
        Serial.print(" ");
        
        Serial.print(rtc.hour());
        Serial.print(':');
        Serial.print(rtc.minute());
        Serial.print(':');
        Serial.println(rtc.second());

      // close the file:
        myFile.close();
        Serial.println("done.");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      m = t;
    }
  }
}

void doiNhietDo() {
  float t = dht.readTemperature();

  if (SD.begin(chipSelect)) {
    if (m != t) {
      myFile = SD.open("test.txt", FILE_WRITE);
    
      // if the file opened okay, write to it:
      if (myFile) {
        Serial.print("Writing to test.txt...");
        myFile.print("Nhiet Do: ");
        myFile.print(t);
        myFile.print(" ");
        
        myFile.print(rtc.hour());
        myFile.print(':');
        myFile.print(rtc.minute());
        myFile.print(':');
        myFile.println(rtc.second());

        Serial.print("Nhiet Do: ");
        Serial.print(t);
        Serial.print(" ");
        
        Serial.print(rtc.hour());
        Serial.print(':');
        Serial.print(rtc.minute());
        Serial.print(':');
        Serial.println(rtc.second());

      // close the file:
        myFile.close();
        Serial.println("done.");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
      m = t;
    }
  }
}