#ifndef MACRO_H
# define MACRO_H
# include "parser.h"

typedef struct
{
	void	*ptr;
	void	(*free)(void*);
	void	*(*clone)(void*);
}	object;
DEF_KLIST_PROTO(object, object_list);
void	free_object_list(object_list_entry *l)
{
	if (l->value.free)
		l->value.free(l->value.ptr);
	free(l);
}
DEF_KLIST(object, object_list, free_object_list);

typedef enum
{
	RESTART_PREPROCESSOR = -1,
	STOP_PREPROCESSOR = 0,
	NEXT_MACRO = 1
}	preprocessor_action;
typedef preprocessor_action (*macro)(parser_context *, ast_list *);
DEF_KLIST_PROTO(macro, macro_list)
DEF_KLIST(macro, macro_list, free)



bool preprocess(parser_context *ctx, ast_list *l)
{
	macro_list	*it = ctx->macros;
	int	depth = 0;
	while (it)
	{
		if (depth++ > 25)
			parse_error(ctx, "depth exceed while running macro name '%s'.", it->data->key);
		preprocessor_action pa = it->data->value(ctx, l);

		if (pa == RESTART_PREPROCESSOR)
			it = ctx->macros;

		if (!pa)
			break ;

		it = it->next;
	}
	return false;
}

#endif
