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

#ifndef PARSE_H_
#define PARSE_H_

#define CMD_RESET 'R'
#define CMD_OFF   '0'
#define CMD_ON    '1'

char parseCommand();

extern char cmdHouse;
extern char cmdDevice;

#endif /* PARSE_H_ */
