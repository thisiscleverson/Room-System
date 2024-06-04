#include <Arduino.h>
#include <Espalexa.h>
#include <Adafruit_NeoPixel.h>


// modulos
#include <connectWifi.h>
#include <LightController.h>
#include <EffectsController.h>
#include <ButtonHandler.h>


#define buttonPin   19
#define pinStripLed 4 
#define lightPin    18
#define sensor      5


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(30, pinStripLed, NEO_GRB + NEO_KHZ800);
Espalexa espalexa;


LightController   light(lightPin);
EffectsController effects(pixels);
ButtonHandler     buttonHandler(buttonPin, light);


const char* ssid     = "Cleverson";
const char* password = "tesla32020";

int beforeSensor;


void led(uint8_t brightness, uint32_t rgb);


void setup(){

  pixels.begin();
  buttonHandler.begin();
  Serial.begin(115200);

  
  bool wifiConnected = connectWifi(ssid, password);
  if(wifiConnected){
    // Define your devices here. 
    espalexa.addDevice("fita de led", led, 255); 
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


void led(uint8_t brightness, uint32_t rgb){
  int red,green,blue;
  
  red   = ((rgb >> 16) & 0xFF);
  green = ((rgb >>  8) & 0xFF);
  blue  = ((rgb & 0xFF));

  pixels.setBrightness(brightness);
  effects.setColor(pixels.Color(red,green,blue));

}