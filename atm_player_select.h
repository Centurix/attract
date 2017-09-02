#pragma once

#include <Automaton.h>

class Atm_player_select : public Machine {
  public:
    enum {NO_COINS_START, NO_COINS, ONE_COIN_START, ONE_COIN, MORE_COINS_START, MORE_COINS, ATTRACT_1_START, ATTRACT_1, ATTRACT_2_START, ATTRACT_2, ATTRACT_3_START, ATTRACT_3}; // STATES
    enum {EVT_ATTRACT_STEP, EVT_ATTRACT_1_CNT, EVT_ATTRACT_2_CNT, EVT_ATTRACT_3_CNT, EVT_NEXT, EVT_START, EVT_ATTRACT, EVT_ONE_COIN, EVT_MORE_COINS, EVT_COINS_EMPTY, EVT_COINS_CNT, ELSE}; // EVENTS 
    enum {ENT_ATTRACT_1_START, ENT_ATTRACT_1, ENT_ATTRACT_2_START, ENT_ATTRACT_2, ENT_ATTRACT_3_START, ENT_ATTRACT_3, ENT_NO_COINS_START, ENT_ONE_COIN_START, ENT_ONE_COIN, ENT_MORE_COINS_START, ENT_MORE_COINS}; // ACTIONS

    static const uint8_t ATTRACT_1_SIZE = 32;
    static const uint8_t ATTRACT_2_SIZE = 32;
    static const uint8_t ATTRACT_3_SIZE = 32;
    static const uint8_t COINS_SIZE = 32;
    
    uint8_t attract_1[ATTRACT_1_SIZE] = {0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255};
    uint8_t attract_2[ATTRACT_2_SIZE] = {0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 10, 12, 15, 18, 22, 26, 31, 37, 44, 54, 63, 76, 90, 108, 127, 153, 180, 217, 230, 255};
    uint8_t attract_3[ATTRACT_3_SIZE] = {255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0};
    uint8_t coins[COINS_SIZE] = {0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 255, 255, 255, 255};
    
    short player_1_pin;
    short player_2_pin;
    
    atm_timer_millis attract_step;
    
    atm_counter attract_1_counter;
    atm_counter attract_2_counter;
    atm_counter attract_3_counter;
    atm_counter coins_counter;
    
    Atm_player_select(void) : Machine(){};
    Atm_player_select & begin(int attached_player_1_pin, int attached_player_2_pin);

    int event(int id);
    void action(int id);
};

