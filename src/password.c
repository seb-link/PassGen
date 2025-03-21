#include "common.h"
#include "password.h"

/**
 * This function generate a password
 *
 * @param[.in]  charset  The charset to use
 * @param[.in]  length   The length of the password
 *
 * @exception NULL if an error is encountered
 * 
 * @return the password as a string
**/
char* generate_password(charset_t charset, size_t length) {
  char* password = malloc(length + 1);
  if (!password) return NULL;
  
  charset_str_t* charset_str = parse_charset(charset);
  
  int index;
  for (size_t i = 0; i < length; ++i) {
    index = random_int(charset_str->length);
    if (index < 0) return NULL;
    password[i] = charset_str->charset[index];
  }
  password[length + 1] = '\0';
  
  double possibilities = pow(charset_str->length, length);
  double entropy       = log2(possibilities);
  
  size_t speed = 240 * (size_t)(pow(10,9)) ;   // Assuming 240 000 000 000 guess per seconds
  double time  = possibilities / speed;

     
  if (entropy == INFINITY) {
    printf("This password powerfulness is impossible to compute making it virtually impossible to crack with the use of conventional methods.\n");
    return password;
  }
  printf("This password as an entropy is : %lf.\n", entropy);
  
  char* time_msg = malloc(100);

  // Spaghetti code
  if (time / 31536000 > 1) { // 31 536 000s = 1y
    double y =  (time / 31536000);
    sprintf(time_msg, "%.2lf years", y);
  }else if (time / 3600 > 1) {
    double h =  (time / 3600);
    sprintf(time_msg, "%.2lfh and %.3lfs", h, time - (int)(h) * 3600);
  }else if(time / 60 > 1) {
    sprintf(time_msg, "%.1lfmin", time / 60);
  }else {
    sprintf(time_msg, "%.3lfs", time);
  }
  
  printf("It will take : %s to crack\n", time_msg);

  free(time_msg);

  return password;
}

/**
 * This function convert a charset_t into a charset_str_t
 *
 * @param[.in]  charset  The charset to be converted
 *
 * @return the charset as a pointer to a charset_str_t (defined in "password.h")
**/
charset_str_t* parse_charset(charset_t charset) {
  size_t len         = 0; 
  char*  lower       = NULL; 
  char*  upper       = NULL;
  char*  numbers     = NULL;
  char*  symbols     = NULL;
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
  if (charset & CHAR_SYMBOL) {
    len += 27;
    symbols = "!#$&()*+,-./:;<=>?@[\\]^_{|}";
  }

  charset_str = malloc(len + 1);
  if (!charset_str) return NULL;

  for (size_t i = 0; i < len + 1; ++i) {
    charset_str[i] = (char) 0;
  }

  if (lower)   strcat(charset_str, lower)  ;
  if (upper)   strcat(charset_str, upper)  ;
  if (numbers) strcat(charset_str, numbers);
  if (symbols) strcat(charset_str, symbols);

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
    if (res == 0) {
      perror("fread");
      return -1;
    }
    fclose(f);

    return num % up_range;
  }
#endif
