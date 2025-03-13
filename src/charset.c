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
  char* buffer = malloc(64);

  (void) fgets(buffer, 64,stdin);

  char* current_char = NULL;
  int current = 0;
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    current_char = strdupli(buffer, i);
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
  
  free(buffer);
  free(current_char);
  return charset;
}

/**
 * This function duplicate the charracter at position index of a string 
 *
 * @parm[.in]  buffer  The original string
 * @parm[.in]  index   The index of buffer to by copied
 *
 * Return a 2 bytes long string
**/
char* strdupli(char* buffer, size_t index) {
  char* result = malloc(2);
  if (!result) {
    perror("malloc");
    return NULL; // return result; XD
  }
  result[0] = buffer[index];
  result[1] = "\0";
  return result;
}



