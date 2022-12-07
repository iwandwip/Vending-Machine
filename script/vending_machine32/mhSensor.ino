#include "Pins.h"

void mhSensor_Init() {
        //  pinMode (pinMHSensor[0], INPUT);
        pinMode(pinMHSensor[1], INPUT);
}
void mhSensor_Test() {
        //  mh_analog_val = analogRead(pinMHSensor[0]); // reads the analog input from the IR distance sensor
        mh_digital_val = !digitalRead(pinMHSensor[1]);  // reads the digital input from the IR distance sensor
        //  Serial.print(" Analogue = ");
        //  Serial.print(mh_analog_val);
        //  Serial.print("\t Digital =");
        //  Serial.println(mh_digital_val);
        //    if (mh_digital_val ) Serial.println("TERDETEKSI");
        //    else Serial.println("TIDAK TERDETEKSI");
        //  delay(100);
}