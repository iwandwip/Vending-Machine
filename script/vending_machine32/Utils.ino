#include "Pins.h"

void Motor_Init() {
        //  for (int i = 0; i < 4; i++) {
        //    pinMode(driver::satu[i], OUTPUT);
        //    pinMode(driver::dua[i], OUTPUT);
        //  }
        pinMode(IN1, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);
        pinMode(IN12, OUTPUT);
        pinMode(IN32, OUTPUT);
        pinMode(ENA2, OUTPUT);
        pinMode(ENB2, OUTPUT);
}

void Motor_Buka(int num) {
        switch (num) {
                case 1:
                        analogWrite(ENA2, 255);
                        digitalWrite(IN12, HIGH);
                        break;
                case 2:
                        analogWrite(ENB2, 255);
                        digitalWrite(IN32, HIGH);
                        break;
                case 3:
                        analogWrite(ENA, 255);
                        digitalWrite(IN1, HIGH);
                        break;
                case 4:
                        analogWrite(ENB, 255);
                        digitalWrite(IN3, HIGH);
                        break;
        }
        //  servo1.write(85);
}

void Motor_Tutup(int num) {
        switch (num) {
                case 1:
                        digitalWrite(IN12, LOW);
                        //      digitalWrite(driver::satu[0], 255);
                        break;
                case 2:
                        digitalWrite(IN32, LOW);
                        //      digitalWrite(driver::satu[2], 255);
                        break;
                case 3:
                        digitalWrite(IN1, LOW);
                        //      digitalWrite(driver::dua[0], 255);
                        break;
                case 4:
                        digitalWrite(IN3, LOW);
                        //      digitalWrite(driver::dua[2], 255);
                        break;
        }
        //  servo1.write(90);
}

void serialSend() {
        if (Serial.available() > 1) {
                String read1, read2;
                String Read = Serial.readString();  //t#33#1.80#3.30
                read1 = parseString(Read, "#", 0);
                if (read1 == "id") {  // suhu
                        read2 = parseString(Read, "#", 1);
                        uidRFID = String(read2);
                        uidRFID.replace(" ", "");
                        Serial.println("uidRFID = " + String(uidRFID));
                }
                // Serial.println("Suhu = " + String(bme_val[0]));
        }
}


String parseString(String data, char separator[], int index) {
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;

        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator[0] || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i + 1 : i;
                }
        }

        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}