#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>
#include "Pins.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial2
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// #define SSID_WIFI "KASTARA GROUP INDONESIA"
// #define PASS_WIFI "KASTARA@2022"
#define SSID_WIFI "Polinema Hotspot AJ LT 3 Tengah"
#define PASS_WIFI ""
// #define SSID_WIFI "pertalite 10k"
// #define PASS_WIFI "00000000"
#define DOMAIN "http://192.168.92.76/vending_machine"

#define ID_BOARD 1

uint8_t id;

/* Surya, Camel, Marlboro*/
uint8_t beli_roko[3] = { 0, 0, 0 };
uint8_t pinMHSensor[2] = { MHSENS1, MHSENS2 };
char customKey;

int mh_analog_val = 0;
bool mh_digital_val = false;

uint8_t statusWifi = 0;

char _mode = 'E';

String uidRFID = "1234";
int fingerID = 0;

int validate = 0;
int regist = 0;
int umur_valid = 0;

uint32_t u_time[5];

void setup() {
        Serial.begin(115200);
        Serial.println("INITIALIZE");
        WIFI_INIT();
        KeyPad_Init();
        rfid_Init();
        Motor_Init();
        //  Servo_Init();
        //  mhSensor_Init();
        lcd_Init();
        FingerPrint_Init();
        ValidationFingerInit();
}

void loop() {
        // koneksiWifiChecker();
        //  Serial.println("statusWifi = " + String(statusWifi));

        if (millis() - u_time[0] > 10) {

                bacaKeypad();

                u_time[0] = millis();
        }

        if (millis() - u_time[1] > 10) {

                bacaRfid();

                u_time[1] = millis();
        }
        //  mhSensor_Test();
        serialSend();
        // checkRFID(uidRFID);

        if (millis() - u_time[2] > 100) {

                fingerID = getFingerprintIDez();

                u_time[2] = millis();
        }

        if (millis() - u_time[3] > 30) {

                lcd_main();

                u_time[3] = millis();
        }
        // Serial.println("validate = " + String(validate));

        // delay(50);
}