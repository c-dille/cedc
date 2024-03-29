#ifndef CE_MACROS_H
# define CE_MACROS_H
# include <stdlib.h>
# include <libc.h>
# include <ctype.h>
# include <dlfcn.h>
# include <errno.h>
# include <stddef.h>
# include <stdarg.h>
# include <stdbool.h>
# include "./types.h"
# include "./debug.h"
# include "./object.h"
# include "./file.h"
# include "./list.h"
# include "./klist.h"
# include "./lpstr.h"

# define IS_EMPTY(...) ( sizeof( (char[]){#__VA_ARGS__} ) == 1 )
# define STR(...) #__VA_ARGS__
# define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
# define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
# define CONCATENATE2(arg1, arg2)  arg1##arg2
# define DEF(X) const char *X = #X;
# define KV(K) STR(K), K
#endif
