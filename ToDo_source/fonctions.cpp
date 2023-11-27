#include "defines.hpp"

uint32_t timer_activite_en_cours = 0;

void commencer_activite() 
{
  while(!FIN_ACVITITE)
  {
    if (PAUSE)
    {
      while(!FIN_PAUSE);
    }
    timer_activite_en_cours++;
    delay(1000);
  }
  
}

void cycle_activites()
{
  for (int numero_activite = 1; numero_activite <= 12; numero_activite++)
  {
    while(!DEBUT_ACTIVITE) { Serial.println("En attente du début des activités..."); delay(1000); }
    commencer_activite(numero_activite);

  } 
}


