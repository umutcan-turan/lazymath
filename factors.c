#include <stdlib.h>

#include "lazy.h"
#include "lazyfuncs.h"

int main(int argc, char *argv[])
{
	lazy_loop(argc, argv, lazy_print_integer_factors);
	return 0;
}

