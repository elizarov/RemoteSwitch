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

#include "xprint.h"

#include <Metro.h>

#define INITIAL_PRINT_INTERVAL 1000L   // wait 1 s before first print to get XBee time to initialize & join
#define PRINT_INTERVAL          250L   // wait 250 ms between prints 

Metro printTimeout(INITIAL_PRINT_INTERVAL);

void setupPrint() {
  Serial.begin(57600);  
}

void waitPrint() {
  while (!printTimeout.check()); // just wait...
  printTimeout.interval(PRINT_INTERVAL);
  printTimeout.reset();
}

void waitPrintln(const char* s) {
  waitPrint();
  Serial.println(s);
}

void print_P(Print& out, PGM_P str) {
  while (1) {
    char ch = pgm_read_byte_near(str++);
    if (!ch)
      return;
    out.write(ch);
  }
}

void print_P(PGM_P str) {
  print_P(Serial, str);
}

