# Room System - Sistema de automação do meu quarto

### O que faz?

 - **liga e desliga a luz**
 - **controla o ar condicionado**
 - **controla a fita de led**
 - **pode ser controlado pela Alexa**

### configuração do sistema
```cpp
#define buttonPin        19
#define pinStripLed      4 
#define lightPin         18
#define buttonNextEffect 5
#define IRsensorPin      6


const char* ssid     = "SSID";
const char* password = "SENHA";
```

### Como definir os dispositivos na alexa:

```cpp
espalexa.addDevice("Light", lightState); 
espalexa.addDevice("fita de led", stripLed, 255); 
espalexa.addDevice("ar condicionado", activateAirConditioning); 
espalexa.addDevice("temperatura 18", activateTemp18);
espalexa.addDevice("temperatura 23", activateTemp23);
```
