#include <stdio.h>
#include <stdlib.h>

#include "length.h"


/**
 * This function ask for user the length of the password
 *
 * @parm[.in]  (void)  No args taken
 *
 * @errors  Returns 0 on error
 *
 * Returns the length desired
**/
int get_length(void) {
  char* buffer = malloc(2);

  (void) fgets(buffer, 2, stdin);
  if (!buffer) {
    perror("fgets");
    return 0;
  }

  int length = atoi(buffer);
   
  free(buffer);

  return length; // length will be 0 on error 
}



