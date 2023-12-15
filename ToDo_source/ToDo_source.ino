#include "defines.hpp"
#include "fonctions.hpp"
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <MFRC522.h>

uint8_t pins_fin_activite[] = { 4, 5, 6 };
// UART RFID_1(digitalPinToPinName(4), digitalPinToPinName(5), NC, NC);

MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key;
byte nuidPICC[4];


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


Adafruit_NeoPixel jauge(NOMBRE_LEDS_JAUGE, PIN_JAUGE_LED, NEO_GRB + NEO_KHZ800);

void isr_fin_activite() {
  if (etat_actuel != ACTIVITE_EN_COURS) {
    SIGNAL_ACTIVITE_TERMINEE = false;
    return;
  }
  SIGNAL_ACTIVITE_TERMINEE = true;
}


void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "0" : "");
    Serial.print(buffer[i], HEX);
  }
}

String lire_nuid_rfid() {
  while (!rfid.PICC_IsNewCardPresent())
    ;

  // Verify if the NUID has been readed
  while (!rfid.PICC_ReadCardSerial())
    ;

  String nuid = "";
  for (int i = 0; i < rfid.uid.size; i++) {
    nuid += String(rfid.uid.uidByte[i]);
  }
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

  return nuid;
}


void setup() {
  Serial.begin(BAUD_RATE);
  SPI.begin();

  rfid.PCD_Init();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }


  jauge.begin();
  delay(1000);
  pinMode(BOUTON_JAUGE, INPUT_PULLDOWN);
  jauge.setBrightness(10);

  Serial.println("Init done");
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.



  ////////////////////////////////

  switch (etat_actuel) {
    case DEBUT_JOURNEE:
      Serial.println("Debut journée");
      etat_actuel = ACTIVITE_EN_ATTENTE;
      SIGNAL_ACTIVITE_TERMINEE = false;
      numero_activite = 0;
      timer_activite = 0;
      break;

    case ACTIVITE_EN_ATTENTE:

      numero_activite++;
      attachInterrupt(digitalPinToInterrupt(pins_fin_activite[numero_activite - 1]), isr_fin_activite, RISING);

      Serial.println("Activité n° " + String(numero_activite) + " en attente");
      while (!digitalRead(BOUTON_JAUGE)) {
        clignoter_jauge(jauge, BLEU);
      }
      if (lire_nuid_rfid() == NUID_RFID) {
        Serial.println("RFID TROUVÉ !");
      }
      timer_activite = 0;
      etat_actuel = ACTIVITE_EN_COURS;
      break;

    case ACTIVITE_EN_COURS:
      Serial.println("Activité n° " + String(numero_activite) + " en cours");
      delay(1000);
      while (!SIGNAL_ACTIVITE_TERMINEE) {
        if (digitalRead(BOUTON_JAUGE)) {
          etat_actuel = ACTIVITE_EN_PAUSE;
          break;
        }
        timer_activite++;
        delay(10);
      }

      if (etat_actuel == ACTIVITE_EN_PAUSE) {
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
      while (!digitalRead(BOUTON_JAUGE)) {
        clignoter_jauge(jauge, VIOLET);
      }
      etat_actuel = ACTIVITE_EN_COURS;
      break;

    case ACTIVITE_TERMINEE:
      detachInterrupt(digitalPinToInterrupt(pins_fin_activite[numero_activite]));
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
