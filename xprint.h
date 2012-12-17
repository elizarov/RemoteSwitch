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

#ifndef PRINT_H
#define PRINT_H

#include <Arduino.h>
#include <avr/pgmspace.h>

void setupPrint();

void waitPrint();
void waitPrintln(const char* s);

void print_P(Print& out, PGM_P str);
void print_P(PGM_P str);

#endif

