#ifndef PARSER_H
# define PARSER_H
# include "ast.h"
typedef enum
{
    NEXT_SYNTAX = -2,
	NEW_LINE = -1,
    STOP = 0,
    NEXT_CHAR = 1,
}   parser_action;

typedef struct
{
	ull			collumn; // only used for parse error, rest may feeded to gcc #line
	ull			line;
	ull 		depth;
	const char	*file_name;
	const char 	*begin_ptr;
	const char	*end_ptr;
}	parser_context;
typedef parser_action(*parser)(parser_context *ctx, const char *fmt, ast_list *ast);
DEF_LIST_PROTO(parser, parser_list);
DEF_LIST(parser, parser_list, 0);


ast_list *ast_list_root(ast_list *root)
{
	return ast_list_new(ALLOC(ast_node,
		.type = "ROOT",
		.parent = root,
		.childs = 0
	));
}

ast_list *ast_push(ast_list *ast, const char *type, const char *source)
{
	ast_list *l = ast_list_add(&ast, ALLOC(ast_node,
		.type = type,
		.source = source,
		.parent = ast->data->parent
	));
	l->data->childs = ast_list_root(l);
	return l;
}

void check_ast_err(ast_list *ast, int check_data)
{
	if (!ast)
	{
		printf("Trying to access parent from a null ast ptr.\n");
		exit(0);
	}

	if (!ast->data && check_data)
	{
		printf("Trying to access parent from a null ast->data ptr.");
		exit (0);
	}
}

#define ast_parent(ast) (_ast_parent(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
ast_list *_ast_parent(parser_context *ctx, ast_list *ast, const char * func, const char * file, ull line)
{

	check_ast_err(ast, 1);
	return ast->data->parent;
}

#define ast_type(ast) (_ast_type(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
const char *_ast_type(parser_context *ctx, ast_list *ast, const char * func, const char * file, ull line)
{
	check_ast_err(ast, 1);
	return ast->data->type;
}

#define ast_source(ast) (_ast_source(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
const char *_ast_source(parser_context *ctx, ast_list *ast, const char * func, const char * file, ull line)
{
	check_ast_err(ast, 1);
	return ast->data->source;
}

#define ast_childs(ast) (_ast_childs(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
ast_list *_ast_childs(parser_context *ctx, ast_list *ast, const char * func, const char * file, ull line)
{
	check_ast_err(ast, 0);
	return ast->data->childs;
}

#define ast_next(ast) (_ast_next(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
ast_list *_ast_next(parser_context *ctx, ast_list *ast, ull func, ull file, ull line)
{
	check_ast_err(ast, 0);
	return ast->next;
}

#define ast_prev(ast) (_ast_prev(ctx, ast, __FUNCTION__, __FILE__, __LINE__))
ast_list *_ast_prev(parser_context *ctx, ast_list *ast, ull func, ull file, ull line)
{
	check_ast_err(ast, 0);
	return ast->next;
}

ull   parse(parser_context *ctx, parser_list *parsers, const char *fmt, ast_list *out)
{
	parser_action 	pa;
	parser_list		*it;


	if (ctx->depth > 5)
	{
		printf("stack error\n");
		exit (0);
	}

	if (!parsers)
	{
		printf("Error, cant proceed without a parser list.\n");
		exit(0);
	}

	ull oj_line = ctx->line;
	ull oj_collumn = ctx->collumn;
	ull oj_depth =  ctx->depth;

	const char *begi_fmt_ptr = fmt;
	ctx->begin_ptr = fmt;
	ctx->depth += 1;

	printf("[new parsing %.5s]\n", fmt);

	pa = STOP;

	while (*fmt)
	{
		pa = STOP;
		it = parsers;
		while (it && *fmt)
		{
			if (fmt > ctx->end_ptr || fmt < ctx->begin_ptr)
			{
				printf("Overlapping detected for fmt !! [%s] [%llu]\n", fmt - 3, ctx->depth);
				exit(0);
			}

			pa = it->data(ctx, fmt, out);

			if (pa == STOP)
			{
			//	fmt += 1;
			// 	ctx->collumn += 1;
				break;
			}
			else if (pa == NEXT_SYNTAX)
				;
			else if (pa == NEW_LINE)
			{
				fmt += 1;
				ctx->line += 1;
				ctx->collumn = 1;
				break ;
			}
			else
			{
				fmt += pa;
				ctx->collumn += pa;
				break ;
			}
			it = it->next;
		}
		/*
		if (pa == STOP && !fmt[1] && depth > 1)
		{
			printf("ERR : unclosed tag.\n");
			exit(0);
		}*/

		if (pa == STOP)// || pa == NEXT_SYNTAX)
		{
		//	printf("stop woth %llu\n", ctx->depth);
		//	fmt += 1;
			break;
		}
		if (pa && !it)
		{
			printf("Parse error in file  %s:%llu:%llu [%.8s...] with depth=%llu\n", ctx->file_name, ctx->line, ctx->collumn, fmt, ctx->depth);
			exit (0);
		}
	}

/*
	if (pa == STOP && ctx->depth == 1)
	{
		printf("Error, opened tag\n");
		exit(0);
	}*/


/*
	if (!*fmt && oj_depth)
	{
		printf("Error, opened tags\n");
		exit(0);
	}*/

	ull new_len = fmt - begi_fmt_ptr;
	ctx->depth -= 1;
	ctx->collumn = oj_collumn;
	ctx->line = oj_line;

	printf("\n\nPARSED [depth=%llu] :: [%.*s]\n\n", ctx->depth, new_len, fmt - new_len);


	return (new_len);
}

#endif


