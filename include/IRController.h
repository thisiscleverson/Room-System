#ifndef IRCONTROLLER_H
#define IRCONTROLLER_H

//#include <IRremoteESP8266.h>
#include <IRsend.h>


#define FREQUENCY 38

class IRController {
   public:

     /**
      * ativador de codigo IR.
      *
      * @param IRsend& irSender
      * 
      * recebe o objeto do IRsend
      */
      IRController(IRsend& irSender); 

     /**
      * ativador de codigo IR.
      *
      * @param commandIndex contém o index de qual código IR deve ser ativado. Sendo
      * 1 - para ligar o ar-condicionado,
      * 2 - para mudar a temperatura para 18, 
      * 3 - para mudar a temperatura para 23.
      */
      void sendIRCommand(byte commandIndex); 

   private:
      IRsend& irSender;
      
      static const uint16_t turnON[];
      static const uint16_t temp18[];
      static const uint16_t temp23[];
};


#endif