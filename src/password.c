#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "password.h"

/**
 * This function generate a password
 *
 * @param[.in]  charset  The charset to use
 * @param[.in]  length   The length of the password
 *
 * @error  Returns NULL if an error is encountered
 *
 * Returns the password as a string
**/
char* generate_password(charset_t charset, size_t length) {
  char* password    = NULL;
  
  char* charset_str = parse_charset(charset);
  puts(charset_str); 
  // Still in development...
  return NULL;
}

/**
 * This function convert a charset_t into a char*
 *
 * @param[.in]  charset  The charset to be converted
 *
 * Returns the charset in a string
**/
char* parse_charset(charset_t charset) {
  size_t len         = 0; 
  char*  lower       = NULL; 
  char*  upper       = NULL;
  char*  numbers     = NULL;
  char*  charset_str = NULL;

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
  charset_str = malloc(len + 1);
  if (!charset_str) return NULL;
  for (int i = 0; i < len + 1; ++i) {
    charset_str[i] = (char) 0;
  }
  if (lower)   strcat(charset_str, lower)  ;
  if (upper)   strcat(charset_str, upper)  ;
  if (numbers) strcat(charset_str, numbers);
  return charset_str;
} 

