headers = $(shell find * -type f -name "*.h")
sources = c99.c#$(shell find * -type f -name "*.c")
objects = $(sources:.c=.o)
cc = cc -Wall -Werror -Wextra -g# -fsanitize=address
name = c99.so
rm = rm -rf

all:	$(name)

%.o:	%.c	$(headers) Makefile
	$(cc) -c $< -o $@ -I./ -I./../../includes

$(name):	$(objects)
	$(cc) -shared -fPIC $(objects) -o $(name)

clean:
	$(rm) -rf $(objects)

fclean:	clean
	$(rm) -rf $(name)

re:	fclean all

.PHONY: clean fclean all re
.SUFIXES:
