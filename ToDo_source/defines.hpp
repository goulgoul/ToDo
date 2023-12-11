#include <stdint.h>
#include <Adafruit_NeoPixel.h>

#define BAUD_RATE 9600
#define NOMBRE_ACTIVITES 3
#define PIN_FIN_ACTIVITE_1 3
#define BOUTON_JAUGE 2
#define PIN_JAUGE_LED 6
// #define NOMBRE_LEDS 75
#define NOMBRE_LEDS_JAUGE 18
// Adafruit_NeoPixel pixels(NOMBRE_LEDS, PIN_JAUGE_LEDS, NEO_RGB + NEO_KHZ800);

#define BLANC 0xFFFFFF
#define VIOLET 0x614084
#define BLEU 0x0000FF
#define NOIR 0x000000
#define ROUGE 0xFF0000
#define VERT 0x00FF00
#define JAUNE 0xFFFF00

#define DUREE_PERIODE_SECONDES 4 * 60 * 3600