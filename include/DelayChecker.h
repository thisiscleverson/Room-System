#ifndef DELAYCHECKER_H
#define DELAYCHECKER_H


class DelayChecker {
   public:
      DelayChecker() : lastMillis(0) {}

      bool checkDelay(unsigned long wait);

   private:
      unsigned long lastMillis;
};


#endif