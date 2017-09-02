#include "atm_play_buttons.h"

Atm_play_buttons & Atm_play_buttons::begin(int attached_red_pin, int attached_green_pin, int attached_blue_pin) {
  const static state_t state_table[] PROGMEM = {
    /*|- STATES --------------|- ACTIONS -------------------------------------|- EVENTS -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    /*                                           ON_ENTER,   ON_LOOP, ON_EXIT, EVT_ATTRACT_STEP,    EVT_ATTRACT_1_CNT,    EVT_ATTRACT_2_CNT,    EVT_ATTRACT_3_CNT,    EVT_ATTRACT_4_CNT,    EVT_ATTRACT_5_CNT, EVT_PLAYER_SELECT,  EVT_GAME_START,        EVT_GAME_OVER,          EVT_ATTRACT,       EVT_NEXT, ELSE */
    /* IDLE */                                   ENT_IDLE, ATM_SLEEP,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* ATTRACT_MODE_1_START */        ENT_ATTRACT_1_START,        -1,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1,   -1,
    /* ATTRACT_MODE_1 */                    ENT_ATTRACT_1,        -1,      -1,   ATTRACT_MODE_1, ATTRACT_MODE_2_START,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* ATTRACT_MODE_2_START */        ENT_ATTRACT_2_START,        -1,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START, ATTRACT_MODE_2,   -1,
    /* ATTRACT_MODE_2 */                    ENT_ATTRACT_2,        -1,      -1,   ATTRACT_MODE_2,                   -1, ATTRACT_MODE_3_START,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* ATTRACT_MODE_3_START */        ENT_ATTRACT_3_START,        -1,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START, ATTRACT_MODE_3,   -1,
    /* ATTRACT_MODE_3 */                    ENT_ATTRACT_3,        -1,      -1,   ATTRACT_MODE_3,                   -1,                   -1, ATTRACT_MODE_4_START,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* ATTRACT_MODE_4_START */        ENT_ATTRACT_4_START,        -1,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START, ATTRACT_MODE_4,   -1,
    /* ATTRACT_MODE_4 */                    ENT_ATTRACT_4,        -1,      -1,   ATTRACT_MODE_4,                   -1,                   -1,                   -1, ATTRACT_MODE_5_START,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* ATTRACT_MODE_5_START */        ENT_ATTRACT_5_START,        -1,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START, ATTRACT_MODE_5,   -1,
    /* ATTRACT_MODE_5 */                    ENT_ATTRACT_5,        -1,      -1,   ATTRACT_MODE_5,                   -1,                   -1,                   -1,                   -1, ATTRACT_MODE_1_START,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1,
    /* GAME_PLAY_START */             ENT_GAME_PLAY_START, ATM_SLEEP,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,      GAME_PLAY,   -1,
    /* GAME_PLAY */                             ATM_SLEEP, ATM_SLEEP,      -1,               -1,                   -1,                   -1,                   -1,                   -1,                   -1,              IDLE, GAME_PLAY_START, ATTRACT_MODE_1_START, ATTRACT_MODE_1_START,             -1,   -1
  };
  Machine::begin(state_table, ELSE);
  
  red_pin = attached_red_pin;
  green_pin = attached_green_pin;
  blue_pin = attached_blue_pin;
  
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  
  attract_step.set(50);
  
  attract_1_counter.set( ATTRACT_1_SIZE );
  attract_2_counter.set( ATTRACT_2_SIZE );
  attract_3_counter.set( ATTRACT_3_SIZE );
  attract_4_counter.set( ATTRACT_4_SIZE );
  attract_5_counter.set( ATTRACT_5_SIZE );

  return *this;
}

int Atm_play_buttons::event(int id) {
  switch(id) {
    case EVT_ATTRACT_STEP:
      return attract_step.expired(this);
    case EVT_ATTRACT_1_CNT:
      return attract_1_counter.expired();
    case EVT_ATTRACT_2_CNT:
      return attract_2_counter.expired();
    case EVT_ATTRACT_3_CNT:
      return attract_3_counter.expired();
    case EVT_ATTRACT_4_CNT:
      return attract_4_counter.expired();
    case EVT_ATTRACT_5_CNT:
      return attract_5_counter.expired();
    case EVT_NEXT:
      return true;
  }
  return 0;
}

void Atm_play_buttons::action(int id) {
  switch(id) {
    case ENT_ATTRACT_1_START:
      attract_1_counter.set( ATTRACT_1_SIZE);
      return;
    case ENT_ATTRACT_1:
      analogWrite(red_pin, attract_1[attract_1_counter.value - 1]);
      analogWrite(green_pin, attract_1[attract_1_counter.value - 1]);
      analogWrite(blue_pin, attract_1[attract_1_counter.value - 1]);
      attract_1_counter.decrement();
      return;
    case ENT_ATTRACT_2_START:
      attract_2_counter.set( ATTRACT_2_SIZE);
      return;
    case ENT_ATTRACT_2:
      analogWrite(red_pin, attract_2[attract_2_counter.value - 1]);
      analogWrite(green_pin, attract_2[attract_2_counter.value - 1]);
      analogWrite(blue_pin, attract_2[attract_2_counter.value - 1]);
      attract_2_counter.decrement();
      return;
    case ENT_ATTRACT_3_START:
      attract_3_counter.set( ATTRACT_3_SIZE);
      return;
    case ENT_ATTRACT_3:
      analogWrite(red_pin, attract_3[attract_3_counter.value - 1]);
      analogWrite(green_pin, attract_3[attract_3_counter.value - 1]);
      analogWrite(blue_pin, attract_3[attract_3_counter.value - 1]);
      attract_3_counter.decrement();
      return;
    case ENT_ATTRACT_4_START:
      attract_4_counter.set( ATTRACT_4_SIZE);
      return;
    case ENT_ATTRACT_4:
      analogWrite(red_pin, attract_4[attract_4_counter.value - 1]);
      analogWrite(green_pin, attract_4[attract_4_counter.value - 1]);
      analogWrite(blue_pin, attract_4[attract_4_counter.value - 1]);
      attract_4_counter.decrement();
      return;
    case ENT_ATTRACT_5_START:
      attract_5_counter.set( ATTRACT_5_SIZE);
      return;
    case ENT_ATTRACT_5:
      analogWrite(red_pin, attract_5[attract_5_counter.value - 1]);
      analogWrite(green_pin, attract_5[attract_5_counter.value - 1]);
      analogWrite(blue_pin, attract_5[attract_5_counter.value - 1]);
      attract_5_counter.decrement();
      return;
    case ENT_GAME_PLAY_START:
      analogWrite(red_pin, 255);
      analogWrite(green_pin, 255);
      analogWrite(blue_pin, 255);
      return;
    case ENT_IDLE:
      analogWrite(red_pin, 0);
      analogWrite(green_pin, 0);
      analogWrite(blue_pin, 0);
      return;    
  }
}

