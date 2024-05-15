#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

extern bool before_button;
extern LightController light;

bool after_button;

unsigned long beforeMillis;
bool button_actived = false;


unsigned long lastDebounceTime = 0; //Variável que armazenará o tempo do último Debounce
unsigned long DebounceTime = 50;      //Tempo (em milissegundos)que é necessário manter o botão pressionado para ter a certeza de que ele foi pressionado de fato.


void read_button(int button); // Passa o pino do botão como parâmetro

void read_button(int button) {
  after_button = digitalRead(button);
  
  static unsigned long timeKeeper = 0, timeout = 2000; // 2 segundo
  unsigned long timing = millis() - timeKeeper;

  if (!before_button && !after_button) {
    if (timing >= timeout && !button_actived) {
      timeKeeper = millis(); // reseta o temporizador
      Serial.println("Ar ligado!");
      button_actived = true;
    }
  } else if (before_button && !after_button) {
    if ((millis() - lastDebounceTime) > DebounceTime){
      Serial.println("Luz!");
      bool stateLight = light.get_state_light(); 
      light.set_state_light(!stateLight);
    } 
  } else {
    timeKeeper = millis(); // reseta o temporizador
    lastDebounceTime = millis();
    button_actived = false;
  }

  before_button = digitalRead(button);
}

#endif