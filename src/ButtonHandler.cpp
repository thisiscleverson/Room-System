#include <Arduino.h>
#include <ButtonHandler.h>
#include <IRController.h>

extern IRController IR;

ButtonHandler::ButtonHandler(int pin, LightController& light) : buttonPin(pin), light(light) {}

void ButtonHandler::begin(){
   pinMode(buttonPin, INPUT_PULLUP);
}

//TODO: separar responsabilidades em outros metodos
void ButtonHandler::readButton(){
   int buttonReading = digitalRead(buttonPin);

   if (buttonReading != lastButtonState) {
      lastDebounceTime = millis();
   }

   if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonReading != buttonState) {
         buttonState = buttonReading;
         if (buttonState == HIGH && !longPressActive) {
            
            bool stateLight = light.get_state_light();
            light.set_state_light(!stateLight);
         } else {
            buttonHoldTime = millis();
            longPressActive = false;
         }
      }
   }

   // reponsavel por ligar o ar condicionado. Quando o botão for apertado e mantido por 1s, o comando IR sera acionado.
   if (buttonState == LOW && !longPressActive && (millis() - buttonHoldTime) >= longPressTime) {
      longPressActive = true;
      IR.sendIRCommand(1);
   }

   lastButtonState = buttonReading;
}