#include <stdio.h>
#include <stdlib.h>


#include "password.h"

/**
 * This function generate a password
 *
 * @parm[.in]  charset  The charset to use
 * @parm[.in]  length   The length of the password
 *
 * @error  Returns NULL if an error is encountered
 *
 * Returns the password as a string
**/
char* generate_password(charset_t charset, size_t length) {
  size_t len = 0;

  char* password    = NULL;
  char* charset_str = NULL;
  char* lower       = NULL; 
  char* upper       = NULL;
  char* numbers     = NULL;

  if (charset & CHAR_LOWER) {
    len += 26;
    lower = "abcdefghijklmnopqrstuvwxyz";
  }
  if (charset & CHAR_UPPER) {
    len += 26;
    upper = "ABCDEFGHIJKMLNOPQRSTUVWXYZ";
  }
  if (charset & CHAR_NUMS) {
    len += 10;
    numbers = "0123456789";
  }
  printf("charset len = %ld\n", len);
  charset_str = malloc(len + 1);
  if (lower) {
    char* temp = malloc(len + 1);
    char* ntemp;
    snprintf(temp, len - 25,"%s", charset_str);
    snprintf(temp, 27 ,"%s", lower);
    ntemp = realloc(temp,len);
    snprintf(charset_str, len, "%s", ntemp);
    free(lower);
    free(ntemp);
  }
  puts(charset_str);
  return NULL;
}

