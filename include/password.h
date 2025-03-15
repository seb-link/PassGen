#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "charset.h"

#ifdef _WIN32
#define random_int random_int_windows
int random_int_windows(size_t up_range);
#define _CRT_RAND_S /* For rand_s on windows*/
#else
#define random_int random_int_nix
int random_int_nix(size_t up_range);
#endif

#include <stdlib.h>

typedef struct {
  char*  charset;
  size_t length;
} charset_str_t;

char*           generate_password  (charset_t charset, size_t length);
charset_str_t*  parse_charset      (charset_t charset);

#endif

