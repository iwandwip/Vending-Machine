#pragma once

/* 12, 14, 27, 26, 25, 33, 32, 2*/

#define MHSENS1 0
#define MHSENS2 0

#define SS
#define MISO
#define MOSI
#define SS_PIN 5   /* ESP32 pin GIOP5 */
#define RST_PIN 15 /* ESP32 pin GIOP27 */

#define IN1 27  // deklarasi pin IN1
#define IN3 14  // deklarasi pin IN3
#define ENA 26  // deklarasi pin ENA
#define ENB 12  // deklarasi pin ENB

#define IN12 32  // deklarasi pin IN1
#define IN32 33  // deklarasi pin IN3
#define ENA2 2   // deklarasi pin ENA
#define ENB2 25  // deklarasi pin ENB

namespace driver {

const uint8_t satu[4] = { 26, 27, 12, 14 };
const uint8_t dua[4] = { 4, 32, 25, 33 };
/*
        #define   ENA        26
        #define   IN1        27
        #define   IN2        GND
        #define   ENB        12
        #define   IN3        14
        #define   IN4        GND

        #define   ENA        2
        #define   IN1        32
        #define   IN2        GND
        #define   ENB        25
        #define   IN3        33
        #define   IN4        GND

*/
};