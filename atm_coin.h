#pragma once

#include <Automaton.h>

class Atm_coin : public Machine {
  public:
    enum {IDLE, LED_ON, LED_OFF}; // STATES
    enum {EVT_TIMER, EVT_ON, EVT_OFF, ELSE}; // EVENTS
    enum {ENT_ON, ENT_OFF}; // ACTIONS

    short pin;
    atm_timer_millis timer;

    Atm_coin(void) : Machine(){};
    Atm_coin & begin(int attached_pin, int blink_rate);

    int event(int id);
    void action(int id);
};

