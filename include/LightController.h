#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <Arduino.h>

class LightController {
   public:
      LightController(int lightPin);
      
      void begin(void);

      /**
      * função para modificar o estado da lampada.
      * @param `state` deve ser do tipo `boolean`. 
      * `true` para ligado e `false` para desligado.
      */
      void set_state_light(bool state);

      /**
      * função para retornar o estado da lampada.
      * 
      * @return `true` para ligado e `false`para desligado. 
      */
      bool get_state_light();

   private:
      bool state_light = false;
      void change_light_state(bool state);

   protected:
      int pin;
};

#endif // LIGHTCONTROLLER_H
