#ifndef DELAYCHECKER_H
#define DELAYCHECKER_H



class DelayChecker {
   public:
      DelayChecker() : lastMillis(0) {}

      bool checkDelay(unsigned long wait) {
         unsigned long currentMillis = millis();

         if (currentMillis - lastMillis >= wait) {
               lastMillis = currentMillis;
               return true;
         }
         return false;
      }

   private:
      unsigned long lastMillis;
};


#endif