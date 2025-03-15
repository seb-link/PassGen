#include <stdio.h>
#include <stdlib.h>

#include "length.h"


/**
 * This function ask for user the length of the password
 *
 * @param[.in]  (void)  No args taken
 *
 * @errors  Returns 0 on error
 *
 * Returns the length desired
**/
size_t get_length(void) {
  char* buffer = malloc(64);

  (void) fgets(buffer, 64, stdin);
  if (!buffer) {
    perror("fgets");
    return 0;
  }

  int length = atoi(buffer);
   
  free(buffer);

  return length; // length will be 0 on error 
}



