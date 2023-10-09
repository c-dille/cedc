headers = $(shell find * -type f -name "*.h")
sources = $(shell find * -type f -name "*.c")


all:	cedilla

cedilla:	$(headers) $(sources) Makefile
	cc -Wall -Werror -Wextra sources/*.c -o cedilla -I includes -I libraries

clean:
	rm -rf cedilla

fclean:	clean

re:	fclean all
