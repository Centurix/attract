#include "atm_player_select.h"

Atm_player_select & Atm_player_select::begin(int attached_player_1_pin, int attached_player_2_pin) {
  const static state_t state_table[] PROGMEM = {
    /*|- STATES --------------|- ACTIONS ------------------------------------|- EVENTS -------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    /*                                      ON_ENTER,     ON_LOOP, ON_EXIT,   EVT_ATTRACT_STEP, EVT_ATTRACT_1_CNT, EVT_ATTRACT_2_CNT, EVT_ATTRACT_3_CNT,      EVT_NEXT, EVT_START,     EVT_ATTRACT,  EVT_ONE_COIN,   EVT_MORE_COINS, EVT_COINS_EMPTY,    EVT_COINS_CNT, ELSE */
    /* NO_COINS_START */          ENT_NO_COINS_START,   ATM_SLEEP,      -1,                 -1,                -1,                -1,                -1,      NO_COINS,       -1,              -1, ONE_COIN_START, MORE_COINS_START,  NO_COINS_START,               -1,   -1,
    /* NO_COINS */                                -1,   ATM_SLEEP,      -1,                 -1,                -1,                -1,                -1,            -1,       -1, ATTRACT_1_START, ONE_COIN_START, MORE_COINS_START,  NO_COINS_START,               -1,   -1,
    /* ONE_COIN_START */          ENT_ONE_COIN_START,          -1,      -1,                 -1,                -1,                -1,                -1,      ONE_COIN,       -1,              -1,             -1, MORE_COINS_START,  NO_COINS_START,               -1,   -1,
    /* ONE_COIN */                      ENT_ONE_COIN,          -1,      -1,           ONE_COIN,                -1,                -1,                -1,            -1,       -1, ATTRACT_1_START,             -1, MORE_COINS_START,  NO_COINS_START,   ONE_COIN_START,   -1,
    /* MORE_COINS_START */      ENT_MORE_COINS_START,          -1,      -1,                 -1,                -1,                -1,                -1,    MORE_COINS,       -1,              -1,             -1,               -1,  NO_COINS_START,               -1,   -1,
    /* MORE_COINS */                  ENT_MORE_COINS,          -1,      -1,         MORE_COINS,                -1,                -1,                -1,            -1,       -1, ATTRACT_1_START, ONE_COIN_START,               -1,  NO_COINS_START, MORE_COINS_START,   -1,
    /* ATTRACT_1_START */        ENT_ATTRACT_1_START,          -1,      -1,                 -1,                -1,                -1,                -1,     ATTRACT_1,       -1,              -1,             -1,               -1,  NO_COINS_START,               -1,   -1,
    /* ATTRACT_1 */                    ENT_ATTRACT_1,          -1,      -1,          ATTRACT_1,   ATTRACT_2_START,                -1,                -1,            -1,       -1,              -1, ONE_COIN_START,               -1,  NO_COINS_START,               -1,   -1,
    /* ATTRACT_2_START */        ENT_ATTRACT_2_START,          -1,      -1,                 -1,                -1,                -1,                -1,     ATTRACT_2,       -1,              -1,             -1,               -1,  NO_COINS_START,               -1,   -1,
    /* ATTRACT_2 */                    ENT_ATTRACT_2,          -1,      -1,          ATTRACT_2,                -1,   ATTRACT_3_START,                -1,            -1,       -1,              -1, ONE_COIN_START,               -1,  NO_COINS_START,               -1,   -1,
    /* ATTRACT_3_START */        ENT_ATTRACT_3_START,          -1,      -1,                 -1,                -1,                -1,                -1,     ATTRACT_3,       -1,              -1,             -1,               -1,  NO_COINS_START,               -1,   -1,
    /* ATTRACT_3 */                    ENT_ATTRACT_3,          -1,      -1,          ATTRACT_3,                -1,                -1,   ATTRACT_1_START,            -1,       -1,              -1, ONE_COIN_START,               -1,  NO_COINS_START,               -1,   -1,
  };
  Machine::begin(state_table, ELSE);
  
  player_1_pin = attached_player_1_pin;
  player_2_pin = attached_player_2_pin;
  
  pinMode(player_1_pin, OUTPUT);
  pinMode(player_2_pin, OUTPUT);
  
  attract_step.set(50);
  
  attract_1_counter.set( ATTRACT_1_SIZE );
  attract_2_counter.set( ATTRACT_2_SIZE );
  attract_3_counter.set( ATTRACT_3_SIZE );
  coins_counter.set( COINS_SIZE );
  
  return *this;
}

int Atm_player_select::event(int id) {
  switch(id) {
    case EVT_ATTRACT_STEP:
      return attract_step.expired(this);
    case EVT_ATTRACT_1_CNT:
      return attract_1_counter.expired();
    case EVT_ATTRACT_2_CNT:
      return attract_2_counter.expired();
    case EVT_ATTRACT_3_CNT:
      return attract_3_counter.expired();
    case EVT_COINS_CNT:
      return coins_counter.expired();
    case EVT_NEXT:
      return true;
  }
  return 0;
}

void Atm_player_select::action(int id) {
  switch(id) {
    case ENT_NO_COINS_START:
      analogWrite(player_1_pin, 0);
      analogWrite(player_2_pin, 0);
      return;
    case ENT_ONE_COIN_START:
      analogWrite(player_1_pin, 0);
      analogWrite(player_2_pin, 0);
      coins_counter.set( COINS_SIZE );
      return;
    case ENT_ONE_COIN:
      analogWrite(player_1_pin, coins[coins_counter.value - 1]);
      coins_counter.decrement();
      return;
    case ENT_MORE_COINS_START:
      analogWrite(player_1_pin, 0);
      analogWrite(player_2_pin, 0);
      coins_counter.set( COINS_SIZE );
      return;
    case ENT_MORE_COINS:
      analogWrite(player_1_pin, coins[coins_counter.value - 1]);
      analogWrite(player_2_pin, coins[coins_counter.value - 1]);
      coins_counter.decrement();
      return;
    case ENT_ATTRACT_1_START:
      attract_1_counter.set( ATTRACT_1_SIZE);
      return;
    case ENT_ATTRACT_1:
      analogWrite(player_1_pin, attract_1[attract_1_counter.value - 1]);
      analogWrite(player_2_pin, attract_1[attract_1_counter.value - 1]);
      attract_1_counter.decrement();
      return;
    case ENT_ATTRACT_2_START:
      attract_2_counter.set( ATTRACT_2_SIZE);
      return;
    case ENT_ATTRACT_2:
      analogWrite(player_1_pin, attract_2[attract_2_counter.value - 1]);
      analogWrite(player_2_pin, attract_2[attract_2_counter.value - 1]);
      attract_2_counter.decrement();
      return;
    case ENT_ATTRACT_3_START:
      attract_3_counter.set( ATTRACT_3_SIZE);
      return;
    case ENT_ATTRACT_3:
      analogWrite(player_1_pin, attract_1[attract_3_counter.value - 1]);
      analogWrite(player_2_pin, attract_3[attract_3_counter.value - 1]);
      attract_3_counter.decrement();
      return;
  }
}

