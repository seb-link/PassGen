#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdint.h>

#include "charset.h"

char*  generate_password  (charset_t charset, size_t length);

#endif

