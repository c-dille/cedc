#ifndef COMPILER_H
# define COMPILER_H
# include "cedilla.h"

typedef enum
{
	RESTART_COMPILER = -1,
	STOP_COMPILER = 0,
	NEXT_COMPILER = 1
}	compiler_action;
typedef const char *(*compiler)(cedilla_context *ctx, ast_list *l);

DEF_KLIST_PROTO(compiler, compiler_list)
DEF_KLIST(compiler, compiler_list, free, ((void*(*)(void*))0))

/*
bool compile(cedilla_context *ctx, ast_list *l)
{
	compiler_list	*it = ctx->compilers;
	int	depth = 0;
	while (it)
	{
		if (depth++ > 25)
			parse_error(ctx, "depth exceed while running macro name '%s'.", it->data->key);
		compiler_action pa = it->data->value(ctx, l);

		if (pa == RESTART_COMPILER)
		{
			it = ctx->compilers;
			continue;
		}
		if (!pa)
			break ;

		it = it->next;
	}
	return false;
}
*/

#endif
