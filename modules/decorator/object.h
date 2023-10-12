#ifndef OBJECT_H
# define OBJECT_H
# include <macros.h>
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
}	object;

/*

#define DEF_OBJECT_PROTO(TYPE_NAME, TYPE)											\
{																					\
	typedef struct	s_ ## TYPE_NAME ## _object 										\
	{																				\
		void		*ptr;															\
		void		(*free)(void*);													\
		void		*(*clone)(void*);												\
		void		(*compile)(int fd, void* data);									\
	} TYPE_NAME ## _object															\
	const char				*##TYPE_NAME = STR(__ ##TYPE_NAME ## _object_type);		\
	object					TYPE_NAME ## _object_upcast(TYPE_NAME ## _object);		\
	TYPE_NAME ## _object  	TYPE_NAME ## _object_new(TYPE);							\
	void	 				TYPE_NAME ## _object_free(TYPE_NAME ## _object);		\
	TYPE_NAME ## _object 	TYPE_NAME ## _object_clone(TYPE_NAME ## _object);		\
	char					*##TYPE_NAME##_object_compile(TYPE_NAME ## _object);	\
}

#define DEF_OBJECT(TYPE_NAME, TYPE, CLONE, COMPILE, FREE)							\
{																					\
	object	TYPE_NAME ## _ ## _object_upcast(TYPE data)
	{
		return (object) {
			.type = TYPE_NAME,
			.ptr = data,
			...

		}
	}

	char	* ... compile()
	{
		printf(
		(object) {
				...
				.ptr = COMPILE(...)
			}
		)
	}
}


DEF_OBJECT_PROTO(str, char *)
void str_compile(int fd, void *data)
{
	dprintf(fd, "strdup(\"%s\")", (char*)data);
}

DEF_OBJECT(str, char*, strdup, compile_str, free);


DEF_OBJECT_PROTO(const_str, char *)
void const_str_compile(int fd, void *data)
{
	dprintf(fd, "\"%s\"", (char*)data);
}
DEF_OBJECT(str, const char*, 0, const_str_compile, 0);


DEF_OBJECT_PROTO(int, int)
void int_compile(int fd, int data)
{
	dprintf(fd, "\"%i\"", (char*)data);
}
DEF_OBJECT(int, int, 0, int_compile, 0);

*/
#endif
