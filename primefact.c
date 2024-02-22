#include <stdlib.h>

#include "lazy.h"
#include "lazyfuncs.h"

int main(int argc, char *argv[])
{
	lazy_loop(argc, argv, lazy_print_prime_fact);
	return 0;
}
