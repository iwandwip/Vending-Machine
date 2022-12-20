#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Seria2
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
        Serial.begin(9600);
        while (!Serial)
                ;  
        delay(100);
        finger.begin(57600);
        delay(5);
        if (finger.verifyPassword()) {
                Serial.println("Found fingerprint sensor!");
        } else {
                Serial.println("Did not find fingerprint sensor :(");
                while (1) { delay(1); }
        }

        finger.getTemplateCount();
}

void loop()  
{
        getFingerprintIDez();
        delay(50);  
}

int getFingerprintIDez() {
        uint8_t p = finger.getImage();
        if (p != FINGERPRINT_OK) return -1;

        p = finger.image2Tz();
        if (p != FINGERPRINT_OK) return -1;

        p = finger.fingerFastSearch();
        if (p != FINGERPRINT_OK) return -1;

        Serial.print("Found ID #");
        Serial.print(finger.fingerID);
        Serial.print(" with confidence of ");
        Serial.println(finger.confidence);
        return finger.fingerID;
}
