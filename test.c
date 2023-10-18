#include <stdio.h>
#include <string.h>

#define test(...) __VA_ARGS__

char *findfirstunescaped(const char *str, const char *c)
{
	int i = 0;

	while (str[i])
	{
		if (!strncmp(str + i, c, strlen(c)) && (i == 0 || str[i - 1] != '\\'))
			return (char *)&str[i];
		i += 1;
	}
	return NULL;
}

typedef int test;
typedef unsigned p;

int main()
{
	printf("%i %i", test(41, 42));

	const char *str = "This is '  lol '.";
	const char *quote = "'";
	const char *result = findfirstunescaped(str, quote);

	if (result != NULL)
	{
		printf("Found\\: %s\n", result);
	}
	else
	{
		printf("Not found\n");
	}

	int i;

	i &= 2;

}
