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

// TODO :: ad enum for TYPES, add a 'closed' state to nodes, when closing tag : check if all parent are already closed or not, add a way to parse childs more easly

typedef struct
{
	ULL			collumn; // only used for parse error, rest may feeded to gcc #line
	ULL			line;
	ULL 		deep;
	const char	*file_name;
	ast_list	*parent;
}	parser_context;
typedef parser_action(*parser)(parser_context *ctx, ast_list **ast, const char *fmt);
DEF_LIST_PROTO(parser, parser_list);
DEF_LIST(parser, parser_list, 0);




ast_list   *parse(parser_context *ctx, parser_list *parsers, const char *fmt, ast_list *parent)
{
	ast_list 		*out;
	parser_action 	pa;
	parser_list		*it;

	static int r = 0;

	if (++r > 5)
	{
		printf("stack error\n");
		exit (0);
	}


	out = 0;
	while (*fmt)
	{
		pa = STOP;
		it = parsers;
		while (it)
		{

			pa = it->data(ctx, &out, fmt);
			if (pa == STOP)
			{
		//		fmt += 1;
			//	ctx->collumn += pa + 1;
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
		if (pa == STOP)// || pa == NEXT_SYNTAX)
		{
			printf("stop woth %i\n", ctx->deep);
		//	fmt += 1;
			break;
		}
		if (pa && !it)
		{
			printf("ERROR, UNKNOW SYNTAX [%s...]!\n", fmt);
			exit (0);
		}
	}
	/*if (!*fmt && ctx->deep <= 1)
	{
		printf("Parse error, unclosed tag \n");
		exit(0);
	}*/
	if (*fmt && !ctx->deep)
			printf("Parse error in file  %s:%llu:%llu [%.8s...] with depth=%i\n", ctx->file_name, ctx->line, ctx->collumn, fmt, ctx->deep);


	return (out);
}

#endif
