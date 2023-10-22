#ifndef Blinkrate_Ctrl
#define Blinkrate_Ctrl

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

static const char led_pin = LED_BUILTIN;

static void toggleLED(void *parameter);
static void BlinkRateCtrl(void *parameter);

#endif