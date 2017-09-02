#include "atm_panel.h"
#include "panel_charset.h"
#include "panel_images.h"

#define BRIGHTNESS 64

Atm_panel & Atm_panel::begin() {
  const static state_t state_table[] PROGMEM = {
    /*|- STATES -----------|- ACTIONS ------------------------------------|- EVENTS ---------------------------------------------------------------------------------------------------------------------------------|
    /*                                ON_ENTER,          ON_LOOP, ON_EXIT,          EVT_TIMER,        EVT_ON, EVT_OFF, EVT_RAINBOW_ON, EVT_RAINBOW_TIMER, EVT_HISCORE_ON, EVT_HISCORE_TIMER, EVT_MAME, EVT_GAME, ELSE */
    /* IDLE */              ENT_MAME_FLASH_OFF,               -1,      -1,                 -1, MAME_FLASH_ON,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* MAME_FLASH_ON */      ENT_MAME_FLASH_ON,               -1,      -1,     MAME_FLASH_OFF,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* MAME_FLASH_OFF */    ENT_MAME_FLASH_OFF,               -1,      -1,      GAME_FLASH_ON,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* GAME_FLASH_ON */      ENT_GAME_FLASH_ON,               -1,      -1,     GAME_FLASH_OFF,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* GAME_FLASH_OFF */    ENT_GAME_FLASH_OFF,               -1,      -1,      MAME_FLASH_ON,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* RAINBOW */               ENT_RAINBOW_ON,               -1,      -1,                 -1,            -1,      -1,        RAINBOW,           RAINBOW,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* HISCORE */               ENT_HISCORE_ON,               -1,      -1,                 -1,            -1,      -1,        RAINBOW,                -1,        HISCORE,           HISCORE,  MAME_ON,  GAME_ON,   -1,
    /* MAME_ON */            ENT_MAME_FLASH_ON,               -1,      -1,                 -1,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1,
    /* GAME_ON */            ENT_GAME_FLASH_ON,               -1,      -1,                 -1,            -1,      -1,        RAINBOW,                -1,        HISCORE,                -1,  MAME_ON,  GAME_ON,   -1
  };
  Machine::begin(state_table, ELSE);
  width = 32;
  height = 8;

  safe_leds = new CRGB[width * height + 1];
  
  timer.set(500);
  rainbow_timer.set(45);
  hiscore_timer.set(1000);

  hiscore.reserve(20);

  // Specific Panel information
  FastLED.addLeds<WS2812B, PANEL_PIN, GRB>(safe_leds, width * height).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(64);
  
  return *this;
}

int Atm_panel::event(int id) {
  switch(id) {
    case EVT_TIMER:
      return timer.expired(this);
    case EVT_RAINBOW_TIMER:
      return rainbow_timer.expired(this);
    case EVT_HISCORE_TIMER:
      return hiscore_timer.expired(this);
  }
  return 0;
}

void Atm_panel::action(int id) {
  uint32_t ms;
  int32_t yHueDelta32, xHueDelta32;
  switch(id) {
    case ENT_MAME_FLASH_ON:
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          safe_leds[ XY(x, y) ] = img_mame[y][x];
        }
      }
      FastLED.show();
      return;
    case ENT_MAME_FLASH_OFF:
      empty();
      FastLED.show();
      return;
    case ENT_GAME_FLASH_ON:
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          safe_leds[ XY(x, y) ] = img_game[y][x];
        }
      }
      FastLED.show();
      return;
    case ENT_GAME_FLASH_OFF:
      empty();
      FastLED.show();
      return;
    case ENT_RAINBOW_ON:
      ms = millis();
      yHueDelta32 = ((int32_t)cos16( ms * (27/1) ) * (350 / width));
      xHueDelta32 = ((int32_t)cos16( ms * (39/1) ) * (310 / height));
      drawOneFrame( ms / 65536, yHueDelta32 / 32768, xHueDelta32 / 32768);
      if( ms < 5000 ) {
        FastLED.setBrightness( scale8( BRIGHTNESS, (ms * 256) / 5000));
      } else {
        FastLED.setBrightness(BRIGHTNESS);
      }
      FastLED.show();
      return;
    case ENT_HISCORE_ON:
      // Show the score send through the serial port. Need a charset and a way to display it right here!
      empty();
      addText(hiscore, 0, 0, CRGB::Blue);
      FastLED.show();
      return;
  }
}

uint16_t Atm_panel::XY( uint8_t x, uint8_t y) {
  uint16_t offset = ((width - 1)- x) * height;

  if (x & 0x01) {
    return offset + height - 1 - y;
  } else {
    return offset + y;
  }

  return offset;
}

void Atm_panel::setGameImage(uint8_t image_data[768]) {
  int row = 0;
  int col = 0;
  for (int index = 0; index < 768; index += 3) {
    long red = image_data[index];
    long green = image_data[index + 1];
    long blue = image_data[index + 2];
    long value = red << 16 | green << 8 | blue;
    img_game[row][col++] = value;
    if (col >= 32) {
      col = 0;
      row++;
      if (row >= 8) {
        row = 0;
      }
    }
  }
}

void Atm_panel::drawOneFrame( byte startHue8, int8_t yHueDelta8, int8_t xHueDelta8) {
  byte lineStartHue = startHue8;
  for( byte y = 0; y < height; y++) {
    lineStartHue += yHueDelta8;
    byte pixelHue = lineStartHue;      
    for( byte x = 0; x < width; x++) {
      pixelHue += xHueDelta8;
      safe_leds[ XY(x, y)]  = CHSV( pixelHue, 255, 255);
    }
  }
}

void Atm_panel::empty() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      safe_leds[ XY(x, y) ] = CRGB::Black;
    }
  }  
}

void Atm_panel::addText(String text, int8_t x, int8_t y, CRGB text_color) {
  int cursor = x;
  for(int index = 0; index < text.length(); index++) {
    int char_value = (int)text[index] - 32;
    for(int line = 0; line < 8; line++) {
      for(int pixel = 0; pixel < 8; pixel++) {
        uint8_t byte_line = pgm_read_byte(charset + (char_value * 8) + line);
        if ((byte_line & round(pow(2, (7 - pixel)))) > 0) {
          safe_leds[ XY(cursor + pixel, line) ] = text_color;
        }
      }
    }
    // Move the cursor position
    cursor += pgm_read_byte(char_widths + char_value);
  }
}

