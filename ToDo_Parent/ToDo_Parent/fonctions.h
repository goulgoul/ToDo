#include <stdint.h>

#define ROUGE 0xFF0000
#define JAUNE 0xFFFF00
#define VERT 0x00FF00
#define NOIR 0x000000


void actualiser_emotion_rouge(Adafruit_NeoPixel& emotions, int nombre_emotions)
{
  for (int i = 0; i < 5; i++)
  {
    emotions.setPixelColor(i, NOIR);
  }
  emotions.show();

  if (nombre_emotions > 5)
    nombre_emotions = 5;
  if (nombre_emotions < 0)
    nombre_emotions = 0;
  for (int i = 0; i < nombre_emotions; i++)
  {
    emotions.setPixelColor(i, ROUGE);
  }
  
  emotions.show();
}

void actualiser_emotion_jaune(Adafruit_NeoPixel& emotions, int nombre_emotions)
{
  for (int i = 0; i < 5; i++)
  {
    emotions.setPixelColor(5 + i, NOIR);
  }
  if (nombre_emotions > 5)
    nombre_emotions = 5;
  if (nombre_emotions < 0)
    nombre_emotions = 0;
  for (int i = 0; i < nombre_emotions; i++)
  {
    emotions.setPixelColor(5 + i, JAUNE);
  }

  emotions.show();
}

void actualiser_emotion_verte(Adafruit_NeoPixel& emotions, int nombre_emotions)
{
  for (int i = 0; i < 5; i++)
  {
    emotions.setPixelColor(10 + i, NOIR);
  }

  if (nombre_emotions > 5)
    nombre_emotions = 5;
  if (nombre_emotions < 0)
    nombre_emotions = 0;
  for (int i = 0; i < nombre_emotions; i++)
  {
    emotions.setPixelColor(10 + i, VERT);
  }

  emotions.show();
}





