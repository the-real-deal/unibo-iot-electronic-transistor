#include <Arduino.h>
#include "config.h"
#include "./controller/systemController.h"

void setup()
{
  if (DEBUG != 0)
  {
    Serial.begin(9600);
  }
  // initialize the lcd

  setupLcd();
  gameModel();

  /* Game Buttons and LEDs */
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

  /* Enable Interrupts */
  interruptButton1();
  enableInterruptGameButtons();

  /* Error LED */
  pinMode(RED_LED, OUTPUT);

  /* Potentiometer */
  pinMode(A0, INPUT);
}

void loop()
{
  control();
  delay(50);
}