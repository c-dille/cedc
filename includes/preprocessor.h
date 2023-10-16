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
DEF_KLIST(macro, preprocessor_klist, free, strdup)


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


DEF(ANY)
DEF(UNTIL)
DEF(NOT)

typedef struct s_ast_macro_result
{
	int			match_size;

	ast_list	*l;
}	ast_macro_result;

ast_macro_result	_match(cedilla_context *ctx, ast_list *l, ...)
{
	ast_macro_result	out = {0, 0};
	va_list				ap;
	const char			*str;

	va_start(ap, l);
	while ((str = va_arg(ap, const char*)))
	{
		if (str == UNTIL)
		{
			str = va_arg(ap, const char *);

			if (!str)
			{
				// ? no end condition ?
			}

			str = va_arg(ap, const char *);
			if (str == NOT)
			{

			}

			// ...

			while (l && ast_type(l) != str)
			{
				out.match_size += 1;
				l = l->prev;
			}
			if (!l && ast_type(l) != str)
			{
				// error
			}
			return	(ast_macro_result) {0, 0};
		}
		else if (str == NOT)
		{
			str = va_arg(ap, const char *);
			if (str && ast_type(l) != str)
				out.match_size += 1;
			else
				return	(ast_macro_result) {0, 0};
		}
		else if (str == ANY || ast_type(l) == str)
			out.match_size += 1;
		else
			return	(ast_macro_result) {0, 0};
		l = l->prev;
	}
	va_end(ap);

	int	match_size = out.match_size;
	while (match_size--)
		ast_list_add_front(&(out.l), ast_node_clone(l->data));
	return out;
}
#define match(...) _match(__VA_ARGS__, 0);

#endif
