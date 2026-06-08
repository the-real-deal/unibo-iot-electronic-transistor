#include <Arduino.h>
#pragma once

// [TODO] check these to be correct
#define BUTTON_PIN PIN0

#define SERVO_PIN PIN3

#define POTENTIOMETER_PIN A0

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#define POT_DEBOUNCE_TIME 300

#define AUTOMATIC_STATE F("automatic")
#define UNCONNECTED_STATE F("unconnected")
#define MANUAL_STATE F("manual")