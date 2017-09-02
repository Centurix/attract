#include "atm_bell.h"

Atm_bell & Atm_bell::begin(int attached_pin) {
  const static state_t state_table[] PROGMEM = {
    /*|- STATES --|- ACTIONS ------------------------|- EVENTS --------------------|
    /*                  ON_ENTER, ON_LOOP,    ON_EXIT, EVT_TIMER, EVT_HISCORE, ELSE */
    /* IDLE */                -1,      -1,         -1,        -1,   PING_PING,   -1,
    /* PING_PING */  ENT_PING_ON,      -1, EX_PING_ON,      IDLE,          -1,   -1
  };
  Machine::begin(state_table, ELSE);
  pin = attached_pin;
  timer.set(250);
  pinMode(pin, OUTPUT);
  return *this;
}

int Atm_bell::event(int id) {
  switch(id) {
    case EVT_TIMER:
      return timer.expired(this);
  }
  return 0;
}

void Atm_bell::action(int id) {
  switch(id) {
    case ENT_PING_ON:
      digitalWrite(pin, HIGH);
      delay(10);
      digitalWrite(pin, LOW);
      delay(100);
      return;
    case EX_PING_ON:
      digitalWrite(pin, HIGH);
      delay(10);
      digitalWrite(pin, LOW);
      delay(100);
      return;
  }
}

