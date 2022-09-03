#include <Servo_ESP32.h>
Servo_ESP32 servo1;
Servo_ESP32 servo2;
Servo_ESP32 servo3;

void Servo_Init() {
  servo1.attach(33);
  servo1.write(90);
}

void servoBuka() {
  servo1.write(85);
}

void servoTutup() {
  servo1.write(90);
}
