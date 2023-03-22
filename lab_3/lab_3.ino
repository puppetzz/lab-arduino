#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <PinButton.h>

// Create a new button object, listening on pin 5.
PinButton myButton(12);

LiquidCrystal_I2C lcd(0x27,16,2);

const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

int lcdState = HIGH;

int isOn = true;

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  lcd.init();  
  lcd.backlight();
  
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  
  lcd.createChar(1, degree);
  // pinMode(buttonPin, 4);

  dht.begin();  

  Serial.begin(9600);
}

void loop() {
  float t = dht.readTemperature();

  myButton.update();

  if (myButton.isClick()) {
    lcdState = !lcdState;
  }

  if (myButton.isDoubleClick()) {
    lcd.setCursor(0,0);
    for (int i = 0; i <= 20; i++) {
      lcd.print(" ");
    }
    lcd.noBacklight();
    isOn = false;
  }

  if (lcdState == HIGH && isOn == true) {
    if (isnan(t)) {
    } 
    else {
      lcd.setCursor(10,0);
      lcd.print(round(t));
      lcd.print(" ");
      lcd.write(1);
      lcd.print("C");
      lcd.print(" ");

      lcd.setCursor(10,1);
    }
  } 
  if (lcdState == LOW && isOn == true) {
    if (isnan(t)) {
    } 
    else {
      lcd.setCursor(10,0);
      lcd.print(round(t*1.8) + 32);
      lcd.print(" ");
      lcd.write(1);
      lcd.print("F");

      lcd.setCursor(10,1);
    }
  }
}