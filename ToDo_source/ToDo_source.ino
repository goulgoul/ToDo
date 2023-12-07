#include "defines.hpp"
#include "fonctions.hpp"
uint8_t pins_fin_activite[] = { 4, 5, 6 };

typedef enum {
  DEBUT_JOURNEE,
  ACTIVITE_EN_ATTENTE,
  ACTIVITE_EN_COURS,
  ACTIVITE_EN_PAUSE,
  ACTIVITE_TERMINEE,
  JOURNEE_TERMINEE
} etats_possibles_t;

etats_possibles_t etat_actuel = DEBUT_JOURNEE;

bool SIGNAL_ACTIVITE_TERMINEE = false;
uint8_t numero_activite = 0;
uint32_t timer_activite = 0;

void isr_fin_activite_1()
{
  if (etat_actuel != ACTIVITE_EN_COURS)
  {
    SIGNAL_ACTIVITE_TERMINEE = false;
    return;
  }
  SIGNAL_ACTIVITE_TERMINEE = true;
}


void setup() 
{
  Serial.begin(BAUD_RATE);
  delay(1000);
  pinMode(BOUTON_JAUGE, INPUT_PULLDOWN);
 
  attachInterrupt(digitalPinToInterrupt(PIN_FIN_ACTIVITE_1), isr_fin_activite_1, CHANGE);
  Serial.println("Init done");
}

void loop() 
{
  switch (etat_actuel) 
  {
    case DEBUT_JOURNEE:
      Serial.println("Debut journée");
      etat_actuel = ACTIVITE_EN_ATTENTE;
      numero_activite = 0;
      timer_activite = 0;
      break;

    case ACTIVITE_EN_ATTENTE:
      numero_activite++;
      Serial.println("Activité n° " + String(numero_activite) + " en attente");
      while (!digitalRead(BOUTON_JAUGE));
      timer_activite = 0;
      etat_actuel = ACTIVITE_EN_COURS;
      break;
  
    case ACTIVITE_EN_COURS:
      Serial.println("Activité n° " + String(numero_activite) + " en cours");
      delay(1000);
      while (!SIGNAL_ACTIVITE_TERMINEE)
      {
        if (digitalRead(BOUTON_JAUGE))
        {
          etat_actuel = ACTIVITE_EN_PAUSE;
          break;
        }
        timer_activite++;
        delay(10);
      }
      
      if (etat_actuel == ACTIVITE_EN_PAUSE)
      {
        break;
      }

      timer_activite /= 100;
      Serial.println("Timer activité n° " + String(numero_activite) + " : " + String(timer_activite) + " secondes.");
      etat_actuel = ACTIVITE_TERMINEE;
      delay(1000);
      break;

    case ACTIVITE_EN_PAUSE:
      Serial.println("Activité n° " + String(numero_activite) + " en pause");
      delay(1000);
      while(!digitalRead(BOUTON_JAUGE));
      etat_actuel = ACTIVITE_EN_COURS;
      break;
  
    case ACTIVITE_TERMINEE:
        numero_activite >= NOMBRE_ACTIVITES ? etat_actuel = JOURNEE_TERMINEE : etat_actuel = ACTIVITE_EN_ATTENTE;
        SIGNAL_ACTIVITE_TERMINEE = false;
        break;
    
    case JOURNEE_TERMINEE:
      Serial.println("Journée terminée");
      etat_actuel = DEBUT_JOURNEE;
      break;

    default:
      Serial.println("Default case");
      etat_actuel = DEBUT_JOURNEE;
      break;
  }
  delay(1000);
}
