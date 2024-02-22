#ifndef LAZYMATH_UTIL_H
#define LAZYMATH_UTIL_H

#include <stddef.h>

#define LAZYMATH_BUFSIZ (200)

typedef void (*lazy_func)(long num);

size_t rstrip(char *str);
size_t lstrip(char *str);
int str_to_long(const char *str, long *retval);
int getlong(char *str, long *retval);
long sq_less_eq(long a, long b);
int read_long(long *retval);
void lazy_arr_loop(char *arr[], int len, lazy_func cb);
void lazy_stdin_loop(lazy_func cb);
void lazy_loop(int argc, char *argv[], lazy_func cb);

#endif
