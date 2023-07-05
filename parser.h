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

ull   parse(parser_context *ctx, parser_list *parsers, const char *fmt, ast_list *out)
{
	parser_action 	pa;
	parser_list		*it;

	static int r = 0;

	if (++r > 5)
	{
		printf("stack error\n");
		exit (0);
	}

	if (!parsers)
	{
		printf("Error, cant proceed without a parser list.\n");
		exit(0);
	}

	ull oj_len = ctx->collumn;
	ull depth =  ctx->depth;
	ctx->depth += 1;
	void *oj_parent = out->data->parent;
	ctx->collumn += 0;

	if (!*fmt)
	{
		printf("ERR\n");
		exit(0);
	}

	while (*fmt)
	{
		pa = STOP;
		it = parsers;
		while (it)
		{

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
		printf("\n\nPARSED :: [%.*s]\n\n", (int)(ctx->collumn - oj_len) , fmt + 1);
		if (!*fmt && depth > 1)
		{
			printf("ERR : unclosed tag.\n");
			exit(0);
		}

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



	//printf("\n\ngot end :: [%s]\n\n", fmt + ctx->collumn - oj_len+  1);
	ull new_len = ctx->collumn - oj_len;
	ctx->collumn = oj_len;
	ctx->depth -= 1;

	if (!*fmt && depth)
	{
		printf("Error, opened tags\n");
		exit(0);
	}

	return (new_len);
}

#endif


