/*
    Copyright (C) 2012 Roman Elizarov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Metro.h>
#include <util/delay.h>

#include "xprint.h"
#include "blink_led.h"
#include "parse.h"

#define DATA_PIN A1
#define A_TIME 400
#define REPEAT_COUNT 8
#define BIT_COUNT 12

void sendZero() {
  digitalWrite(DATA_PIN, 1);
  _delay_us(A_TIME);
  digitalWrite(DATA_PIN, 0);
  _delay_us(3 * A_TIME);
}

void sendOne() {
  digitalWrite(DATA_PIN, 1);
  _delay_us(3 * A_TIME);
  digitalWrite(DATA_PIN, 0);
  _delay_us(A_TIME);
}

void sendBreak() {
  digitalWrite(DATA_PIN, 1);
  _delay_us(A_TIME);
  digitalWrite(DATA_PIN, 0);
  _delay_us(31 * A_TIME);  
}

void sendBits(int bits) {
  for (int r = 0; r < REPEAT_COUNT; r++) {
    int mask = 1;
    for (int i = 0; i < BIT_COUNT; i++) {
      sendZero();
      if ((bits & mask) != 0)
        sendOne();
      else
        sendZero();
      mask <<= 1;  
    }
    sendBreak();
  }
}

// house - 'A' to 'P'
// device - '1' to '9' and 'A' to 'G'
// operation - '0' (OFF) or '1' (ON)
int encode(char house, char device, char operation) {
  return (house - 'A') + 
    ((device <= '9' ? device - '1' : device - 'A' + 9) << 4) +
    (6 << 8) + ((operation - '0') << 11);
}

//------- SETUP & MAIN -------

void setup() {
  setupPrint();
  pinMode(DATA_PIN, OUTPUT);
  waitPrintln("{S:RemoteSwitch started}*");
}

Metro timer(40000); // turn ON every 40 sec

void loop() {
  blinkLed();
  if (timer.check()) {
    waitPrintln("[S:ON]");
    sendBits(encode('E', '1', '1'));
    timer.reset();    
  }
  char cmd = parseCommand();
  switch (cmd) {
    case CMD_RESET:
      waitPrintln("[S:OFF]*");
      sendBits(encode('E', '1', '0'));
      timer.reset();
      break;
    case CMD_OFF:
    case CMD_ON:
      waitPrint();
      Serial.print("[S:");
      Serial.print(cmdHouse);
      Serial.print(cmdDevice);
      Serial.print(cmd);
      Serial.println("]*");
      sendBits(encode(cmdHouse, cmdDevice, cmd));
      break;
  }
}

