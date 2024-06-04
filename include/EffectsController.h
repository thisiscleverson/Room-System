#ifndef EFFECTSCONTROLLER_H
#define EFFECTSCONTROLLER_H

#include <Adafruit_NeoPixel.h>

class EffectsController{
   public:
      /*!
       @brief Construtor da classe EffectsController.
      * 
      * Este construtor inicializa a classe com uma referência a um objeto
      * Adafruit_NeoPixel, que é usado para controlar o strip de LEDs.
      * 
      * @param neoPixel Referência a um objeto Adafruit_NeoPixel.
      * 
      * A referência ao objeto Adafruit_NeoPixel é armazenada no membro `NeoPixel`
      * da classe para ser usado posteriormente nos métodos da classe.
      */
      EffectsController(Adafruit_NeoPixel& neoPixel);
      
      void setColor(uint32_t color);
      void nextEffect();
      void loop();
   
   private:
      Adafruit_NeoPixel& NeoPixel;
      
      uint16_t hue = 0;
      uint32_t color = 0xff0000;
      byte effectsIndex = 0;
      byte colorWipeIndex = 0;

      // private method
      void resertColorWipeIndex();
      void setPixelHeatColor(int pixel, byte temperature);
      uint32_t getNextHueColor();
      
      // effects
      void colorWipe(int speedDelay);
      void rainbow(int speedDelay);
      void theaterChase(int speedDelay);
      void colorRange(int speedDelay);
      void breathingOfColors(int speedDelay);
      void fireEffect(int cooling, int sparking, int speedDelay);
};

#endif