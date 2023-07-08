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
	const char	*file_path;
	const char 	*begin_ptr;
	const char	*end_ptr;
	const char 	*parser_name;
}	parser_context;


void parse_info(parser_context *ctx, const char *msg, ...) {
	va_list	ap;
	printf("Parse info in %s:%llu:%llu: ", ctx->file_path, ctx->line, ctx->collumn);
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void parse_error(parser_context *ctx, const char *msg, ...) {
	va_list	ap;
	printf("Parse error in %s:%llu:%llu: ", ctx->file_path, ctx->line, ctx->collumn);
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
	exit(0);
}

void ast_info(const char *msg, const char *file, int line, const char *func) {
	printf("AST info in %s:%i within %s(...): %s\n", file, line, func, msg);
}

void ast_error(const char *msg, const char *file, int line, const char *func) {
	printf("AST error in %s:%i within %s(...): %s\n", file, line, func, msg);
	exit(0);
}

typedef parser_action(*parser)(parser_context *ctx, const char *fmt, ast_list *ast);
typedef struct
{
	parser		f;
	const char 	*name;
}	named_parser;

DEF_LIST_PROTO(named_parser*, named_parser_list);
DEF_LIST(named_parser*, named_parser_list, 0);
#define alloc_named_parser(n) \
	(ALLOC(named_parser,\
		.name = STR(n),\
		.f = n\
	))\

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

int check_ast_deref(ast_list *ast, int check_data, const char *file, int line, const char *func)
{
	if (!ast)
		ast_error("Trying to access parent from a null ast ptr.", file, line, func);
	if (!ast->data && check_data)
		ast_error("Trying to access parent from a null ast->data ptr.", file, line, func);
	return 0;
}

#define ast_parent(ast)	(check_ast_deref(ast, 1, __FILE__, __LINE__, __FUNCTION__) + ast->data->parent)
#define ast_type(ast) 	(check_ast_deref(ast, 1, __FILE__, __LINE__, __FUNCTION__) + ast->data->type)
#define ast_source(ast) (check_ast_deref(ast, 1, __FILE__, __LINE__, __FUNCTION__) + ast->data->source)
#define ast_childs(ast) (check_ast_deref(ast, 1, __FILE__, __LINE__, __FUNCTION__) + ast->data->childs)
#define ast_next(ast) (check_ast_deref(ast, 0, __FILE__, __LINE__, __FUNCTION__) + ast->next)
#define ast_prev(ast) (check_ast_deref(ast, 0, __FILE__, __LINE__, __FUNCTION__) + ast->prev)

const ull max_depth = 7;

ull   parse(parser_context *ctx, named_parser_list *parsers, const char *fmt, ast_list *out)
{
	parser_action 	pa;
	named_parser_list		*it;


	if (ctx->depth > max_depth)
		parse_error(ctx, "stack error, depth exceed maximum of : %llu\n", max_depth);

	if (!parsers)
		parse_error(ctx, "argument error, can not proceed without a parser list.\n");

	if (fmt > ctx->end_ptr || fmt < ctx->begin_ptr)
		parse_error(ctx, "overlapsing (grade A), one of ast parser (%s) returned an invalid length, which exceed format memory area.", it->data->name);

	ctx->collumn += 1;

	ull oj_line = ctx->line;
	ull oj_collumn = ctx->collumn;
	ull oj_depth =  ctx->depth;

	const char *begi_fmt_ptr = fmt;
	ctx->begin_ptr = fmt;
	ctx->depth += 1;

	//printf("[new parsing %.5s]\n", fmt);

	pa = STOP;

	while (*fmt)
	{
		pa = STOP;
		it = parsers;
		while (it && *fmt)
		{
			ctx->parser_name = it->data->name;
			pa = it->data->f(ctx, fmt, out);

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
		if (fmt > ctx->end_ptr || fmt < ctx->begin_ptr)
			parse_error(ctx, "overlapsing (grade B), one of ast parser (%s) returned an invalid length, which exceed format memory area.", it->data->name);

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
			parse_error(ctx, "unknow syntax [%.7s...].", fmt);

	}

/*
	if (pa == STOP && ctx->depth == 1)
	{
		printf("Error, opened tag\n");
		exit(0);
	}
*/

	if (!*fmt && oj_depth)
		parse_error(ctx, "opened pair.");

	ull new_len = fmt - begi_fmt_ptr;
	ctx->depth -= 1;
	ctx->collumn = oj_collumn;
	ctx->line = oj_line;

	printf("PARSED [depth=%llu] :: [%.*s]\n", ctx->depth, (int)new_len, fmt - new_len);

	ctx->collumn -= 1;

	return (new_len);
}

#endif


