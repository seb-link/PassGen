#include "common.h"
#include "length.h"


/**
 * This function ask for user the length of the password
 *
 * @param[.in]  (void)  No args taken
 *
 * @exception  Returns 0 on error
 *
 * @return the length desired as a size_t
**/
size_t get_length(void) {
  char* buffer = malloc(64);

  printf("Enter the length of the password : ");
  (void) fgets(buffer, 64, stdin);
  if (!buffer) {
    perror("fgets");
    return 0;
  }

  int length = atoi(buffer);
  if (length < 0) {
    length = 0;
  }
   
  free(buffer);

  return length; // length will be 0 on error 
}



