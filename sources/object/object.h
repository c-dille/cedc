#ifndef OBJECT_H
# define OBJECT_H
# include "./../macros.h"
/*
	ptr = strdup("yoo")
	nptr = strdup(ptr) // clone
	printf("strdup()")
*/

DEF(STRING)
DEF(STATIC_STRING)
DEF(INT)


typedef struct
{
	const char	*type;
	void		*ptr;
	void		(*free)(void*);
	void		*(*clone)(void*);
	void		(*compile)(int fd, void* data);
	bool		is_const;
}	object;




/*

	typedef struct
	{

	} int_object;

	const

	new_int_object(42);

*/

// may be create a const field for each object prototype so that object itself dont contains
// reddundant data
// object = string_object
// string_object = object

void compile_str(int fd, void *data)
{
	dprintf(fd, "strdup(\"%s\")", (char*)data);
}

void compile_static_str(int fd, void *data)
{
	dprintf(fd, "\"%s\"", (char*)data);
}

object	new_str_object(char *ptr)
{
	return (object) {
		.type		= STRING,
		.ptr		= ptr,
		.free		= free,
		.clone		= (void*(*)(void*))strdup,
		.compile	= compile_str,
		.is_const	= false
	};
}

object	new_static_str_object(char *ptr)
{
	return (object) {
		.type		= STATIC_STRING,
		.ptr		= ptr,
		.free		= 0,
		.clone		= 0,
		.compile	= compile_static_str
	};
}

#endif
