#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

extern LightController light;


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay    = 50;
unsigned long longPressTime    = 1000; // timer 1 s button long press 
unsigned long buttonHoldTime   = 0;

bool buttonState;
bool lastButtonState;
bool longPressActive = false;


void read_button(int buttonPin);

void ar();

void read_button(int buttonPin) {
  int buttonReading = digitalRead(buttonPin);

  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonReading != buttonState) {
      buttonState = buttonReading;
      if (buttonState == HIGH && longPressActive == false) {
        // Toque curto, alternar a luz
        Serial.println("Luz alternada");
        bool stateLight = light.get_state_light();
        light.set_state_light(!stateLight);
      } else {
        // Botão pressionado
        buttonHoldTime = millis();
        longPressActive = false;
      }
    }
  }

  if (buttonState == LOW && !longPressActive && (millis() - buttonHoldTime) >= longPressTime) {
    longPressActive = true;
    ar();
  }

  lastButtonState = buttonReading;
}

void ar(){
  Serial.println("Ar condicionado ligado");
}

#endif