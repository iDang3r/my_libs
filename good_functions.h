#ifndef GOOD_FUNCTIONS_H
#define GOOD_FUNCTIONS_H

#include "super_define.h"

/*!
 * counts number of digits
 *
 * @param[in] x number
 * @return number of digits x
 */

int count_number_digit(int x);

void secure_free(char** ptr) {
    if (*ptr == errptr <char> ())
        assert("DOUBLE FREE!!!" == ERROR);
    free(*ptr);
    poison(ptr);
}

int count_number_digit(int x) {
    int result = 0;
    if (x < 0) {
        result++;
        x *= -1;
    }
    do {
        ++result;
        x /= 10;
    } while (x);
    return result;
}

#endif //GOOD_FUNCTIONS_H