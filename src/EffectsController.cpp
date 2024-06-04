#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "EffectsController.h"
#include "DelayChecker.h"
 
DelayChecker delayChecker;


EffectsController::EffectsController(Adafruit_NeoPixel& neoPixel) : NeoPixel(neoPixel) {} 


//effects
void EffectsController::colorWipe(int speedDelay){
   //static int i = 0;

   if(delayChecker.checkDelay(speedDelay)){
      if(colorWipeIndex < NeoPixel.numPixels()){
         NeoPixel.setPixelColor(colorWipeIndex, color); 
         NeoPixel.show(); 
         colorWipeIndex++;
      }else{
         colorWipeIndex=0;
      }
   }
}


void EffectsController::rainbow(int speedDelay){
   static long firstPixelHue = 0;

   if(delayChecker.checkDelay(speedDelay)){

      if(firstPixelHue < 5*65536){
         firstPixelHue += 256;
         NeoPixel.rainbow(firstPixelHue);
         NeoPixel.show(); // Update strip with new contents
      }else{
         firstPixelHue = 0;
      }
   }
}


void EffectsController::theaterChase(int speedDelay){
   uint32_t color = 0xff0000;
   static int a = 0;
   static int b = 0;

   if(delayChecker.checkDelay(speedDelay)){
      
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


void EffectsController::colorRange(int speedDelay){
   static uint32_t color = getNextHueColor();
   static int i = 0;

   if(delayChecker.checkDelay(speedDelay)){
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


void EffectsController::breathingOfColors(int speedDelay){
   static int brightness = 0; // Mantém o nível de brilho atual
   static bool increasingBrightness = true; 


   if(delayChecker.checkDelay(speedDelay)){

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


void EffectsController::fireEffect(int cooling, int sparking, int speedDelay) {
   static byte heat[50];
   int cooldown;

   if(delayChecker.checkDelay(speedDelay)){
      for (int i = 0; i < NeoPixel.numPixels(); i++) {
         cooldown = random(0, ((cooling * 10) / NeoPixel.numPixels()) + 2);

         if (cooldown > heat[i]) {
            heat[i] = 0;
         } else {
            heat[i] = heat[i] - cooldown;
         }
      }

      for (int k = NeoPixel.numPixels() - 1; k >= 2; k--) {
         heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
      }

      if (random(255) < sparking) {
         int y = random(7);
         heat[y] = heat[y] + random(160, 255);
      }

      for (int j = 0; j < NeoPixel.numPixels(); j++) {
         setPixelHeatColor(j, heat[j]);
      }

      NeoPixel.show();
   }
   //delay(speedDelay);
}



void EffectsController::setPixelHeatColor(int pixel, byte temperature) {
   byte t192 = round((temperature / 255.0) * 191);

   byte heatramp = t192 & 63;
   heatramp <<= 2;

   if (t192 > 128) {
      NeoPixel.setPixelColor(pixel, 255, 255, heatramp);
   } else if (t192 > 64) {
      NeoPixel.setPixelColor(pixel, 255, heatramp, 0);
   } else {
      NeoPixel.setPixelColor(pixel, heatramp, 0, 0);
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

   if(effectsIndex > 5){
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
      case 5:
         fireEffect(55, 120, 100);
         break;
   }
}