#include <Adafruit_NeoPixel.h>
#include "fonctions.h"

#define NOMBRE_LEDS_EMOTIONS 15
#define LUMINOSITE 30
#define PIN_LEDS_EMOTIONS 9
#define BOUTON_ROUGE 2
#define BOUTON_JAUNE 3
#define BOUTON_VERT 4

typedef enum {
  ATTENDRE,
  MODIFIER_ROUGE,
  MODIFIER_JAUNE,
  MODIFIER_VERT
} etats_possibles_t;

Adafruit_NeoPixel emotions(NOMBRE_LEDS_EMOTIONS, PIN_LEDS_EMOTIONS, NEO_GRB + NEO_KHZ800);
etats_possibles_t etat_actuel = ATTENDRE;
int nombre_emotions_rouges = 0;
int nombre_emotions_jaunes = 0;
int nombre_emotions_vertes = 0;
int timer = 0;

void routine_modifier_rouge() {
  while (digitalRead(BOUTON_ROUGE) && timer < 70) {
    timer++;
    delay(10);
  }
  timer >= 70 ? nombre_emotions_rouges-- : nombre_emotions_rouges++;

  if (nombre_emotions_rouges < 0)
    nombre_emotions_rouges = 0;

  actualiser_emotion_rouge(emotions, nombre_emotions_rouges);
  while (digitalRead(BOUTON_ROUGE))
    ;
}

void routine_modifier_jaune() {
  while (digitalRead(BOUTON_JAUNE) && timer < 70) {
    timer++;
    delay(10);
  }
  timer >= 70 ? nombre_emotions_jaunes-- : nombre_emotions_jaunes++;

  if (nombre_emotions_jaunes < 0)
    nombre_emotions_jaunes = 0;

  actualiser_emotion_jaune(emotions, nombre_emotions_jaunes);
  while (digitalRead(BOUTON_JAUNE))
    ;
}
void routine_modifier_vert() {
  while (digitalRead(BOUTON_VERT) && timer < 70) {
    timer++;
    delay(10);
  }
  timer >= 70 ? nombre_emotions_vertes-- : nombre_emotions_vertes++;

  if (nombre_emotions_vertes < 0)
    nombre_emotions_vertes = 0;

  actualiser_emotion_verte(emotions, nombre_emotions_vertes);
  while (digitalRead(BOUTON_VERT))
    ;
}



void setup() {
  // put your setup code here, to run once:
  pinMode(BOUTON_ROUGE, INPUT_PULLDOWN);
  pinMode(BOUTON_JAUNE, INPUT_PULLDOWN);
  pinMode(BOUTON_VERT, INPUT_PULLDOWN);
  emotions.begin();
  emotions.setBrightness(LUMINOSITE);
  emotions.show();

  Serial.begin(9600);
}

void loop() {
  switch (etat_actuel) {
    case ATTENDRE:
      timer = 0;
      if (nombre_emotions_rouges > 5)
        nombre_emotions_rouges = 5;

      if (nombre_emotions_jaunes > 5)
        nombre_emotions_jaunes = 5;
      if (nombre_emotions_jaunes < 0)
        nombre_emotions_jaunes = 0;

      if (nombre_emotions_vertes > 5)
        nombre_emotions_vertes = 5;
      if (nombre_emotions_vertes < 0)
        nombre_emotions_vertes = 0;

      Serial.println("Attente");
      if (digitalRead(BOUTON_ROUGE)) {
        etat_actuel = MODIFIER_ROUGE;
        break;
      }
      if (digitalRead(BOUTON_JAUNE)) {
        etat_actuel = MODIFIER_JAUNE;
        break;
      }
      if (digitalRead(BOUTON_VERT)) {
        etat_actuel = MODIFIER_VERT;
        break;
      }
      break;


    case MODIFIER_ROUGE:
      Serial.println("ROUGE");
      routine_modifier_rouge();
      etat_actuel = ATTENDRE;
      break;

    case MODIFIER_JAUNE:
      Serial.println("JAUNE");
      routine_modifier_jaune();
      etat_actuel = ATTENDRE;
      break;

    case MODIFIER_VERT:
      Serial.println("VERT");
      routine_modifier_vert();
      etat_actuel = ATTENDRE;
      break;


    default:
      etat_actuel = ATTENDRE;
      break;
  }
  delay(100);
}
