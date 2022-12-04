#include "Pins.h"

void FingerPrint_Init() {
        Serial.begin(115200);
        while (!Serial)
                ;  // For Yun/Leo/Micro/Zero/...
        delay(100);
        Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

        // set the data rate for the sensor serial port
        finger.begin(57600);

        if (finger.verifyPassword()) {
                Serial.println("Found fingerprint sensor!");
        } else {
                Serial.println("Did not find fingerprint sensor :(");
                while (1) {
                        delay(1);
                }
        }

        Serial.println(F("Reading sensor parameters"));
        finger.getParameters();
        Serial.print(F("Status: 0x"));
        Serial.println(finger.status_reg, HEX);
        Serial.print(F("Sys ID: 0x"));
        Serial.println(finger.system_id, HEX);
        Serial.print(F("Capacity: "));
        Serial.println(finger.capacity);
        Serial.print(F("Security level: "));
        Serial.println(finger.security_level);
        Serial.print(F("Device address: "));
        Serial.println(finger.device_addr, HEX);
        Serial.print(F("Packet len: "));
        Serial.println(finger.packet_len);
        Serial.print(F("Baud rate: "));
        Serial.println(finger.baud_rate);
}

uint8_t readnumber(void) {
        uint8_t num = 0;

        while (num == 0) {
                while (!Serial.available())
                        ;
                num = Serial.parseInt();
        }
        return num;
}

//void loop()                     // run over and over again
//{
//  Serial.println("Ready to enroll a fingerprint!");
//  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
//  id = readnumber();
//  if (id == 0) {// ID #0 not allowed, try again!
//     return;
//  }
//  Serial.print("Enrolling ID #");
//  Serial.println(id);
//
//  while (!  getFingerprintEnroll() );
//}

