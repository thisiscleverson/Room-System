#include <EffectsController.h>
#include <ReadButtonNextEffect.h>


unsigned long debounceDelay  = 25;
unsigned long lastDebounceTime = 0;

bool lastButtonState;
bool beforeStateButton = LOW;

void readButtonNextEffet(int pinButton, EffectsController & effects){
   int buttonReading = digitalRead(pinButton);

   if (buttonReading != lastButtonState) {
      lastDebounceTime = millis();
   }

   if ((millis() - lastDebounceTime) > debounceDelay) {
      if(buttonReading == LOW && beforeStateButton == HIGH){
         effects.nextEffect();
         delay(50);
      }
      beforeStateButton = digitalRead(pinButton);
   }

   lastButtonState = buttonReading;
}