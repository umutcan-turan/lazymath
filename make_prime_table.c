#include <stdlib.h>
#include <stdio.h>

#include "lazy.h"

static int is_prime(long n)
{
	if (n < 2)
		return 0;

	for (long i = 2; sq_less_eq(i, n); i++) {
		if ((n % i) == 0) {
			return 0;
		}
	}
	return 1;
}

static long find_next_prime(long x)
{
	for (x++; !is_prime(x); x++) {
		;
	}
	return x;
}

int main(int argc, char *argv[])
{
	const char *header = "#ifndef PRIME_TABLE_H\n#define PRIME_TABLE_H\n";
	const char *footer = "#endif\n";
	const char *varname = "prime_table";
	const size_t length = 5000;
	int is_first_num = 1;
	long n = 1;

	(void)argc;
	(void)argv;

	printf("%s", header);
	printf("const size_t %s_size = %ld;\n", varname, length);
	printf("const long %s[%ld] = {", varname, length);
	for (size_t i = 0; i < length; i++) {
		n = find_next_prime(n);

		if (is_first_num) {
			is_first_num = 0;
		} else {
			printf(",");
		}
		printf(" %ld", n);
	}
	printf("};\n");
	printf("%s", footer);
	return 0;
}
