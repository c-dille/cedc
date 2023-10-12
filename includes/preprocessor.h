#ifndef PREPROCESSOR_H
# define PREPROCESSOR_H
# include "parser.h"

typedef enum
{
	RESTART_PREPROCESSOR = -1,
	STOP_PREPROCESSOR = 0,
	NEXT_PREPROCESSOR = 1
}	preprocessor_action;
typedef preprocessor_action (*macro)(cedilla_context *, ast_list *);
DEF_KLIST_PROTO(macro, preprocessor_klist)
DEF_KLIST(macro, preprocessor_klist, free)


/*
*	TODO:
*
*		Perform matches in reverse order in one pass,
*		Or apply preprocessor in a second pass
*/
bool preprocess(cedilla_context *ctx, ast_list *l)
{
	preprocessor_klist	*it = ctx->preprocessors;
	int	depth = 0;
	while (it)
	{
		if (depth++ > 25)
			parse_error(ctx, "depth exceed while running macro name '%s'.", it->data->key);
		preprocessor_action pa = it->data->value(ctx, l);

		if (pa == RESTART_PREPROCESSOR)
		{
			it = ctx->preprocessors;
			continue;
		}
		if (!pa)
			break ;

		it = it->next;
	}
	return false;
}

#endif
