#pragma once

#include <Automaton.h>

/**
 * Fill in this state machine for the play buttons, then make a state machine for the LED matrix
 */
class Atm_play_buttons : public Machine {
  public:
    enum {IDLE, ATTRACT_MODE_1_START, ATTRACT_MODE_1, ATTRACT_MODE_2_START, ATTRACT_MODE_2, ATTRACT_MODE_3_START, ATTRACT_MODE_3, ATTRACT_MODE_4_START, ATTRACT_MODE_4, ATTRACT_MODE_5_START, ATTRACT_MODE_5, GAME_PLAY_START, GAME_PLAY}; // STATES
    enum {EVT_ATTRACT_STEP, EVT_ATTRACT_1_CNT, EVT_ATTRACT_2_CNT, EVT_ATTRACT_3_CNT, EVT_ATTRACT_4_CNT, EVT_ATTRACT_5_CNT, EVT_PLAYER_SELECT, EVT_GAME_START, EVT_GAME_OVER, EVT_ATTRACT, EVT_NEXT, ELSE}; // EVENTS 
    enum {ENT_ATTRACT_1_START, ENT_ATTRACT_1, ENT_ATTRACT_2_START, ENT_ATTRACT_2, ENT_ATTRACT_3_START, ENT_ATTRACT_3, ENT_ATTRACT_4_START, ENT_ATTRACT_4, ENT_ATTRACT_5_START, ENT_ATTRACT_5, ENT_IDLE, ENT_GAME_PLAY_START, ENT_GAME_PLAY}; // ACTIONS

    static const uint8_t ATTRACT_1_SIZE = 32;
    static const uint8_t ATTRACT_2_SIZE = 32;
    static const uint8_t ATTRACT_3_SIZE = 32;
    static const uint8_t ATTRACT_4_SIZE = 32;
    static const uint8_t ATTRACT_5_SIZE = 32;
    
    uint8_t attract_1[ATTRACT_1_SIZE] = {0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255};
    uint8_t attract_2[ATTRACT_2_SIZE] = {255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0};
    uint8_t attract_3[ATTRACT_3_SIZE] = {0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255};
    uint8_t attract_4[ATTRACT_4_SIZE] = {255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0};
    uint8_t attract_5[ATTRACT_5_SIZE] = {0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255};
    
    short red_pin;
    short green_pin;
    short blue_pin;
    
    atm_timer_millis attract_step;
    
    atm_counter attract_1_counter;
    atm_counter attract_2_counter;
    atm_counter attract_3_counter;
    atm_counter attract_4_counter;
    atm_counter attract_5_counter;
    
    atm_counter attract_counter;
    
    Atm_play_buttons(void) : Machine(){};
    Atm_play_buttons & begin(int attached_red_pin, int attached_green_pin, int attached_blue_pin);

    int event(int id);
    void action(int id);
};

