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
 
  free(charset_str->charset);
  
  double possibilities = pow(charset_str->length, length);
  double entropy       = log2(possibilities);
  
  size_t speed = 240 * (size_t)(pow(10,9)) ;   // Assuming 240 000 000 000 guess per seconds
  double time  = possibilities / speed;

     
  if (entropy == INFINITY) {
    printf("This password powerfulness is impossible to compute making it virtually impossible to crack with the use of conventional methods.\n");
    return password;
  }
  printf("This password as an entropy is : %lf.\n", entropy);

  unsigned long long mill_sec = 31536000000001ULL; // 1000 millenniums in seconds !
  if ( time > mill_sec ) {
    printf("It would take more than 1000 millenniums to crack this password !\n");
  } else {
    time_data_t* times = timeconvert(time);
    if (times->millennium != 0) printf("%ld millennium ", times->millennium);
    if (times->years != 0)      printf("%ld years ",      times->years);
    if (times->months != 0)     printf("%ld months ",     times->months);
    if (times->days != 0)       printf("%ld days ",       times->days);
    if (times->hours != 0)      printf("%ld hours ",      times->hours);
    if (times->minutes != 0)    printf("%ld minutes ",     times->minutes);
    printf("%ld seconds ", times->seconds);
    printf("to crack !\n");
  }

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

time_data_t* timeconvert(double seconds) {
  double timeleft = seconds;
  
  static time_data_t time;

  unsigned long long mill_sec = 31536000000ULL;
  if (timeleft / mill_sec > 1) { // millennium 
    while (timeleft / mill_sec > 1) {
      timeleft -= mill_sec;
      time.millennium += 1;
    }
  }

  if (timeleft / (3600 * 24 * 365) > 1) { // years 
    while (timeleft / (3600 * 24 * 365) > 1) {
      timeleft -= (3600 * 24 * 365);
      time.years += 1;
    }
  }
 
  if (timeleft / (3600 * 24 * 30) > 1) { // months 
    while (timeleft / (3600 * 24 * 30) > 1) {
      timeleft -= (3600 * 24 * 30);
      time.months += 1;
    }
  }

  if (timeleft / (3600 * 24) > 1) { // days 
    while (timeleft / (3600 * 24) > 1) {
      timeleft -= (3600 * 24);
      time.days += 1;
    }
  }

  if (timeleft / (3600) > 1) { // hours 
    while (timeleft / (3600) > 1) {
      timeleft -= (3600);
      time.hours += 1;
    }
  }

  if (timeleft / (60) > 1) { // minutes 
    while (timeleft / (60) > 1) {
      timeleft -= (60);
      time.minutes += 1;
    }
  }
  time.seconds = timeleft;

  return &time;
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
