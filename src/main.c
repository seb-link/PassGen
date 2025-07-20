#include "common.h"
#include "charset.h"
#include "length.h"
#include "password.h"

int main(void) {
  charset_t charset = get_charset();   // Get the character to use
  if (charset == 0) return 1;
  
  size_t length =  get_length();       // Get the password length
  if (length == 0) {
    printf("Error occured\n");
    return 1;
  }
  char* password = NULL;               // Password to be generated
 
  password = generate_password(charset, length);
  if (!password) // If password == NULL then an error occured
    return 1;
 
  printf("Your password is : ");
  puts(password);

  free(password);
  return 0;
}
