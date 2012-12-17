#include <Arduino.h>

#include "parse.h"

#define PARSE_ANY       0
#define PARSE_ATTN      1      // Attention char '!' received, wait for 'R'
#define PARSE_WCMD      2      // '!R' was read, wait for command char
#define PARSE_DEVICE    3
#define PARSE_OPERATION 4

byte parseState = PARSE_ANY;
byte parseArg;

char cmdHouse;
char cmdDevice;

inline char parseChar(char ch) {
  switch (parseState) {
  case PARSE_ANY:
    if (ch == '!')
      parseState = PARSE_ATTN;
    break;
  case PARSE_ATTN:
    parseState = (ch == 'R') ? PARSE_WCMD : PARSE_ANY;
    break;
  case PARSE_WCMD:
    switch (ch) {
    case CMD_RESET:
      parseState = PARSE_ANY;
      return ch; // command for external processing
    default:
      if (ch >= 'A' && ch <= 'P') {
        cmdHouse = ch;
        parseState = PARSE_DEVICE;
      } else
        parseState = PARSE_ANY;
    }
    break;
  case PARSE_DEVICE:
    if (ch >= '1' && ch <= '9' || ch >= 'A' && ch <= 'G') {
      cmdDevice = ch;
      parseState = PARSE_OPERATION;
    } else
      parseState = PARSE_ANY;
    break;    
  case PARSE_OPERATION:
    if (ch >= '0' && ch <= '1') {
      parseState = PARSE_ANY;
      return ch;
    }  
    break;
  }
  return 0;
}

char parseCommand() {
  while (Serial.available()) {
    char cmd = parseChar(Serial.read());
    if (cmd != 0)
      return cmd;
  }
  return 0;
}
