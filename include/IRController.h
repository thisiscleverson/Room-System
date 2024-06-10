#ifndef IRCONTROLLER_H
#define IRCONTROLLER_H

#include <IRremoteESP8266.h>
#include <IRsend.h>


#define FREQUENCY 38

class IRController {
   public:
      IRController(IRsend& irSender); 

      void sendIRCommand(byte commandIndex); 

   private:
      IRsend& irSender;
      
      static const uint16_t turnON[];
      static const uint16_t temp18[];
      static const uint16_t temp23[];
};


#endif