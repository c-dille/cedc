#ifndef OBJECT_H
# define OBJECT_H

typedef struct s_object
{
	void	*ptr;
	void*	(*clone)(void*);
	void 	(*free)(void*);
	const char *(*serialize)(void *data);
	void	*(*unserialize)(void *data);
}	object;

object	object_clone(object o)
{
	return (o.clone(o.ptr));
}

void 	object_free(object o)
{
	o.free(o.ptr);
}

const char *object_serialize(object o)
{
	return (o.serialize(o.ptr));
}

void	*object_unserialize(object o)
{
	return (o.unserialize(o.ptr));
}

#endif
