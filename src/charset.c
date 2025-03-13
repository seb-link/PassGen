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
  if (!buffer) {
    perror("malloc");
    return 0;
  }

  (void) fgets(buffer, 64,stdin);

  char* current_char = NULL;
  int current = 0;
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    current = (int) buffer[i] - 48; // Sorry for the magic number. 1 in ascii is 49
    if (current < 0) break;
    switch (current) {
      case 0 :
        break; // The rest of the buffer
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
        return 0;
    }
  }
  
  free(buffer);
  free(current_char);
  return charset;
}

