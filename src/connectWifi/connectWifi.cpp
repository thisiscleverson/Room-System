#include <Arduino.h>

#include "connectWifi.h"

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif


boolean connectWifi(const char* ssid, const char* password){
   boolean state = true;

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);

   Serial.println("\nConnecting to WiFi");

   // Wait for connection
   Serial.print("Connecting...");

   while (WiFi.status() != WL_CONNECTED) {
      static int i = 0;
      
      delay(500);
      Serial.print(".");
      if (i > 20){
         state = false; 
         break;
      }
      i++;
   }

   Serial.println("");

   if (state){
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
   }
   else {
      Serial.println("Connection failed.");
   }

   return state;
}