#include <Arduino.h>
#include <ButtonHandler.h>

ButtonHandler::ButtonHandler(int pin, LightController& light) : buttonPin(pin), light(light) {}

void ButtonHandler::begin(){
   pinMode(buttonPin, INPUT_PULLUP);
}

void ButtonHandler::readButton(){
   int buttonReading = digitalRead(buttonPin);

   if (buttonReading != lastButtonState) {
      lastDebounceTime = millis();
   }

   if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonReading != buttonState) {
         buttonState = buttonReading;
         if (buttonState == HIGH && !longPressActive) {
            //Serial.println("Luz alternada");
            bool stateLight = light.get_state_light();
            light.set_state_light(!stateLight);
         } else {
            buttonHoldTime = millis();
            longPressActive = false;
         }
      }
   }

   if (buttonState == LOW && !longPressActive && (millis() - buttonHoldTime) >= longPressTime) {
      longPressActive = true;
      Serial.println("Ar condicionado!");
   }

   lastButtonState = buttonReading;
}