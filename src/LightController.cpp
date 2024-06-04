#include <Arduino.h>
#include <LightController.h>


LightController::LightController(int p) {
   pin = p;
}

void LightController::begin(void){
   if(pin >= 0){
      pinMode(pin, OUTPUT);
   }
}

void LightController::set_state_light(bool state) {
   state_light = state;
   change_light_state(state);
}

bool LightController::get_state_light() {
   return state_light;
}

void LightController::change_light_state(bool state) {
   digitalWrite(pin, state);
}