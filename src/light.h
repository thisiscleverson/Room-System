#ifndef LIGHT_H
#define LIGHT_h

#include <Arduino.h>


class LightController{
   public:
      void set_state_light(bool state);
      bool get_state_light();

      LightController(int lightPin){
         this->lightPin = lightPin;
      }

   private:
      int lightPin;
      bool state_light = false;

      void change_light_state(bool state){
         digitalWrite(this->lightPin, state);
      }
};


void LightController::set_state_light(bool state){
   this->state_light = state;
   this->change_light_state(state);
}


bool LightController::get_state_light(){
   return this->state_light;
}

#endif
