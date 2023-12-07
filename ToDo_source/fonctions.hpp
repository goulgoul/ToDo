#include "defines.hpp"

void clignoter_jauge(Adafruit_NeoPixel& jauge, uint32_t couleur)
{
  for (int i = 0; i < NOMBRE_LEDS_JAUGE; i++)
    jauge.setPixelColor(i, couleur);
  jauge.show();
  delay(200);
  jauge.clear();
  jauge.show();
  delay(200);
}

void actualiser_jauge()
{
  
}

