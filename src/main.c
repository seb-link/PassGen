#include <stdio.h>
#include <stdlib.h>

#include "charset.h"
#include "length.h"

int main(void) {
  charset_t charset  =  get_charset();   // Get the character to use
  if (charset == (charset_t) 0 ) return 1;
  int       length   =  get_length();    // Get the password length
  if (length == 0) return 1;
  /*char*     password = malloc(length); // Password to be generated
  if (!password) {
    perror("malloc");
    return 1;
  }
  password = generate_random_password(charset, length);
  if (!password) // If password == NULL then an error occured
    return 1;
  */
  return 0;
}
