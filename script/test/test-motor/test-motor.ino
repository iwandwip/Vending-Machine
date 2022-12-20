#define ENA 15 /* L298N */
#define IN1 2
#define IN2 4

void setup() {
        pinMode(ENA, OUTPUT);
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
}

void loop() {
        runMotorA();
        delay(2000);
}

void runMotorA() {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 255);

        delay(2000);
}

void runMotorB() {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, 255);
        delay(2000);
}
