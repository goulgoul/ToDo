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

void actualiser_jauge(Adafruit_NeoPixel& jauge, const uint32_t couleurs_jauge[NOMBRE_LEDS_JAUGE])
{
  for (int i = 0; i < NOMBRE_LEDS_JAUGE; i++)
  {
    jauge.setPixelColor(i, couleurs_jauge[i]);
  }
  jauge.show();
}

uint32_t* repartir_temps(uint8_t nombre_taches_terminees, const uint32_t* temps_par_activite)
{
  uint32_t tableau[nombre_taches_terminees];
  uint32_t somme_temps = 0;
  for (int i = 0; i < nombre_taches_terminees; i++)
  {
    somme_temps += temps_par_activite[i];
  }
  for (int i = 0; i < nombre_taches_terminees; i++)
  {
    tableau[i] = temps_par_activite[i] / somme_temps;
  }
  return tableau;
}

