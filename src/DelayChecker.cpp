#include <Arduino.h>
#include <DelayChecker.h>

bool DelayChecker::checkDelay(unsigned long wait) {
   unsigned long currentMillis = millis();

   if (currentMillis - lastMillis >= wait) {
         lastMillis = currentMillis;
         return true;
   }
   return false;
}