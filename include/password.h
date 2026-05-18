#ifndef PASSWORD_H
#define PASSWORD_H


#include "charset.h"

#if defined(_WIN32)
#  define _CRT_RAND_S /* For rand_s on windows */
#elif defined(__linux__)
#  define _GNU_SOURCE
#endif


#include <stdlib.h>
#include <stddef.h>
#if defined(__linux__)
#  include <sys/random.h>
#endif

typedef struct {
  char*  charset;
  size_t length;
} charset_str_t;

typedef struct {
  size_t seconds   ;
  size_t minutes   ;
  size_t hours     ;
  size_t days      ;
  size_t months    ;
  size_t years     ;
  size_t millennium;
} time_data_t ;

#define DAYS_MILLENIUM 36524250LL
#define SECONDS_MILLENNIUM (3600 * 24 * DAYS_MILLENIUM)

char*           generate_password  (charset_t charset, size_t length);
charset_str_t*  parse_charset      (charset_t charset);
void            print_time         (charset_str_t* charset_str, size_t length);
time_data_t*    timeconvert        (double seconds);
int             random_int         (unsigned int up_range);

#endif

