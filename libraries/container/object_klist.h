#ifndef OBJECT_KLIST_H
# define OBJECT_KLIST_H
# include "object.h"
# include "klist.h"
/*
	ptr = strdup("yoo")
	nptr = strdup(ptr) // clone
	printf("strdup()")
*/

DEF_KLIST_PROTO(object, object_klist);
void	free_object_klist(object_klist_entry *l)
{
	if (l->value.free)
		l->value.free(l->value.ptr);
	free(l);
}
DEF_KLIST(object, object_klist, free_object_klist);

#endif
