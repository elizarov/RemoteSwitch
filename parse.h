#ifndef PARSE_H_
#define PARSE_H_

#define CMD_RESET 'R'
#define CMD_OFF   '0'
#define CMD_ON    '1'

char parseCommand();

extern char cmdHouse;
extern char cmdDevice;

#endif /* PARSE_H_ */
