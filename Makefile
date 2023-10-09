headers = $(shell find * -type f -name "*.h")


all:	cedilla

cedilla:	$(headers)
	cc -Wall -Werror -Wextra sources/*.c -o cedilla -I includes -I libraries

clean:
	rm -rf cedilla

fclean:	clean

re:	fclean all
