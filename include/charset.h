#ifndef CHARSET_H
#define CHARSET_H


typedef enum {
	CHAR_LOWER  = 1<<1, // Is there lowercase
	CHAR_UPPER  = 1<<2, // Is there uppercase 
	CHAR_NUMS   = 1<<3, // Is there numbers
	CHAR_SYMBOL = 1<<4  // Is there symbols
} charset_t;


charset_t get_charset(void);

#endif

