#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial2
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define SSID_WIFI "KASTARA GROUP INDONESIA"
#define PASS_WIFI "KASTARA@2022"
#define DOMAIN "http://192.168.200.147:8080/vending_machine"

#define ID_BOARD 1

uint8_t id;

/* Surya, Camel, Marlboro*/
uint8_t beli_roko[3] = {0, 0, 0};
uint8_t pinMHSensor[2] = {25, 27};
char customKey;

int mh_analog_val = 0;
bool mh_digital_val = true;

uint8_t statusWifi = 0;

char _mode = 'E';

String uidRFID = "";
int fingerID = 0;

uint8_t validate = 0;
uint8_t regist = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("INITIALIZE");
  WIFI_INIT();
  KeyPad_Init();
  rfid_Init();
  Servo_Init();
  mhSensor_Init();
  lcd_Init();
  FingerPrint_Init();
  ValidationFingerInit();
}

void loop()
{
  koneksiWifiChecker();
  //  Serial.println("statusWifi = " + String(statusWifi));
  bacaKeypad();
  bacaRfid();
  mhSensor_Test();

  fingerID = getFingerprintIDez();
  lcd_main();

  delay(50);
}
