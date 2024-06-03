#include <Arduino.h>

#include "LightController.h"


LightController::LightController(int p) {
   this->pin = p;
}

void LightController::begin(void){
   if(this->pin >= 0){
      pinMode(this->pin, OUTPUT);
   }
}

void LightController::set_state_light(bool state) {
   this->state_light = state;
   change_light_state(state);
}

bool LightController::get_state_light() {
   return this->state_light;
}

void LightController::change_light_state(bool state) {
   digitalWrite(this->pin, state);
}