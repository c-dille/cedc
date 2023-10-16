#include <stdio.h>

#define test(...) __VA_ARGS__

int main()
{
	printf("%i %i", test(41, 42));
}
