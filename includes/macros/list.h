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
NAME    *NAME ## _add(NAME **l, TYPE data);\
NAME    *NAME ## _link(NAME **l, NAME *i);\
void    NAME ## _del(NAME **l, NAME *k);\
void    NAME ## _free(NAME *l);         \
NAME    *NAME ## _clone(NAME    *, TYPE (*)(TYPE));		\

# define DEF_LIST(TYPE, NAME, FREEF)	\
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
    NAME *last;							\
    NAME *prev;							\
                                        \
	(void)	prev;						\
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
        return *l = NAME ## _new(data);	\
    }                                   \
    last->next = NAME ## _new(data);    \
    last->next->prev = last;            \
                                        \
    return last->next;                  \
                                        \
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
void    NAME ## _free(NAME *l)          \
{										\
    NAME    *it;						\
    NAME    *swp;						\
										\
    it = l;								\
    while (it)							\
    {									\
        swp = it->next;					\
        if (FREEF)			            \
                (FREEF)(it->data);		\
        free(it);						\
        it = swp;						\
    }									\
}										\
                                        \
NAME    * NAME ## _clone(NAME *l, TYPE (*clone)(TYPE))\
{										\
    NAME    *it;						\
    NAME    *out = 0;					\
										\
	(void) clone;						\
    it = l;								\
    while (it)							\
    {									\
		NAME ## _add(&out, it->data);	\
        it = it->next;					\
    }									\
    return out;                         \
}
#endif
