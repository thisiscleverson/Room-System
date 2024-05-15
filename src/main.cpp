#include <Arduino.h>

#include <Espalexa.h>
#include <Adafruit_NeoPixel.h>
#include <connectWifi/connectWifi.h>

#include <light.h>
#include <button.h> 

const int button = 19; // pino para o botão

#define PIN 4 

#define lightPin 18

LightController light = LightController(lightPin);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void led(uint8_t brightness, uint32_t rgb);
void read_button(int button);

// Change this!!
const char* ssid     = "Cleverson";
const char* password = "tesla32020";

bool before_button;

Espalexa espalexa;
EspalexaDevice* device3; 

void setup(){

  //pixels.begin();  
  Serial.begin(115200);

  /*
  bool wifiConnected = connectWifi(ssid, password);
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("Light 1", firstLightChanged); 
    espalexa.addDevice("Light 2", secondLightChanged, 255); 
    
    device3 = new EspalexaDevice("Light 3", thirdLightChanged); 
    espalexa.addDevice(device3); 
    device3->setValue(128); 

    espalexa.addDevice("led3", led); 


    espalexa.begin();
    
  } else{
    while (true){
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
  */

  Serial.print("Light state: ");
  Serial.print(light.get_state_light());
  Serial.println();

  pinMode(button, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);

  before_button = digitalRead(button);

}
 
void loop()
{
  //espalexa.loop();
  read_button(button);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
    Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("ON, brightness ");
      Serial.println(brightness);
    }
    else  {
      Serial.println("OFF");
    }
}

void secondLightChanged(uint8_t brightness) {
  Serial.println("Device 2 changed to ");
  Serial.println(brightness);
}

void thirdLightChanged(uint8_t brightness) {
  //do what you need to do here
}

void led(uint8_t brightness, uint32_t rgb){
  int red,green,blue;
  
  red   = ((rgb >> 16) & 0xFF);
  green = ((rgb >>  8) & 0xFF);
  blue  = ((rgb & 0xFF));

  pixels.setBrightness(brightness);
  pixels.show();
  for(int  i=0; i < pixels.numPixels(); i++){
      pixels.setPixelColor(i,pixels.Color(red,green,blue));
      pixels.show();
  }
}