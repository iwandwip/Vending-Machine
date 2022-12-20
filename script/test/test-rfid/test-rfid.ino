#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 21  
#define RST_PIN 22 
#define BAUDRATE 115200
String uidRFID = "";
MFRC522 rfid(SS_PIN, RST_PIN);

void rfid_Init() {
  Serial.println("RFID Init");
  SPI.begin(); 
  rfid.PCD_Init(); 

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void bacaRfid() {
  if (rfid.PICC_IsNewCardPresent()) { 
    if (rfid.PICC_ReadCardSerial()) { 
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      uidRFID = "";

      
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
        uidRFID.concat(String(rfid.uid.uidByte[i]));
      }
      Serial.println();
      Serial.println("uidRFID = " + uidRFID);

      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1(); 
    }
  }
}

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("INITIALIZE");
  rfid_Init();
}

void loop() {
  bacaRfid();
}
