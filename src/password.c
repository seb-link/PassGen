#include "password.h"
#include "common.h"

#include <stddef.h>
#include <stdlib.h>

static unsigned int calculate_timeleft(double            *timeleft,
                                       unsigned long long time_in_sec);

/**
 * This function generate a password
 *
 * @param[in]  charset  The charset to use
 * @param[in]  length   The length of the password
 *
 * @exception NULL if an error is encountered
 *
 * @return the password as a string
 **/
char *generate_password(charset_t charset, size_t length)
{
    char *password = malloc(length + 1);
    if (!password) return NULL;

    charset_str_t *charset_str = parse_charset(charset);
    if (!charset_str) {
        free(password);
        return NULL;
    }

    int index;
    for (size_t i = 0; i < length; ++i) {
        index = random_int(charset_str->length);
        if (index < 0) {
            free(password);
            password = NULL;
            goto end;
        }
        password[i] = charset_str->charset[index];
    }
    password[length] = '\0';

    print_time(charset_str, length);

end:
    free(charset_str->charset);

    return password;
}

/**
 * This function convert a charset_t into a charset_str_t
 *
 * @param[in]  charset  The charset to be converted
 *
 * @exception Returns NULL
 *
 * @return the charset as a pointer to a charset_str_t (defined in "password.h")
 **/
charset_str_t *parse_charset(charset_t charset)
{
    size_t len         = 0;
    char  *lower       = NULL;
    char  *upper       = NULL;
    char  *numbers     = NULL;
    char  *symbols     = NULL;
    char  *charset_str = NULL;

    static charset_str_t charset_str_struct;

    if (charset & CHAR_LOWER) {
        len += 26;
        lower = "abcdefghijklmnopqrstuvwxyz";
    }
    if (charset & CHAR_UPPER) {
        len += 26;
        upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (charset & CHAR_NUMS) {
        len += 10;
        numbers = "0123456789";
    }
    if (charset & CHAR_SYMBOL) {
        len += 27;
        symbols = "!#$&()*+,-./:;<=>?@[\\]^_{|}";
    }

    charset_str = calloc(len + 1, sizeof(char));
    if (!charset_str) {
        perror("calloc");
        return NULL;
    }

#define ADD_CHARSETSTR(field)                                                  \
    do {                                                                       \
        const char *_field = (field);                                          \
        if (_field) {                                                          \
            strcat(charset_str, field);                                        \
        }                                                                      \
    } while (0)

    ADD_CHARSETSTR(lower);
    ADD_CHARSETSTR(upper);
    ADD_CHARSETSTR(numbers);
    ADD_CHARSETSTR(symbols);

#undef ADD_CHARSETSTR

    charset_str_struct.charset = charset_str;
    charset_str_struct.length  = len;

    return &charset_str_struct;
}

// This functions print the estimated time to crack a password
void print_time(charset_str_t *charset_str, size_t length)
{
    double possibilities = pow(charset_str->length, length);
    double entropy       = log2(possibilities);

    double speed =
        240 * (double)(pow(10, 9)); // Assuming 240 billions guess per seconds
    double time = possibilities / speed;

    if (entropy == INFINITY) {
        printf("Couldn't compute this password powerfulness making it "
               "virtually impossible to crack with the use of conventional "
               "methods.\n");
        return;
    }
    printf("This password as an entropy is : %lf.\n", entropy);

    if (time > SECONDS_MILLENNIUM * 1000) {
        printf("It would take more than 1000 millenniums to crack this "
               "password !\n");
        return;
    }

    time_data_t *times = timeconvert(time);

#define PRINT_TIME_FIELD(field)                                                \
    do {                                                                       \
        if (times->field != 0) {                                               \
            printf("%zu %s ", times->field, #field);                           \
        }                                                                      \
    } while (0)

    PRINT_TIME_FIELD(millennium);
    PRINT_TIME_FIELD(years);
    PRINT_TIME_FIELD(months);
    PRINT_TIME_FIELD(days);
    PRINT_TIME_FIELD(hours);
    PRINT_TIME_FIELD(minutes);
    printf("%zu seconds ", times->seconds);

    printf("to crack !\n");
}

time_data_t *timeconvert(const double seconds)
{
    double timeleft = seconds;

    static time_data_t time;

    time.millennium = calculate_timeleft(&timeleft, SECONDS_MILLENNIUM);
    time.years      = calculate_timeleft(&timeleft, 3600 * 24 * 365);
    time.months     = calculate_timeleft(&timeleft, 3600 * 24 * 30);
    time.days       = calculate_timeleft(&timeleft, 3600 * 24);
    time.hours      = calculate_timeleft(&timeleft, 3600);
    time.minutes    = calculate_timeleft(&timeleft, 60);
    time.seconds    = timeleft;

    return &time;
}

static unsigned int calculate_timeleft(double            *timeleft,
                                       unsigned long long time_in_sec)
{
    unsigned int result = (unsigned int)(*timeleft / time_in_sec);
    *timeleft -= result * time_in_sec;
    return result;
}

int random_int(unsigned int up_range)
{
    if (up_range == 0) return 0;

    // limit is divisible by up_range to negate modulo bias
    uint32_t limit = UINT32_MAX - (UINT32_MAX % up_range);
    uint32_t num;

    do {
#if defined(_WIN32)
        if (rand_s(&num) != 0) {
            perror("rand_s");
            return -1;
        }
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__OpenBSD__)
        num = arc4random();
#elif defined(__linux__)
        if (getrandom(&num, sizeof(num), 0) != sizeof(num)) {
            perror("getrandom");
            return -1;
        }
#endif
    } while (num >= limit);

    return num % up_range;
}