uint8_t getFingerprintEnroll() {

        int p = -1;
        Serial.print("Waiting for valid finger to enroll as #");
        Serial.println(id);
        while (p != FINGERPRINT_OK) {
                p = finger.getImage();
                switch (p) {
                        case FINGERPRINT_OK:
                                Serial.println("Image taken");
                                break;
                        case FINGERPRINT_NOFINGER:

                                lcd.setCursor(0, 0);
                                lcd.print("     REGISTER       ");
                                lcd.setCursor(0, 1);
                                lcd.print("                    ");
                                lcd.setCursor(0, 2);
                                lcd.print(" LETAKAN JARI ANDA  ");
                                lcd.setCursor(0, 3);
                                lcd.print("                    ");

                                //        Serial.println(".");
                                break;
                        case FINGERPRINT_PACKETRECIEVEERR:
                                Serial.println("Communication error");
                                break;
                        case FINGERPRINT_IMAGEFAIL:
                                Serial.println("Imaging error");
                                break;
                        default:
                                Serial.println("Unknown error");
                                break;
                }
        }

        // OK success!

        p = finger.image2Tz(1);
        switch (p) {
                case FINGERPRINT_OK:
                        Serial.println("Image converted");
                        break;
                case FINGERPRINT_IMAGEMESS:
                        Serial.println("Image too messy");
                        return p;
                case FINGERPRINT_PACKETRECIEVEERR:
                        Serial.println("Communication error");
                        return p;
                case FINGERPRINT_FEATUREFAIL:
                        Serial.println("Could not find fingerprint features");
                        return p;
                case FINGERPRINT_INVALIDIMAGE:
                        Serial.println("Could not find fingerprint features");
                        return p;
                default:
                        Serial.println("Unknown error");
                        return p;
        }

        lcd.setCursor(0, 0);
        lcd.print("     REGISTER       ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LEPASKAN JARI ANDA ");
        lcd.setCursor(0, 3);
        lcd.print("       #####        ");

        Serial.println("Remove finger");
        delay(2000);
        p = 0;
        while (p != FINGERPRINT_NOFINGER) {
                p = finger.getImage();
        }
        Serial.print("ID ");
        Serial.println(id);
        p = -1;

        lcd.setCursor(0, 0);
        lcd.print("     REGISTER       ");
        lcd.setCursor(0, 1);
        lcd.print("                    ");
        lcd.setCursor(0, 2);
        lcd.print(" LETAKAN JARI ANDA  ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");

        Serial.println("Place same finger again");
        while (p != FINGERPRINT_OK) {
                p = finger.getImage();
                switch (p) {
                        case FINGERPRINT_OK:
                                Serial.println("Image taken");
                                break;
                        case FINGERPRINT_NOFINGER:
                                //        Serial.print(".");
                                break;
                        case FINGERPRINT_PACKETRECIEVEERR:
                                Serial.println("Communication error");
                                break;
                        case FINGERPRINT_IMAGEFAIL:
                                Serial.println("Imaging error");
                                break;
                        default:
                                Serial.println("Unknown error");
                                break;
                }
        }

        // OK success!

        p = finger.image2Tz(2);
        switch (p) {
                case FINGERPRINT_OK:
                        Serial.println("Image converted");
                        break;
                case FINGERPRINT_IMAGEMESS:
                        Serial.println("Image too messy");
                        return p;
                case FINGERPRINT_PACKETRECIEVEERR:
                        Serial.println("Communication error");
                        return p;
                case FINGERPRINT_FEATUREFAIL:
                        Serial.println("Could not find fingerprint features");
                        return p;
                case FINGERPRINT_INVALIDIMAGE:
                        Serial.println("Could not find fingerprint features");
                        return p;
                default:
                        Serial.println("Unknown error");
                        return p;
        }

        // OK converted!
        Serial.print("Creating model for #");
        Serial.println(id);

        p = finger.createModel();
        if (p == FINGERPRINT_OK) {
                Serial.println("Prints matched!");
        } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
                Serial.println("Communication error");
                return p;
        } else if (p == FINGERPRINT_ENROLLMISMATCH) {
                Serial.println("Fingerprints did not match");
                return p;
        } else {
                Serial.println("Unknown error");
                return p;
        }

        Serial.print("ID ");
        Serial.println(id);
        p = finger.storeModel(id);
        if (p == FINGERPRINT_OK) {

                lcd.setCursor(0, 0);
                lcd.print("     REGISTER       ");
                lcd.setCursor(0, 1);
                lcd.print("                    ");
                lcd.setCursor(0, 2);
                lcd.print(" LEPASKAN JARI ANDA ");
                lcd.setCursor(0, 3);
                lcd.print("     BERHASIL       ");

                Serial.println("Stored!");
        } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

                lcd.setCursor(0, 0);
                lcd.print("     REGISTER       ");
                lcd.setCursor(0, 1);
                lcd.print("                    ");
                lcd.setCursor(0, 2);
                lcd.print(" LEPASKAN JARI ANDA ");
                lcd.setCursor(0, 3);
                lcd.print("   ERROR / GAGAL    ");

                Serial.println("Communication error");
                return p;
        } else if (p == FINGERPRINT_BADLOCATION) {
                Serial.println("Could not store in that location");
                return p;
        } else if (p == FINGERPRINT_FLASHERR) {
                Serial.println("Error writing to flash");
                return p;
        } else {
                lcd.setCursor(0, 0);
                lcd.print("     REGISTER       ");
                lcd.setCursor(0, 1);
                lcd.print("                    ");
                lcd.setCursor(0, 2);
                lcd.print(" LEPASKAN JARI ANDA ");
                lcd.setCursor(0, 3);
                lcd.print("   ERROR / GAGAL    ");

                Serial.println("Unknown error");
                return p;
        }

        return true;
}

uint8_t deleteFingerprint(uint8_t id) {
        uint8_t p = -1;

        p = finger.deleteModel(id);

        if (p == FINGERPRINT_OK) {
                Serial.println("Deleted!");
        } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
                Serial.println("Communication error");
        } else if (p == FINGERPRINT_BADLOCATION) {
                Serial.println("Could not delete in that location");
        } else if (p == FINGERPRINT_FLASHERR) {
                Serial.println("Error writing to flash");
        } else {
                Serial.print("Unknown error: 0x");
                Serial.println(p, HEX);
        }

        return p;
}

void ValidationFingerInit() {
        finger.getTemplateCount();

        if (finger.templateCount == 0) {
                Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
        } else {
                Serial.println("Waiting for valid finger...");
                Serial.print("Sensor contains ");
                Serial.print(finger.templateCount);
                Serial.println(" templates");
        }
}

