#ifndef KLIST_H
# define KLIST_H
# include "list.h"
# define DEF_KLIST_PROTO(TYPE, NAME)        \
                                            \
typedef struct s_##NAME##_entry     {       \
    const char  *key;                       \
    TYPE        value;                      \
} NAME##_entry;                             \
                                            \
DEF_LIST_PROTO(NAME##_entry*, NAME);        \
                                            \
int     NAME ##_set(NAME **map, const char *key, TYPE value);\
TYPE    NAME ##_get(NAME *map, const char *key);\

# define DEF_KLIST(TYPE, NAME, FREEF)       \
                                            \
DEF_LIST(NAME##_entry*, NAME, FREEF)        \
                                            \
int         NAME ## _isset(NAME **map, const char *key)\
{                                           \
    NAME    *l;                             \
                                            \
    l = *map;                               \
    while (l)                               \
    {                                       \
        if (!strcmp(l->data->key, key))     \
            return 1;                       \
        l = l->next;                        \
    }                                       \
    return 0;                               \
}											\
int         NAME ## _set(NAME **map, const char *key, TYPE value)\
{                                           \
    NAME    *l;                             \
                                            \
    l = *map;                               \
    while (l)                               \
    {                                       \
        if (!strcmp(l->data->key, key))     \
        {                                   \
            l->data->value = value;         \
            return 1;                       \
        }                                   \
        l = l->next;                        \
    }                                       \
    NAME##_add(map, ALLOC(NAME ## _entry, .key=key, .value=value));\
    return 0;                               \
}                                           \
                                            \
TYPE    NAME##_get(NAME *map, const char *key)\
{                                           \
    NAME    *l;                             \
                                            \
    l = map;                                \
    while (l)                               \
    {                                       \
        if (!strcmp(l->data->key, key))     \
            return l->data->value;          \
        l = l->next;                        \
    }										\
	printf("Error, trying to get an unknow key %s in %s:%u\n", key, __FILE__, __LINE__);\
	exit(0);								\
    return l->data->value;          		\
}

#endif
