#pragma once

#include <Automaton.h>

class Atm_bell : public Machine {
  public:
    enum {IDLE, PING_PING}; // STATES
    enum {EVT_TIMER, EVT_HISCORE, ELSE}; // EVENTS
    enum {ENT_PING_ON, EX_PING_ON}; // ACTIONS

    short pin;
    atm_timer_millis timer;

    Atm_bell(void) : Machine(){};
    Atm_bell & begin(int attached_pin);

    int event(int id);
    void action(int id);
};
