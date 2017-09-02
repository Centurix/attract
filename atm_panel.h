#pragma once

#include <Automaton.h>
#include <FastLED.h>

#include "attract.h"

class Atm_panel : public Machine {
  public:
    enum {IDLE, MAME_FLASH_ON, MAME_FLASH_OFF, GAME_FLASH_ON, GAME_FLASH_OFF, RAINBOW, HISCORE, MAME_ON, GAME_ON}; // STATES
    enum {EVT_TIMER, EVT_ON, EVT_OFF, EVT_RAINBOW_ON, EVT_RAINBOW_TIMER, EVT_HISCORE_ON, EVT_HISCORE_TIMER, EVT_MAME, EVT_GAME, ELSE}; // EVENTS
    enum {ENT_MAME_FLASH_ON, ENT_MAME_FLASH_OFF, ENT_GAME_FLASH_ON, ENT_GAME_FLASH_OFF, ENT_RAINBOW_ON, ENT_HISCORE_ON}; // ACTIONS

    atm_timer_millis timer;
    atm_timer_millis rainbow_timer;
    atm_timer_millis hiscore_timer;
    
    uint8_t width;
    uint8_t height;

    CRGB* safe_leds;

    String hiscore;

    Atm_panel(void) : Machine(){};
    Atm_panel & begin();

    int event(int id);
    void action(int id);
    uint16_t XY( uint8_t x, uint8_t y);
    void setGameImage(uint8_t image_data[]);
    void drawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8);
    void empty();
    void addText(String text, int8_t x, int8_t y, CRGB text_color);
};
