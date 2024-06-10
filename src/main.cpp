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


#define buttonPin   19
#define pinStripLed 4 
#define lightPin    18
#define sensor      5
#define IRsensorPin 8


Adafruit_NeoPixel pixels(30, pinStripLed, NEO_GRB + NEO_KHZ800);
IRsend IRsensor(IRsensorPin);
Espalexa espalexa;


IRController      IR(IRsensor);
LightController   light(lightPin);
EffectsController effects(pixels);
ButtonHandler     buttonHandler(buttonPin, light);

const char* ssid     = "Cleverson";
const char* password = "tesla32020";

int beforeSensor;

void setup(){

  pixels.begin();
  IRsensor.begin(); 
  buttonHandler.begin();
  Serial.begin(115200);

  
  bool wifiConnected = connectWifi(ssid, password);
  if(wifiConnected){
    // Define your devices here. 
    espalexa.addDevice("Lampada", lightState, 0); 
    espalexa.addDevice("fita de led", stripLed, 255); 
    espalexa.addDevice("ar condicionado", activateAirConditioning); 
    espalexa.addDevice("temperatura 18", activateTemp18);
    espalexa.addDevice("temperatura 23", activateTemp23);

    espalexa.begin();
    
  } else{
    Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
  }


  pinMode(sensor, INPUT);
  beforeSensor = digitalRead(sensor);
}
 
void loop(){
  buttonHandler.readButton();

  if(digitalRead(sensor) == HIGH && beforeSensor == LOW){
    Serial.println("Sensor Touch!");
    effects.nextEffect();
  }

  beforeSensor = digitalRead(sensor);

  espalexa.loop();
  effects.loop();

}
