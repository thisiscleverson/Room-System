#ifndef EFFECTSCONTROLLER_H
#define EFFECTSCONTROLLER_H

#include <Adafruit_NeoPixel.h>

class EffectsController{
   public:
     /**
      * @brief Construtor da classe EffectsController.
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
      

      /**
      * @brief Define a cor dos LEDs.
      * 
      * Esta função define a cor de todos os LEDs da fita para a cor especificada.
      * 
      * @param color A cor a ser definida, representada como um valor de 32 bits no formato RGB (8 bits para cada canal de cor: vermelho, verde e azul).
      * 
      * Exemplo de uso:
      * 
      * @code
      *  uint32_t red = 0xFF0000;  // Cor vermelha
      *  setColor(red);            // Define todos os LEDs para vermelho
      * @endcode
      */
      void setColor(uint32_t color);
      
      /**
       * @brief Controla a transição entre diferentes efeitos de iluminação.
       * 
       * Esta função é responsável por alternar entre os seguintes efeitos de iluminação:
       * 
       * - `colorWipe`: Um efeito de limpeza de cor.
       * - `rainbow`: Um efeito de arco-íris.
       * - `theaterChase`: Um efeito de perseguição no estilo teatro.
       * - `colorRange`: Um efeito que exibe uma gama de cores.
       * - `breathingOfColors`: Um efeito de cores pulsantes.
       * - `fireEffect`: Um efeito que simula chamas.
       * 
       * @note Chame esta função para passar ao próximo efeito na sequência.
       */
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