#include <stdio.h>

#include "prime_table.h"
#include "lazy.h"
#include "lazyfuncs.h"

static int isprime(long n)
{
	long divisor = 2;

	if (n < 2)
		return 0;

	for (size_t i = 0; i < prime_table_size && sq_less_eq(divisor, n); i++) {
		divisor = prime_table[i];
		if (!(n % divisor)) {
			return 0;
		}
	}
	for (; sq_less_eq(divisor, n); divisor++) {
		if (!(n % divisor)) {
			return 0;
		}
	}
	return 1;
}

static long find_next_prime(long x)
{
	for (x++; !isprime(x); x++) {
		;
	}
	return x;
}

void lazy_print_prime(long n)
{
	if (n < 0) {
		n = -n;
	}
	if (n < 2) {
		return;
	}
	if (isprime(n)) {
		printf("%ld\n", n);
	}
}

void lazy_print_prime_fact(long n)
{
	int is_first_print = 1;
	long prime = 0;

	printf("%ld", n);
	while (n && (prime <= n)) {
		long exponent = 0;

		prime = find_next_prime(prime);
		while (!(n % prime)) {
			exponent++;
			n /= prime;
		}
		if (exponent) {
			if (is_first_print) {
				is_first_print = 0;
				printf(" =");
			} else {
				printf(" *");
			}
			printf(" %ld^%ld", prime, exponent);
		}
	}
	putchar('\n');
}

void lazy_print_sq_factors(long n)
{
	for (long r = 1, sq = 1; sq <= n; r++, sq = r*r) {
		if (!(n % sq)) {
			//printf("%ld^2 * %ld (%ld)\n", r, n / sq, sq);
			//printf("(%ld) %ld^2 * %ld\n", sq, r, n / sq);
			printf("%ld / %ld = %ld (%ld^2)\n", n, sq, n / sq, r);
		}
	}
	putchar('\n');
}
void lazy_print_integer_factors(long num)
{
	size_t total;
	long increment;

	if (num < 0) {
		num = -num;
	}
	increment = 1 + (num % 2);
	total = 1;
	printf("%ld = %ld * %ld\n", num, 1L, num);
	for (long i = 1 + increment; sq_less_eq(i, num); i += increment) {
		if (!(num % i)) {
			printf("%ld = %ld * %ld\n", num, i, num / i);
			total++;
		}
	}
	putchar('\n');
}
