const static uint8_t char_widths[96] PROGMEM = {
/*0 1 2 3 4 5 6 7 8 9*/
      4,2,4,7,7,7,7,2, // 30
  7,3,3,7,6,3,5,2,4,3, // 40
  4,5,4,4,4,4,4,4,8,8, // 50
  8,8,8,8,8,5,8,8,8,8, // 60
  8,8,8,8,8,8,8,8,8,8, // 70
  8,8,8,8,8,8,8,8,8,8, // 80
  8,8,8,8,8,8,8,8,8,8, // 90
  8,8,8,8,8,8,8,8,8,8, // 100
  8,8,8,8,8,8,8,8,8,8, // 110
  8,8,8,8,8,8,8,8      // 120
};

const static uint8_t charset[] PROGMEM = {
//const static uint8_t charset[96][8] PROGMEM = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // 32
    // 33
    0b00000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b00000000,
    0b01000000,
    0b00000000,
    // 34
    0b00000000,
    0b01010000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    // 35
    0b00000000,
    0b00100100,
    0b01111110,
    0b00100100,
    0b00100100,
    0b01111110,
    0b00100100,
    0b00000000,
    // 36
    0b00010000,
    0b01111110,
    0b01010000,
    0b01111110,
    0b00010010,
    0b00010010,
    0b01111110,
    0b00010000,
    // 37
    0b00000000,
    0b01110010,
    0b01010100,
    0b01111000,
    0b00011110,
    0b00101010,
    0b01001110,
    0b00000000,
    // 38
    0b00000000,
    0b01110000,
    0b01010010,
    0b01110100,
    0b00101000,
    0b01010100,
    0b01110010,
    0b00000000,
    // 39
    0b00000000,
    0b01000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    // 40
    0b00000000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b01000000,
    0b00100000,
    0b00000000,
    // 41
    0b00000000,
    0b01000000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b01000000,
    0b00000000,
    // 42
    0b00000000,
    0b01010010,
    0b00110100,
    0b01111110,
    0b00011000,
    0b00110100,
    0b01010010,
    0b00000000,
    // 43
    0b00000000,
    0b00010000,
    0b00010000,
    0b01111100,
    0b00010000,
    0b00010000,
    0b00000000,
    0b00000000,
    // 44
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00100000,
    0b01000000,
    0b00000000,
    // 45
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    // 46
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b00000000,
    // 47
    0b00000000,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b00000000,
    // 48
    0b00000000,
    0b00100000,
    0b01010000,
    0b01010000,
    0b01010000,
    0b01010000,
    0b00100000,
    0b00000000,
    // 49
    0b00000000,
    0b00100000,
    0b01100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00100000,
    0b00000000,
    // 50
    0b00000000,
    0b00100000,
    0b01010000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b01110000,
    0b00000000,
    // 51
    0b00000000,
    0b00110000,
    0b01001000,
    0b00010000,
    0b00001000,
    0b01001000,
    0b00110000,
    0b00000000,
    // 52
    0b00000000,
    0b01000000,
    0b01010000,
    0b01010000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b00000000,
    // 53
    0b00000000,
    0b01110000,
    0b01000000,
    0b01100000,
    0b00010000,
    0b01010000,
    0b00100000,
    0b00000000,
    // 54
    0b00000000,
    0b00110000,
    0b01000000,
    0b01100000,
    0b01010000,
    0b01010000,
    0b00100000,
    0b00000000,
    // 55
    0b00000000,
    0b01110000,
    0b00010000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b01000000,
    0b00000000,
    // 56
    0b00000000,
    0b00100000,
    0b01010000,
    0b00100000,
    0b01010000,
    0b01010000,
    0b00100000,
    0b00000000,
    // 57
    0b00000000,
    0b00100000,
    0b01010000,
    0b01010000,
    0b00110000,
    0b00010000,
    0b01100000,
    0b00000000,
    // 58
    0b00000000,
    0b01000000,
    0b01000000,
    0b00000000,
    0b00000000,
    0b01000000,
    0b01000000,
    0b00000000,
    // 59
    0b00000000,
    0b00100000,
    0b00100000,
    0b00000000,
    0b00000000,
    0b00100000,
    0b01000000,
    0b00000000,
    // 60
    0b00000000,
    0b00000110,
    0b00011000,
    0b01100000,
    0b01100000,
    0b00011000,
    0b00000110,
    0b00000000,
    // 61
    0b00000000,
    0b00000000,
    0b01111000,
    0b00000000,
    0b01111000,
    0b00000000,
    0b00000000,
    0b00000000,
    // 62
    0b00000000,
    0b01100000,
    0b00011000,
    0b00000110,
    0b00000110,
    0b00011000,
    0b01100000,
    0b00000000,
    // 63
    0b00000000,
    0b00111100,
    0b01000010,
    0b00001100,
    0b00010000,
    0b00000000,
    0b00010000,
    0b00000000,
    // 64
    0b00000000,
    0b00111100,
    0b01000010,
    0b01011010,
    0b01111010,
    0b00000010,
    0b01111100,
    0b00000000,
    // 65
    0b00000000,
    0b00100000,
    0b01010000,
    0b01010000,
    0b01110000,
    0b01010000,
    0b01010000,
    0b00000000,
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 66
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 67
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 68
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 69
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 70
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 71
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 72
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 73
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 74
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 75
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 76
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 77
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 78
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 79
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 80
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 81
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 82
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 83
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 84
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 85
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 86
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 87
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 88
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 89
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 90
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 91
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 92
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 93
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 94
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 95
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 96
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 97
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 98
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 99
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 100
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 101
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 102
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 103
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 104
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 105
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 106
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 107
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 108
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 109
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 110
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 111
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 112
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 113
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 114
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 115
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 116
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 117
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 118
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 119
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 120
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 121
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 122
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 123
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 124
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 125
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000, // 126
  0b00000000, 0b01111110, 0b01000010, 0b01011010, 0b01011010, 0b01000010, 0b01111110, 0b00000000  // 127
};