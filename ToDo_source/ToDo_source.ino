#include "defines.hpp"
#include "fonctions.hpp"

typedef enum
{
  DEBUT_JOURNEE,
  ACTIVITE_EN_ATTENTE,
  ACTIVITE_EN_COURS,
  ACTIVITE_EN_PAUSE,
  ACTIVITE_TERMINEE,
  JOURNEE_TERMINEE
} etats_possibles_t;

etats_possibles_t etat_actuel;
uint8_t numero_activite = 0;
uint32_t timer_activite = 0;

void setup() 
{
  Serial.begin(BAUD_RATE);
}

void loop() 
{
  switch(etat_actuel)
  {
    case DEBUT_JOURNEE: //init
      etat_actuel = ACTIVITE_EN_ATTENTE;
      Serial.println("Début de la journée");
      break;

    case ACTIVITE_EN_ATTENTE:
      // clignoter jauge
      Serial.println("Activité en attente");

      while (!digitalRead(BOUTON_JAUGE))
      {
        clignoter_jauge(BLANC);
      }
      etat_actuel = ACTIVITE_EN_COURS;
      break;

    case ACTIVITE_EN_COURS:
      Serial.println("Activité en cours");

      while (!digitalRead(BOUTON_JAUGE))
      {
        if (digitalRead(pins_fin_activite[numero_activite]))
        {
          etat_actuel = ACTIVITE_TERMINEE;
          break;
        }
        timer_activite++;
        delay(1000);
      }
      etat_actuel = ACTIVITE_EN_PAUSE;
      
      break;
      
    case ACTIVITE_EN_PAUSE:
      Serial.println("Activité en pause");

      // FAIRE CLIGNOTER LA JAUGE
      while(!digitalRead(BOUTON_JAUGE))
      {
        clignoter_jauge(ORANGE);
      }
      etat_actuel = ACTIVITE_EN_COURS;
      
      break;

    case ACTIVITE_TERMINEE:
      Serial.println("Activité terminée");

      actualiser_jauge();
      if (numero_activite == NOMBRE_ACTIVITES)
      {
        etat_actuel = JOURNEE_TERMINEE;
        break;
      }
      numero_activite++;
      break;

    case JOURNEE_TERMINEE:
      Serial.println("Journée terminée");

      break;

    default:
      Serial.println("Défaut");

      break;
  }
}
