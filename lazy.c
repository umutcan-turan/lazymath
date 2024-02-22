#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#include "lazy.h"

size_t rstrip(char *str)
{
	size_t len;

	len = strlen(str);
	while (len && isspace(str[len - 1])) {
		len--;
	}
	str[len] = '\0';
	return len;
}

size_t lstrip(char *str)
{
	size_t len;
	size_t skip;

	len = strlen(str);
	skip = 0;
	while ((skip < len) && isspace(str[skip])) {
		skip++;
	}
	if (skip && (len - skip)) {
		memmove(str, str + skip, len - skip);
	}
	str[len - skip] = '\0';
	return len - skip;
}

int str_to_long(const char *str, long *retval)
{
	char *endp;
	long num;
	int err;

	errno = 0;
	num = strtol(str, &endp, 0);
	if (errno) {
		err = errno;
	} else {
		err = !(str[0] && !endp[0]);
		if (!err) {
			*retval = num;
		}
	}
	return err;
}

int getlong(char *str, long *retval)
{
	lstrip(str);
	rstrip(str);
	return str_to_long(str, retval);
}

long sq_less_eq(long a, long b)
{
	if (a <= (LONG_MAX / b)) {
		return a * a <= b;
	}
	return a <= sqrt(b);
}

int read_long(long *retval)
{
	char buf[LAZYMATH_BUFSIZ];
	int err;

	err = !fgets(buf, LAZYMATH_BUFSIZ, stdin);
	if (!err) {
		err = getlong(buf, retval);
	} else if (feof(stdin) || ferror(stdin)) {
		err = EOF;
	}
	return err;
}

void lazy_arr_loop(char *arr[], int len, lazy_func cb)
{
	int rc;
	long num;

	for (int i = 0; i < len; i++) {
		rc = getlong(arr[i], &num);
		if (rc == ERANGE) {
			printf("Number '%s' out of range\n", arr[i]);
		} else if (rc) {
			printf("Failed to convert '%s' to a number\n", arr[i]);
		} else {
			cb(num);
		}
	}
}

void lazy_stdin_loop(lazy_func cb)
{
	int rc;
	long num;

	while (1) {
		rc = read_long(&num);
		if (rc == EOF) {
			printf("Failed to read input\n");
			break;
		} else if (rc == ERANGE) {
			printf("Number is out of range\n");
		} else if (rc == 0){
			cb(num);
		} else {
			printf("Failed to read number\n");
		}
	}
}

void lazy_loop(int argc, char *argv[], lazy_func cb)
{
	const char keep_going_switch[] = "-k";
	int keep_going;

	keep_going = 0;
	if (argc > 1) {
		argv++, argc--;

		if (!strncmp(argv[0], keep_going_switch, sizeof(keep_going_switch))) {
			keep_going = 1;
			argv++, argc--;
		}
		lazy_arr_loop(argv, argc, cb);
		if (!keep_going) {
			return;
		}
	}
	lazy_stdin_loop(cb);
	return;
}
