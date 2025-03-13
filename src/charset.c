#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "charset.h"

/** 
 * Ask the user for the charset to use
 *
 * @parm[in]  (void)   No parameter taken  
 *
 * @return a charset_t (defined in "charset.h") that represent the desired charset
 **/
charset_t get_charset(void) {
  charset_t charset = 0;
  char* buffer = malloc(5);

  (void) fgets(buffer, 5,stdin);

  char* current_char = NULL;
  int current = 0;
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    current_char = strdupli(buffer,1);
    current = atoi(current_char);
    switch (current){
      case 1:
	charset |= CHAR_LOWER;
	break;
      
      case 2:
	charset |= CHAR_UPPER;
	break;

      case 3 :
	charset |= CHAR_NUMS;
        break;
      
      case 4 :
	charset |= CHAR_SYMBOL;
	break;
      
      default :
	printf("Unknow option : %d\n", current);
        return (charset_t) 0;
    }
  }

  return charset;
}

/**
 * This function duplicate the len th first charracter of a string 
 *
 * @parm[.in]  buffer  The original string
 * @parm[.in]  len     The amout of character to copy
 *
 * Return a len + 1 long string
**/
char* strdupli(char* buffer, size_t len) {
  char* result = malloc(len + 1);
  for (size_t i = 0; i < len; ++i) {
    result[i] = buffer[i];
  }
  result[len + 1] = "\0";
  return result;
}



