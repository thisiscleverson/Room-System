#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "EffectsController.h"
#include "DelayChecker.h"
 
DelayChecker delayChecker;


EffectsController::EffectsController(Adafruit_NeoPixel& neoPixel) : NeoPixel(neoPixel) {} 


//effects
void EffectsController::colorWipe(int wait){
   //static int i = 0;

   if(delayChecker.checkDelay(wait)){
      if(colorWipeIndex < NeoPixel.numPixels()){
         NeoPixel.setPixelColor(colorWipeIndex, color); 
         NeoPixel.show(); 
         colorWipeIndex++;
      }else{
         colorWipeIndex=0;
      }
   }
}


void EffectsController::rainbow(int wait){
   static long firstPixelHue = 0;

   if(delayChecker.checkDelay(wait)){

      if(firstPixelHue < 5*65536){
         firstPixelHue += 256;
         NeoPixel.rainbow(firstPixelHue);
         NeoPixel.show(); // Update strip with new contents
      }else{
         firstPixelHue = 0;
      }
   }
}


void EffectsController::theaterChase(int wait){
   uint32_t color = 0xff0000;
   static int a = 0;
   static int b = 0;

   if(delayChecker.checkDelay(wait)){
      
      b++;
      if (b >= 3) {
         b = 0;
         a++;
         if (a >= 10) {
            a = 0;
         }
      }

      NeoPixel.clear(); 
      for(int c=b; c<NeoPixel.numPixels(); c += 3) {
         NeoPixel.setPixelColor(c, color); 
      }
      NeoPixel.show();
   }
}


void EffectsController::colorRange(int wait){
   static uint32_t color = getNextHueColor();
   static int i = 0;

   if(delayChecker.checkDelay(wait)){
      if(i < NeoPixel.numPixels()){
         NeoPixel.setPixelColor(i, color);         //  Set pixel's color (in RAM)
         NeoPixel.show(); 
         i++;
      }else{
         i=0;
         color = getNextHueColor();
      }
   }
}


void EffectsController::breathingOfColors(int wait){
   static int brightness = 0; // Mantém o nível de brilho atual
   static bool increasingBrightness = true; 


   if(delayChecker.checkDelay(wait)){

         // Ajusta o brilho gradualmente
         if (increasingBrightness) {
            brightness+= 5;
            if (brightness >= 255) {
               brightness = 255;
               increasingBrightness = false;
            }
         } else {
            brightness-=5;
            if (brightness <= 5) {
               
               uint32_t color = getNextHueColor();

               NeoPixel.fill(color); 

               brightness = 5;
               increasingBrightness = true;
            }
         }

         // Define o brilho e exibe os pixels
         NeoPixel.setBrightness(brightness);
         NeoPixel.show();
   }
}



uint32_t EffectsController::getNextHueColor(){
   hue += 65536 / 30;

   if (hue >= 65536) hue -= 65536; 

   uint16_t scaledHue = hue / 255; // Scale to 0-255 for NeoPixel library
   uint32_t colorFromHue = NeoPixel.gamma32(NeoPixel.ColorHSV(scaledHue * 256));

   return colorFromHue;
}


void EffectsController::resertColorWipeIndex(){
   colorWipeIndex = 0;
}

void EffectsController::setColor(uint32_t newColor){
   color = newColor;
   resertColorWipeIndex();
   effectsIndex = 0;
}


void EffectsController::nextEffect(){
   effectsIndex++;

   if(effectsIndex > 4){
      effectsIndex = 0;
   }

   if(effectsIndex == 0){
      resertColorWipeIndex();
   }

   NeoPixel.setBrightness(255); // devo retirar ?
}


void EffectsController::loop(){

   switch(effectsIndex) {
      case 0:
         colorWipe(50);
         break;
      case 1:
         rainbow(10);
         break;
      case 2:
         theaterChase(50);
         break;
      case 3:
         colorRange(50);
         break;
      case 4:
         breathingOfColors(50);
         break;
   }
}