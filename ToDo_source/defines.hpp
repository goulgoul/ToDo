#include <stdint.h>
#include <Adafruit_NeoPixel.h>

#define BAUD_RATE 9600
#define NOMBRE_ACTIVITES 3
#define PIN_FIN_ACTIVITE_1 3
#define BOUTON_JAUGE 2
// #define PIN_JAUGE_LEDS 9
// #define NOMBRE_LEDS 75

// Adafruit_NeoPixel pixels(NOMBRE_LEDS, PIN_JAUGE_LEDS, NEO_RGB + NEO_KHZ800);

#define BLANC pixels.Color(64, 64, 64)
#define ORANGE pixels.Color(64, 32, 0)
