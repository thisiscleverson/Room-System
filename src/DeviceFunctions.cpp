#include <Arduino.h>
#include <IRController.h>
#include <DeviceFunctions.h>
#include <LightController.h>
#include <EffectsController.h>
#include <Adafruit_NeoPixel.h>

extern IRController IR;
extern LightController light;
extern EffectsController effects;
extern Adafruit_NeoPixel pixels;


void stripLed(uint8_t brightness, uint32_t rgb){
   int red,green,blue;
  
   red   = ((rgb >> 16) & 0xFF);
   green = ((rgb >>  8) & 0xFF);
   blue  = ((rgb & 0xFF));

   pixels.setBrightness(brightness);
   effects.setColor(pixels.Color(red,green,blue));

}

void lightState(uint8_t state){
   if(state){
      light.set_state_light(true);
   }else{
      light.set_state_light(false);
   }   
}

void activateAirConditioning(uint8_t _){IR.sendIRCommand(1);}

void activateTemp18(uint8_t _){IR.sendIRCommand(2);}

void activateTemp23(uint8_t _){IR.sendIRCommand(3);}
