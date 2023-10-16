#ifndef CE_LIST_H
# define CE_LIST_H
# define DEF_LIST_PROTO(TYPE, NAME)     \
                                        \
	typedef struct s_ ## NAME			\
	{									\
		TYPE				data;		\
		struct s_ ## NAME	*next;		\
		struct s_ ## NAME	*prev;		\
	}  NAME;							\
NAME    *NAME ## _last(NAME *l);		\
NAME    *NAME ## _new(TYPE data);		\
NAME    *NAME ## _add_front(NAME **l, TYPE data);\
NAME    *NAME ## _add(NAME **l, TYPE data);\
NAME    *NAME ## _link_front(NAME **l, NAME *i);\
NAME    *NAME ## _link(NAME **l, NAME *i);\
void    NAME ## _del(NAME **l, NAME *k);\
void    NAME ## _free(NAME *l); \
NAME    *NAME ## _clone(NAME    *);\

# define DEF_LIST(TYPE, NAME, FREEF, CLONEF)\
										\
NAME    *NAME ## _last(NAME *l)			\
{										\
    while (l)							\
    {									\
        if (!l->next)					\
            return l;					\
        l = l->next;					\
    }									\
    return 0;							\
}										\
ull 	NAME ## _count(NAME *l)			\
{										\
	ull		o = 0;						\
    while (l)							\
    {									\
		o += 1;							\
        if (!l->next)					\
            return (o);					\
        l = l->next;					\
    }									\
    return 0;							\
}										\
NAME    *NAME ## _new(TYPE data)		\
{										\
    NAME *o;							\
										\
    o = malloc(sizeof(NAME));			\
    o->data = data;						\
    o->next = 0;						\
    o->prev = 0;                        \
    return o;							\
}										\
										\
NAME    *NAME ## _add(NAME **l, TYPE data)\
{										\
   	return  NAME ## _link(l, NAME ## _new(data));\
}                                       \
										\
NAME    *NAME ## _add_front(NAME **l, TYPE data)\
{										\
   	return  NAME ## _link_front(l, NAME ## _new(data));\
}                                       \
										\
NAME    *NAME ## _link(NAME **l, NAME *i)\
{										\
    NAME *last;							\
    NAME *prev;							\
										\
	(void)	prev;                       \
    prev = 0;                           \
    last = *l;							\
    while (last)						\
    {									\
        if (!last->next)				\
            break ;                     \
        prev = last;                    \
        last = last->next;				\
    }	                                \
    if (!last)							\
    {                                   \
		i->prev = 0;					\
        return *l = i;					\
    }                                   \
    last->next = i; 					\
    last->next->prev = last;            \
                                        \
    return last->next;                  \
                                        \
}                                       \
										\
NAME    *NAME ## _link_front(NAME **l, NAME *i)\
{										\
    NAME *first;						\
    NAME *next;							\
										\
	(void)	next;                       \
    next = 0;                           \
    first = *l;							\
    while (first)						\
    {									\
        if (!first->prev)				\
            break ;                     \
        next = first;                    \
        first = first->prev;			\
    }	                                \
    if (!first)							\
    {                                   \
		i->next = 0;					\
        return *l = i;					\
    }                                   \
    first->prev = i; 					\
    first->prev->next = first;          \
                                        \
    return first->prev;                 \
                                        \
}                                       \
										\
void   NAME ## _del(NAME **l, NAME *k)  \
{										\
    NAME    *it;						\
    NAME    *swp;						\
    NAME    **prev;						\
										\
    it = *l;							\
    prev = l;							\
    while (it)							\
    {									\
        swp = it->next;					\
        if (it == k)					\
        {								\
            if (FREEF)		            \
                (FREEF)(it->data);		\
            free(it);					\
            *prev = swp;				\
        }								\
        it = swp;						\
        if (it)							\
            prev = &(it->next);			\
    }									\
}										\
										\
void    NAME ## _free(NAME *l)\
{										\
    NAME    *it;						\
    NAME    *swp;						\
										\
    it = l;								\
    while (it)							\
    {									\
        swp = it->next;					\
        if (FREEF)			            \
                (FREEF)(it->data);	\
        free(it);						\
        it = swp;						\
    }									\
}										\
                                        \
NAME    * NAME ## _clone(NAME *l)\
{										\
    NAME    *it;						\
    NAME    *out = 0;					\
										\
    it = l;								\
    while (it)							\
    {									\
		if (CLONEF)						\
			NAME ## _add(&out, CLONEF(it->data));\
		else							\
			NAME ## _add(&out, it->data);\
        it = it->next;					\
    }									\
    return out;                         \
}
#endif
