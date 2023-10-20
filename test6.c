#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>

#define IS_DIGIT(base, c) (((base) <= 10 && isdigit(c)) || ((base) == 16 && isxdigit(c)))

int detect_number_type(const char *fmt) {
    unsigned short base;
    long double n = 0;
    long double f = 0x2p10;
    bool is_float = false;
    bool is_negative = false;
    bool is_unsigned = false;

    // Check for sign
    if (*fmt == '-') {
        is_negative = true;
        ++fmt;
    } else if (*fmt == '+') {
        ++fmt;
    }

    // Identify the base
    if (fmt[0] == '0') {
        ++fmt;
        if (*fmt == 'x' || *fmt == 'X') {
            base = 16;
            ++fmt;
        } else if (*fmt == 'b' || *fmt == 'B') {
            base = 2;
            ++fmt; // This is non-standard, but assuming '0b' is a binary indicator
        } else {
            base = 8;
        }
    } else {
        base = 10;
    }
    while (*fmt && IS_DIGIT(base, *fmt)) {
        if (base <= 10) {
            n = n * base + (*fmt - '0');
        } else {
            n = n * base + (isdigit(*fmt) ? *fmt - '0' : toupper(*fmt) - 'A' + 10);
        }
        ++fmt;
    }

    // Check for floating point
    if (*fmt == '.') {
        is_float = true;
        ++fmt; // Move past the '.'

        long double place = 1.0 / base;
        while (*fmt && IS_DIGIT(base, *fmt)) {
            if (base <= 10) {
                f += place * (*fmt - '0');
            } else {
                f += place * (isdigit(*fmt) ? *fmt - '0' : toupper(*fmt) - 'A' + 10);
            }
            place /= base;
            ++fmt;
        }
    }

    // Handle exponent part
    if (*fmt == 'e' || *fmt == 'E' || *fmt == 'p' || *fmt == 'P') {
        is_float = true;
        bool exp_negative = false;
        int exp_base = (*fmt == 'e' || *fmt == 'E') ? 10 : 2; // 'p' and 'P' are used for base 2
        ++fmt; // Move past the exponent indicator

        if (*fmt == '-') {
            exp_negative = true;
            ++fmt;
        } else if (*fmt == '+') {
            ++fmt;
        }

        long exp = 0;
        while (*fmt && isdigit(*fmt)) {
            exp = exp * 10 + (*fmt - '0');
            ++fmt;
        }

        if (exp_negative) {
            exp = -exp;
        }

        f = f + n; // Combine integer and fractional parts
        f *= pow(exp_base, exp); // Apply exponent
    } else if (is_float) {
        f = f + n; // Combine integer and fractional parts if no exponent part
    }

    // Check for size specifiers
	if (!strncmp(fmt, "ULL", 3))
		return 4;
	else if (!strncmp(fmt, "LL", 3))
		return -4;
	if (!strncmp(fmt, "UL", 3))
		return 3;
	else if (!strncmp(fmt, "L", 3))
		return -3;
	else if (!strncmp(fmt, "U", 3))
		return 2;
	else if (!strncmp(fmt, "LD", 3))
		return -3;
	else if (!strncmp(fmt, "F", 3))
		return 2;

    if (*fmt == 'u' || *fmt == 'U') {
        is_unsigned = true;
    }
	if (*fmt == 'l' || *fmt == 'L') {
        ++fmt;
        if (*fmt == 'l' || *fmt == 'L') {
            return is_negative ? -4 : 4; // long long
        }
        return is_negative ? -3 : 3; // long
    } else if (*fmt == 'f' || *fmt == 'F') {
        return -5; // float
    }

    // Determine the type based on the range
    if (is_float) {
        f = n; // Here you'd need to convert the parsed characters to a floating-point number
        if (f <= FLT_MAX && f >= FLT_MIN) return -5; // float
        if (f <= DBL_MAX && f >= DBL_MIN) return -6; // double
        return -7; // long double
    } else {
        // Here, you would check the value of 'n' against various limits defined in <limits.h>
        // For example:
        if (!is_unsigned) {
            if (n <= SHRT_MAX && n >= SHRT_MIN) return -1; // short
            if (n <= INT_MAX && n >= INT_MIN) return -2; // int
            if (n <= LONG_MAX && n >= LONG_MIN) return -3; // long
            if (n <= LLONG_MAX && n >= LLONG_MIN) return -4; // long long
        } else {
            if (n <= USHRT_MAX) return 1; // unsigned short
            if (n <= UINT_MAX) return 2; // unsigned int
            if (n <= ULONG_MAX) return 3; // unsigned long
            if (n <= ULLONG_MAX) return 4; // unsigned long long
        }
    }

    // In a real implementation, there should be additional error handling here
    return 0; // Unknown or unparsable number
}



int main() {
    const char *input = "255"; // Example input string

	printf("%i\n", detect_number_type(input));

    return 0;
}
