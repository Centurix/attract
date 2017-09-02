#include "atm_coin.h"

Atm_coin & Atm_coin::begin(int attached_pin, int blink_rate) {
  const static state_t state_table[] PROGMEM = {
    /*|- STATES --|- ACTIONS ---------------|- EVENTS ------------------------|
    /*            ON_ENTER, ON_LOOP, ON_EXIT, EVT_TIMER, EVT_ON, EVT_OFF, ELSE */
    /* IDLE */     ENT_OFF,      -1,      -1,        -1, LED_ON,      -1,   -1,
    /* LED_ON */    ENT_ON,      -1,      -1,   LED_OFF,     -1,    IDLE,   -1,
    /* LED_OFF */  ENT_OFF,      -1,      -1,    LED_ON,     -1,    IDLE,   -1,
  };
  Machine::begin(state_table, ELSE);
  pin = attached_pin;
  timer.set(blink_rate);
  pinMode(pin, OUTPUT);
  return *this;
}

int Atm_coin::event(int id) {
  switch(id) {
    case EVT_TIMER:
      return timer.expired(this);
  }
  return 0;
}

void Atm_coin::action(int id) {
  switch(id) {
    case ENT_ON:
      digitalWrite(pin, HIGH);
      return;
    case ENT_OFF:
      digitalWrite(pin, LOW);
      return;
  }
}

