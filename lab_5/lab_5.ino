//RST 9
// MISO 12
// MOSI 11
//SCK 13
// SDA 10

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 8

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Tạo đối tượng MFRC522

// Chuỗi Serial ID của thẻ RFID được phép truy cập
char cardID[] = "13 c3 91 ae";

// Số lần quét sai thẻ
int count = 0;

long start = millis();

void setup() {
  Serial.begin(9600);   // Khởi tạo giao tiếp Serial
  SPI.begin();          // Khởi tạo giao tiếp SPI
  mfrc522.PCD_Init();    // Khởi tạo module RC522
  pinMode(LED_PIN, OUTPUT);  // Khởi tạo chân điều khiển LED là đầu ra
}

void loop() {
  while (true) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      // So sánh Serial ID của thẻ RFID với chuỗi được cho phép
      String readID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        readID += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
        readID += String(mfrc522.uid.uidByte[i], HEX) + " ";
      }

      readID.trim();
      Serial.println("Card ID: " + readID);

      if (strcmp(readID.c_str(), cardID) == 0) {
        // Nếu Serial ID đúng, bật đèn LED  
        digitalWrite(LED_PIN, HIGH); 
        delay(200);
        start = millis();
        while(millis() - start < 2000) {
          if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
            String readNewID = "";
            for (byte i = 0; i < mfrc522.uid.size; i++) {
              readNewID += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
              readNewID += String(mfrc522.uid.uidByte[i], HEX) + " ";
            }
            Serial.println(readNewID);
            Serial.println(strcmp(readNewID.c_str(), cardID));
            
            if (strcmp(readNewID.c_str(), cardID) != 32){
              break;
            }

            if (strcmp(readNewID.c_str(), cardID) == 32) {
              digitalWrite(LED_PIN, LOW);
              delay(500);
              break;
            }
            start = millis();
          }
        }
      } else if (strcmp(readID.c_str(), cardID) != 0){
        digitalWrite(LED_PIN, HIGH);
        while(true) {
          digitalWrite(LED_PIN, HIGH);
          delay(100);
          digitalWrite(LED_PIN, LOW);
          delay(100);
          if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
            String readNewID = "";
            for (byte i = 0; i < mfrc522.uid.size; i++) {
              readNewID += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
              readNewID += String(mfrc522.uid.uidByte[i], HEX) + " ";
            }
            Serial.println(readNewID);
            Serial.println(strcmp(readNewID.c_str(), cardID));
            
            if (strcmp(readNewID.c_str(), cardID) == 32){
              break;
            }
          }
        }
      }
      
    }
  }
}