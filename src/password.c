#include "password.h"
#include "common.h"

#include <stdlib.h>
#include <stddef.h>

static unsigned int calculate_timeleft(double *timeleft,
                                       unsigned long long time_in_sec);

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
char *generate_password(charset_t charset, size_t length)
{
  char *password = malloc(length + 1);
  if (!password)
    return NULL;

  charset_str_t *charset_str = parse_charset(charset);

  int index;
  for (size_t i = 0; i < length; ++i) {
    index = random_int(charset_str->length);
    if (index < 0) {
      free(password);
      free(charset_str->charset);
      return NULL;
    }
    password[i] = charset_str->charset[index];
  }
  password[length] = '\0';

  free(charset_str->charset);

  print_time(charset_str, length);

  return password;
}

/**
 * This function convert a charset_t into a charset_str_t
 *
 * @param[.in]  charset  The charset to be converted
 *
 * @return the charset as a pointer to a charset_str_t (defined in "password.h")
 **/
charset_str_t *parse_charset(charset_t charset)
{
  size_t len = 0;
  char *lower = NULL;
  char *upper = NULL;
  char *numbers = NULL;
  char *symbols = NULL;
  char *charset_str = NULL;

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
  if (!charset_str)
    return NULL;

  for (size_t i = 0; i < len + 1; ++i) {
    charset_str[i] = (char)0;
  }

  #define ADD_CHARSETSTR(field)         \
    do {                                \
        const char *_field = (field);   \
        if (_field) {                   \
            strcat(charset_str, field); \
        }                               \
    } while(0)                          \

  ADD_CHARSETSTR(lower);
  ADD_CHARSETSTR(upper);
  ADD_CHARSETSTR(numbers);
  ADD_CHARSETSTR(symbols);

  #undef ADD_CHARSETSTR
  
  charset_str_struct.charset = charset_str;
  charset_str_struct.length = len;

  return &charset_str_struct;
}

// This functions print the estimated time to crack a password
void print_time(charset_str_t *charset_str, size_t length)
{
  double possibilities = pow(charset_str->length, length);
  double entropy = log2(possibilities);

  size_t speed =
      240 * (size_t)(pow(10, 9)); // Assuming 240 billions guess per seconds
  double time = possibilities / speed;

  if (entropy == INFINITY) {
    printf("This password powerfulness is impossible to compute making it "
           "virtually impossible to crack with the use of conventional "
           "methods.\n");
    return;
  }
  printf("This password as an entropy is : %lf.\n", entropy);

  if (time > MILLENNIUM_SECONDS*1000) {
    printf(
        "It would take more than 1000 millenniums to crack this password !\n");
  } else {
    time_data_t *times = timeconvert(time);
    #define PRINT_TIME_FIELD(field) \
        do {                        \
            if (times->field != 0) { \
                printf("%zu %s ", times->field, #field);\
            }\
        } while (0)\

    PRINT_TIME_FIELD(millennium);
    PRINT_TIME_FIELD(years);
    PRINT_TIME_FIELD(months);
    PRINT_TIME_FIELD(hours);
    PRINT_TIME_FIELD(minutes);
    printf("%zu seconds ", times->seconds); 
    
    printf("to crack !\n");
  }
}

time_data_t *timeconvert(const double seconds)
{
  double timeleft = seconds;

  static time_data_t time;

  time.millennium = calculate_timeleft(&timeleft, MILLENNIUM_SECONDS); 
  time.years = calculate_timeleft(&timeleft, 3600 * 24 * 365);
  time.months = calculate_timeleft(&timeleft, 3600 * 24 * 30);
  time.days = calculate_timeleft(&timeleft, 3600 * 24);
  time.hours = calculate_timeleft(&timeleft, 3600);
  time.minutes = calculate_timeleft(&timeleft, 60);
  time.seconds = timeleft;

  return &time;
}

static unsigned int calculate_timeleft(double *timeleft,
                                       unsigned long long time_in_sec)
{
  unsigned int result = (unsigned int) (*timeleft / time_in_sec);
  *timeleft -= result * time_in_sec;
  return result;
}

#ifdef _WIN32
// This function returns a random number. Only with windows
int random_int_windows(size_t up_range)
{
  printf("WARNING : Untested function ! Use at your own risk !\n");
  unsigned int *index;
  if (rand_s(index) != 0) {
    return -1;
  }
  int return_value = *index % up_range;
  return return_value;
}
#else
// This function returns a random number. Compatible with *NIX systems
int random_int_nix(size_t up_range)
{
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
