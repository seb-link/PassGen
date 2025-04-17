#ifndef PASSWORD_H
#define PASSWORD_H

#include "charset.h"

#ifdef _WIN32

#define random_int random_int_windows
int random_int_windows(size_t up_range);
#define _CRT_RAND_S /* For rand_s on windows */

#else

#define random_int random_int_nix
int random_int_nix(size_t up_range);

#endif

#include <stdlib.h>

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

char*           generate_password  (charset_t charset, size_t length);
charset_str_t*  parse_charset      (charset_t charset);
void            print_time         (charset_str_t* charset_str, size_t length);
time_data_t*    timeconvert        (double seconds);

#endif

