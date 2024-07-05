#ifndef DELAYCHECKER_H
#define DELAYCHECKER_H


class DelayChecker {
   public:
      DelayChecker() : lastMillis(0) {}
      
      
      /**
      * @brief Verifica se o tempo de espera especificado se passou.
      * 
      * Esta função verifica se o intervalo de tempo especificado (em milissegundos) se passou desde a última vez que foi verificado. 
      * Se o tempo de espera tiver passado, atualiza o último registro de tempo e retorna `true`. Caso contrário, retorna `false`.
      * 
      * @param wait O intervalo de tempo a ser aguardado, em milissegundos.
      * 
      * @return `true` se o intervalo de tempo especificado se passou desde a última verificação, `false` caso contrário.
      * 
      * Exemplo de uso:
      * 
      * @code
      * DelayChecker delayChecker;
      * unsigned long interval = 1000; // 1 segundo
      * 
      * void loop() {
      *     if (delayChecker.checkDelay(interval)) {
      *         // Código a ser executado a cada intervalo de 1 segundo
      *     }
      * }
      * @endcode
      */
      bool checkDelay(unsigned long wait);

   private:
      unsigned long lastMillis;
};


#endif