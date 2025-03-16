#include "password.h"

/**
 * This function generate a password
 *
 * @param[.in]  charset  The charset to use
 * @param[.in]  length   The length of the password
 *
 * @exception NULL if an error is encountered
 *
 * Returns the password as a string
**/
char* generate_password(charset_t charset, size_t length) {
  char* password = malloc(length);
  if (!password) return NULL;
  
  charset_str_t* charset_str = parse_charset(charset);
  
  int index;
  for (size_t i = 0; i < length; ++i) {
    index = random_int(charset_str->length);
    if (index < 0) return NULL;
    password[i] = charset_str->charset[index];
  }
    
  return password;
}

/**
 * This function convert a charset_t into a char*
 *
 * @param[.in]  charset  The charset to be converted
 *
 * Returns the charset in a string
**/
charset_str_t* parse_charset(charset_t charset) {
  size_t len         = 0; 
  char*  lower       = NULL; 
  char*  upper       = NULL;
  char*  numbers     = NULL;
  char*  charset_str = NULL;

  static charset_str_t charset_str_struct;

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

  for (size_t i = 0; i < len + 1; ++i) {
    charset_str[i] = (char) 0;
  }

  if (lower)   strcat(charset_str, lower)  ;
  if (upper)   strcat(charset_str, upper)  ;
  if (numbers) strcat(charset_str, numbers);

  charset_str_struct.charset = charset_str;
  charset_str_struct.length  = len;

  return &charset_str_struct;
} 

#ifdef _WIN32
  // This function returns a random number. Only with windows
  int random_int_windows(size_t up_range) {
    printf("WARNING : Untested function ! Use at your own risk !\n");
    unsigned int* index;
    if (rand_s(index) != 0) {
      return -1;
    } 
    int return_value = *index % up_range;
    return return_value;
  }
#else
  // This function returns a random number. Compatible with *NIX systems
  int random_int_nix(size_t up_range) {
    FILE *f = fopen("/dev/urandom", "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    int num;
    size_t res = fread(&num, sizeof(num), 1, f);
    if (res < 0) {
      perror("fread");
      return -1;
    }
    fclose(f);

    return num % up_range;
  }
#endif
