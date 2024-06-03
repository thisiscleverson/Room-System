#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <Arduino.h>

class LightController {
   public:
      LightController(int lightPin);
      
      void begin(void);
      void set_state_light(bool state);
      bool get_state_light();

   private:
      bool state_light = false;
      void change_light_state(bool state);

   protected:
      int pin;

};

#endif // LIGHTCONTROLLER_H