uint8_t getFingerprintID() {
        uint8_t p = finger.getImage();
        switch (p) {
                case FINGERPRINT_OK:
                        Serial.println("Image taken");

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print(" SIDIK JARI DIAMBIL ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        break;
                case FINGERPRINT_NOFINGER:

                        // lcd.setCursor(0, 0);
                        // lcd.print("     PURCHASE       ");
                        // lcd.setCursor(0, 1);
                        // lcd.print("                    ");
                        // lcd.setCursor(0, 2);
                        // lcd.print("      TIDAK ADA     ");
                        // lcd.setCursor(0, 3);
                        // lcd.print("      SIDIK JARI    ");

                        //      Serial.println("No finger detected");
                        return p;
                case FINGERPRINT_PACKETRECIEVEERR:
                        //      Serial.println("Communication error");
                        return p;
                case FINGERPRINT_IMAGEFAIL:

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print("  SIDIK JARI ERROR  ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        //      Serial.println("Imaging error");
                        return p;
                default:
                        //      Serial.println("Unknown error");
                        return p;
        }

        // OK success!

        p = finger.image2Tz();
        switch (p) {
                case FINGERPRINT_OK:

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print("    SIDIK JARI OK   ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        Serial.println("Image converted");
                        break;
                case FINGERPRINT_IMAGEMESS:

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print("  SIDIK JARI KOTOR  ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        Serial.println("Image too messy");
                        return p;
                case FINGERPRINT_PACKETRECIEVEERR:
                        Serial.println("Communication error");
                        return p;
                case FINGERPRINT_FEATUREFAIL:

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print("  SIDIK JARI GAGAL  ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        Serial.println("Could not find fingerprint features");
                        return p;
                case FINGERPRINT_INVALIDIMAGE:

                        lcd.setCursor(0, 0);
                        lcd.print("     PURCHASE       ");
                        lcd.setCursor(0, 1);
                        lcd.print("                    ");
                        lcd.setCursor(0, 2);
                        lcd.print("  SIDIK JARI GAGAL  ");
                        lcd.setCursor(0, 3);
                        lcd.print("                    ");

                        Serial.println("Could not find fingerprint features");
                        return p;
                default:
                        Serial.println("Unknown error");
                        return p;
        }

        // OK converted!
        p = finger.fingerSearch();
        if (p == FINGERPRINT_OK) {

                lcd.setCursor(0, 0);
                lcd.print("     PURCHASE       ");
                lcd.setCursor(0, 1);
                lcd.print("                    ");
                lcd.setCursor(0, 2);
                lcd.print(" SIDIK JARI DIAMBIL ");
                lcd.setCursor(0, 3);
                lcd.print("                    ");

                Serial.println("Found a print match!");
        } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
                Serial.println("Communication error");
                return p;
        } else if (p == FINGERPRINT_NOTFOUND) {
                Serial.println("Did not find a match");
                return p;
        } else {
                Serial.println("Unknown error");
                return p;
        }

        // found a match!
        Serial.print("Found ID #");
        Serial.print(finger.fingerID);
        Serial.print(" with confidence of ");
        Serial.println(finger.confidence);

        lcd.setCursor(0, 0);
        lcd.print("     PURCHASE       ");
        lcd.setCursor(0, 1);
        lcd.print("    ID DITEMUKAN    ");
        lcd.setCursor(0, 2);
        lcd.print(" LEPASKAN JARI ANDA ");
        lcd.setCursor(0, 3);
        lcd.print("     BERHASIL       ");

        // delay(2000);
        return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
        uint8_t p = finger.getImage();
        if (p != FINGERPRINT_OK) return -1;

        p = finger.image2Tz();
        if (p != FINGERPRINT_OK) return -1;

        p = finger.fingerFastSearch();
        if (p != FINGERPRINT_OK) return -1;

        // found a match!
        Serial.print("Found ID #");
        Serial.print(finger.fingerID);
        Serial.print(" with confidence of ");
        Serial.println(finger.confidence);

        lcd.setCursor(0, 0);
        lcd.print("     PURCHASE       ");
        lcd.setCursor(0, 1);
        lcd.print("    ID DITEMUKAN    ");
        lcd.setCursor(0, 2);
        lcd.print(" LEPASKAN JARI ANDA ");
        lcd.setCursor(0, 3);
        lcd.print("     BERHASIL       ");

        return finger.fingerID;
}

//  Serial.println("Ready to enroll a fingerprint!");
//  Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
//  id = readnumber();
//  if (id == 0) {// ID #0 not allowed, try again!
//    return;
//  }
//  Serial.print("Enrolling ID #");
//  Serial.println(id);
//
//  while (!  getFingerprintEnroll() );
//  getFingerprintID();
//  deleteFingerprint(id);