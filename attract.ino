#include "attract.h"
#include "atm_coin.h"
#include "atm_player_select.h"
#include "atm_play_buttons.h"
#include "atm_bell.h"
#include "atm_panel.h"

//#define DEBUG 1

// Need to convert the classes to the following state tables

//Events          Coin buttons  Player buttons  Game buttons  Panel         Bell
//Startup         Attract mode  Attract mode    Attract mode  MAME gfx      Idle
//Game select     Attract mode  Idle            Attract mode  Game gfx      Idle
//One coin        n/c           One player      n/c           n/c           n/c
//More coins      n/c           Two players     n/c           n/c           n/c
//No coins        n/c           Idle            n/c           n/c           n/c
//Game start      n/c           n/c             Game play     n/c           n/c
//Hiscore         n/c           n/c             n/c           Show score    Ping
//Update score    n/c           n/c             n/c           Show score    n/c
//Game over       n/c           n/c             n/c           Game gfx      n/c
//          
//Ping over       n/c           n/c             n/c           n/c           Idle

Atm_coin coins;
Atm_player_select player_selects;
Atm_play_buttons play_buttons;
Atm_panel panel;
Atm_bell bell;

String serialInput = "";
uint8_t serialData[768];
int currentByte;
boolean stringComplete = false;
int serialBufferSize = 32;
long serialTimeout = 2000;
long lastSerial = 0;

void setup() {
  Serial.begin(9600);
  serialInput.reserve(40);
  coins.begin(COIN_PIN, 500);
  player_selects.begin(PLAYER_1_PIN, PLAYER_2_PIN);
  play_buttons.begin(RED_PIN, GREEN_PIN, BLUE_PIN);
  panel.begin();
  bell.begin(BELL_PIN);

  coins.trigger(coins.EVT_ON);
  player_selects.trigger(player_selects.EVT_ATTRACT);
  play_buttons.trigger(play_buttons.EVT_ATTRACT);
  panel.trigger(panel.EVT_MAME);
  bell.trigger(bell.EVT_HISCORE);
}

