#include <Keypad_I2C.h>
#include <Keypad.h>  // GDY120705
#include <Wire.h>
#define I2CADDR 0x21
#define ROWS 4  
#define COLS 4  

char hexaKeys[ROWS][COLS] = {
        { '1', '2', '3', 'A' },
        { '4', '5', '6', 'B' },
        { '7', '8', '9', 'C' },
        { 'E', '0', 'F', 'D' }
};
byte rowPins[ROWS] = { 3, 2, 1, 0 };  
byte colPins[COLS] = { 7, 6, 5, 4 };  
Keypad_I2C customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);

void setup() {
        customKeypad.begin();
        Wire.begin();
}

void loop() {
        char customKey = customKeypad.getKey();
        if (customKey != NO_KEY) {
                Serial.print("Key = ");
                Serial.println(customKey);
        }
}
