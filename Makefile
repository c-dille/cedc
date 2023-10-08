headers = $(shell find * -type f -name "*.h")

cedilla:	$(headers)
	cc -Wall -Werror -Wextra sources/*.c -o cedilla -I includes -I libraries