void loop() {
  coins.cycle();
  player_selects.cycle();
  play_buttons.cycle();
  panel.cycle();
  bell.cycle();
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      #ifdef DEBUG
      Serial.println(serialInput);
      #endif
      if (serialInput == "c_on") {
        #ifdef DEBUG
        Serial.println("Turning coins on");
        #endif
        coins.trigger(coins.EVT_ON);
      }
      if (serialInput == "c_off") {
        #ifdef DEBUG
        Serial.println("Turning coins off");
        #endif
        coins.trigger(coins.EVT_OFF);
      }
      if (serialInput == "p_attract") {
        #ifdef DEBUG
        Serial.println("Turning attract mode on");
        #endif
        player_selects.trigger(player_selects.EVT_ATTRACT);
      }
      if (serialInput == "p_nocoins") {
        #ifdef DEBUG
        Serial.println("Turning attract mode off");
        #endif
        player_selects.trigger(player_selects.EVT_COINS_EMPTY);
      }
      if (serialInput == "p_onecoin") {
        #ifdef DEBUG
        Serial.println("One coin entered");
        #endif
        player_selects.trigger(player_selects.EVT_ONE_COIN);
      }
      if (serialInput == "p_morecoins") {
        #ifdef DEBUG
        Serial.println("Mode coins entered");
        #endif
        player_selects.trigger(player_selects.EVT_MORE_COINS);
      }
      if (serialInput == "g_attract") {
        #ifdef DEBUG
        Serial.println("Turning attract mode on");
        #endif
        play_buttons.trigger(play_buttons.EVT_ATTRACT);
      }
      if (serialInput == "g_game_start") {
        #ifdef DEBUG
        Serial.println("Game start");
        #endif
        play_buttons.trigger(play_buttons.EVT_GAME_START);
      }
      if (serialInput == "g_game_over") {
        #ifdef DEBUG
        Serial.println("Game over");
        #endif
        play_buttons.trigger(play_buttons.EVT_GAME_OVER);
      }
      if (serialInput == "g_player_select") {
        #ifdef DEBUG
        Serial.println("Player select");
        #endif
        play_buttons.trigger(play_buttons.EVT_PLAYER_SELECT);
      }
      // Control modes from MAME
      if (serialInput == "mode_attract") {
        #ifdef DEBUG
        Serial.println("System Mode: Attract");
        #endif
        coins.trigger(coins.EVT_ON);
        player_selects.trigger(player_selects.EVT_ATTRACT);
        play_buttons.trigger(play_buttons.EVT_ATTRACT);
        panel.trigger(panel.EVT_ON);
      }
      if (serialInput == "mode_one_player") {
        #ifdef DEBUG
        Serial.println("System Mode: One player select");
        #endif
        coins.trigger(coins.EVT_ON);
        player_selects.trigger(player_selects.EVT_ONE_COIN);
        play_buttons.trigger(play_buttons.EVT_PLAYER_SELECT);
      }
      if (serialInput == "mode_more_players") {
        #ifdef DEBUG
        Serial.println("System Mode: More player select");
        #endif
        coins.trigger(coins.EVT_ON);
        player_selects.trigger(player_selects.EVT_MORE_COINS);
        play_buttons.trigger(play_buttons.EVT_PLAYER_SELECT);
      }
      if (serialInput == "mode_game_play") {
        #ifdef DEBUG
        Serial.println("System Mode: Game play");
        #endif
        coins.trigger(coins.EVT_ON);
        play_buttons.trigger(play_buttons.EVT_GAME_START);
      }
      if (serialInput == "mode_game_over") {
        #ifdef DEBUG
        Serial.println("System Mode: Game over");
        #endif
        coins.trigger(coins.EVT_ON);
        play_buttons.trigger(play_buttons.EVT_GAME_OVER);
      }
      if (serialInput == "mode_no_coins") {
        #ifdef DEBUG
        Serial.println("System Mode: No coins left");
        #endif
        player_selects.trigger(player_selects.EVT_COINS_EMPTY);
      }
      if (serialInput == "mode_rainbow") {
        #ifdef DEBUG
        Serial.println("Rainbow mode activated!");
        #endif
        panel.trigger(panel.EVT_RAINBOW_ON);
      }
      if (serialInput.substring(0, 12) == "mode_hiscore") {
        #ifdef DEBUG
        Serial.println("Hiscore mode activated!");
        #endif
        panel.hiscore = serialInput.substring(12);
        #ifdef DEBUG
        Serial.println(panel.hiscore);
        #endif
        panel.trigger(panel.EVT_HISCORE_ON);
      }
      if (serialInput == "mode_ping") {
        #ifdef DEBUG
        Serial.println("Ping mode activated!");
        #endif
        bell.trigger(bell.EVT_HISCORE);
      }
      // Switch to data mode
      if (serialInput == "mode_data_1") {
        #ifdef DEBUG
        Serial.println("Switching to data mode for image 1");
        #endif
        Serial.print("READY");
        currentByte = 0;
        lastSerial = millis();
        while (true) {
          // Gridlock, Arduino can't have this back until 768 bytes have been read, or a timeout is reached.
          if (Serial.available()) {
            serialData[currentByte++] = (uint8_t)Serial.read();
            lastSerial = millis();
            if (currentByte % serialBufferSize == 0 && currentByte > 0) {
              Serial.print("BLOCK"); // Send some handshaking
            }
            // Process X Bytes of data (RGB), send to the panel and revert to command mode
            if (currentByte >= 768) {
              Serial.print("FINISH"); // Send some handshaking
              // We have a complete frame, send to the panel, drop out of data mode
              panel.setGameImage(serialData);
              break;
            }          
          }
          if (millis() - lastSerial > serialTimeout) {
            Serial.println("TIMEOUT");
            break;
          }
        }
      }
      serialInput = "";
    } else {
      if (serialInput.length() < 40) {
        serialInput += inChar;
      }
    }
  }
}

