#include <Arduino.h>
#include <Espalexa.h>
#include <Adafruit_NeoPixel.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


// modulos
#include <connectWifi.h>
#include <LightController.h>
#include <EffectsController.h>
#include <ButtonHandler.h>
#include <IRController.h>
#include <DeviceFunctions.h>
#include <ReadButtonNextEffect.h>


#define buttonPin        19
#define pinStripLed      4 
#define lightPin         18
#define buttonNextEffect 5
#define IRsensorPin      6


const char* ssid     = "SSID";
const char* password = "SENHA";


Adafruit_NeoPixel pixels(30, pinStripLed, NEO_GRB + NEO_KHZ800);
IRsend IRsensor(IRsensorPin); // pertence a biblioteca IRsend e o objeto IRsensor será injetada dentro do IRController
Espalexa espalexa;


IRController      IR(IRsensor);
LightController   light(lightPin);
EffectsController effects(pixels);
ButtonHandler     buttonHandler(buttonPin, light);



void setup(){

  pixels.begin();
  IRsensor.begin(); 
  buttonHandler.begin();
  light.begin();
  Serial.begin(115200);

  
  bool wifiConnected = connectWifi(ssid, password);
  if(wifiConnected){
   
    espalexa.addDevice("Light", lightState); 
    espalexa.addDevice("fita de led", stripLed, 255); 
    espalexa.addDevice("ar condicionado", activateAirConditioning); 
    espalexa.addDevice("temperatura 18", activateTemp18);
    espalexa.addDevice("temperatura 23", activateTemp23);

    espalexa.begin();
    
  } else{
    Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
  }


  pinMode(buttonNextEffect, INPUT_PULLUP);
}
 
void loop(){
  buttonHandler.readButton();

  readButtonNextEffet(buttonNextEffect, effects);

  espalexa.loop();
  effects.loop();

}