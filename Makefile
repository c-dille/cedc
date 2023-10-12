cc = cc -Wall -Werror -Wextra -g #-fsanitize=address
rm = rm -rf
#
sources_dir = sources/
includes_dir = includes/
bin_dir = bin/
#
name = cedilla
#
headers = $(shell find $(includes_dir)* -type f -name "*.h")
sources = $(shell cd sources && find * -type f -name "*.c")
objects = $(addprefix $(bin_dir), $(sources:.c=.o))
#
all:	$(name)
	make -C modules/c99

$(bin_dir)%.o:	$(sources_dir)%.c	$(headers) Makefile
	@mkdir -p $(bin_dir)
	$(cc) -c $< -o $@ -I $(includes_dir)

$(name):	$(objects)
	$(cc) $(objects) -o $(name)

clean:
	$(rm) -rf $(objects)
	make clean -C modules/c99

fclean:	clean
	$(rm) -rf $(name)
	make clean -C modules/c99

re:	fclean all
	make re -C modules/c99

.PHONY: clean fclean all re
.SUFIXES:
