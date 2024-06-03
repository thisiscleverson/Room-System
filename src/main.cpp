#include <Arduino.h>

#include <Espalexa.h>
#include <Adafruit_NeoPixel.h>
#include <connectWifi/connectWifi.h>

#include <LightController.h>
#include <EffectsController.h>
#include <button.h> 

const int button = 19; // pino para o botão
int ledyellow = 9; //tirar no codigo final

#define pinStripLed 4 
#define lightPin 18
#define sensor 5


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(30, pinStripLed, NEO_GRB + NEO_KHZ800);

LightController light = LightController(lightPin);
EffectsController effects = EffectsController(pixels);


void led(uint8_t brightness, uint32_t rgb);
void read_button(int button);

// Change this!!
const char* ssid     = "Cleverson";
const char* password = "tesla32020";

Espalexa espalexa;
EspalexaDevice* device3; 

int beforeSensor;

void setup(){

  //pixels.begin();  
  Serial.begin(115200);

  
  bool wifiConnected = connectWifi(ssid, password);
  
  if(wifiConnected){
    // Define your devices here. 
    espalexa.addDevice("fita de led", led, 255); 
    espalexa.begin();
    
  } else{
    while (true){
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }


  pinMode(button, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  pinMode(lightPin, OUTPUT);

  pinMode(ledyellow, OUTPUT); // <-- tirar no codigo final//

  beforeSensor = digitalRead(sensor);
}
 
void loop(){
  read_button(button);

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