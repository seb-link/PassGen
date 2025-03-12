#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "charset.h"

/** 
 * Ask the user for the charset to use
 *
 * @parm[in]  void   No parameter taken  
 *
 * @return a charset_t (defined in "charset.h") that represent the desired charset
 **/
charset_t get_charset(void) {
  charset_t charset = 0;
  char* buffer = malloc(5);

  (void) fgets(buffer, sizeof(buffer), stdin);
  
  for (size_t i = 0; i < sizeof(buffer); ++i) {
    printf("%d\n",(int) buffer[i]);
    switch ((int) buffer[i]){
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
	printf("Hell naw\n");
	return (charset_t) 0;
    }
  }

  return charset;
}
