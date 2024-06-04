#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <LightController.h>

class ButtonHandler {
   public:
      ButtonHandler(int buttonPin, LightController& light);

      void begin();
      void readButton();

   private:
      int buttonPin;
      LightController& light;

      unsigned long lastDebounceTime = 0;
      unsigned long debounceDelay    = 50;
      unsigned long longPressTime    = 1000; // timer 1 s button long press 
      unsigned long buttonHoldTime   = 0;

      bool buttonState;
      bool lastButtonState;
      bool longPressActive = false;
};

#endif