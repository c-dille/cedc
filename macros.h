#ifndef MACROS_H
# define MACROS_H
# include <stdlib.h>
# include <libc.h>
# include <ctype.h>
# include <dlfcn.h>
# include <errno.h>
# include "stdarg.h"


# define IS_EMPTY(...) ( sizeof( (char[]){#__VA_ARGS__} ) == 1 )
# define DEF(X) const char *X = #X;


#endif
