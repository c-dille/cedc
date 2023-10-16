#ifndef PARSER_H
# define PARSER_H
# include "ast.h"

typedef enum
{
    NEXT_SYNTAX = -2,
	PARSE_NEW_LINE = -1,
    STOP_PARSER = 0,
    PARSE_NEXT_CHAR = 1,
}   parser_action;
typedef struct s_cedilla_context cedilla_context;
typedef parser_action(*parser)(cedilla_context *ctx, const char *fmt, ast_list *ast);
DEF_KLIST_PROTO(parser, parser_klist);
DEF_KLIST(parser, parser_klist, free, ((void*(*)(void*))0));

void parse_info(cedilla_context *ctx, const char *msg, ...);
void parse_error(cedilla_context *ctx, const char *msg, ...);

typedef struct s_preprocessor_klist preprocessor_klist;
//typedef struct s_object_klist object_klist;

struct s_cedilla_context
{
	ull						collumn; // only used for parse error, rest may feeded to gcc #line
	ull						line;
	ull 					depth;
	const char				*file_path;
	const char 				*begin_ptr;
	const char				*end_ptr;
	parser_klist			*parsers;
	object					data;
	preprocessor_klist		*preprocessors;

	// TODO: compiler_klist
};


void parse_info(cedilla_context *ctx, const char *msg, ...) {
	va_list	ap;
	printf("Parse info in %s:%llu:%llu: ", ctx->file_path, ctx->line, ctx->collumn);
	va_start(ap, msg);
	vprintf(msg, ap);
	printf("\n");
	va_end(ap);
}

void parse_error(cedilla_context *ctx, const char *msg, ...) {
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



ast_list *ast_list_root(ast_list *root)
{
	return ast_list_new((ast_node) {
		.type = "ROOT",
		.source = 0,
		.data = {0, 0, 0, 0, 0},
		.parent = root,
		.childs = 0
	});
}

ast_list *ast_push(ast_list *ast, const char *type, char *source)
{
	ast_list *l = ast_list_add(&ast, (ast_node) {
		.type = type,
		.source = source,
		.data = {0, 0, 0, 0, 0},
		.parent = ast->data.parent,
		.childs = 0
	});
	l->data.childs = ast_list_root(l);
	return l;
}

int ast_check_deref(ast_list *ast, const char *file, int line, const char *func)
{
	if (!ast)
		ast_error("Trying to access parent from a null ast ptr.", file, line, func);
	return 0;
}

#define ast_parent(ast)	(ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->data.parent)
#define ast_type(ast) 	(ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->data.type)
#define ast_source(ast) (ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->data.source)
#define ast_childs(ast) (ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->data.childs)
#define ast_next(ast) (ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->next)
#define ast_prev(ast) (ast_check_deref(ast, __FILE__, __LINE__, __FUNCTION__) + ast->prev)

#include "preprocessor.h"

const ull max_depth = 20;

ull   parse(cedilla_context *ctx, const char *fmt, ast_list *out)
{
	parser_action 	pa;
	parser_klist	*it;

	it = NULL;
	if (ctx->depth > max_depth)
		parse_error(ctx, "stack error, depth exceed maximum of : %llu\n", max_depth);
	if (!ctx->parsers)
		parse_error(ctx, "argument error, can not proceed without a parser list.\n");
	if (fmt > ctx->end_ptr || fmt < ctx->begin_ptr)
		parse_error(ctx, "overlapsing (grade A), one of ast parser (%s) returned an invalid length, which exceed format memory area.", "it->data->key ???");
	//ctx->collumn += 1;
	ull oj_depth =  ctx->depth;
	const char *begin_fmt_ptr = fmt;
	ctx->begin_ptr = fmt;
	ctx->depth += 1;

	pa = STOP_PARSER;
	while (*fmt)
	{
		pa = STOP_PARSER;
		it = ctx->parsers;
		while (it && *fmt)
		{
			pa = it->data->value(ctx, fmt, out);

			if (pa == STOP_PARSER)
				break;
			else if (pa == NEXT_SYNTAX)
				;
			else if (pa == PARSE_NEW_LINE)
			{
				fmt += 1;
				ctx->line += 1;
				ctx->collumn = 1;
				break ;
			}
			else
			{
				fmt += pa;
				if (pa == PARSE_NEXT_CHAR)
					ctx->collumn += 1;
				break ;
			}
			it = it->next;
		}
		if (fmt > ctx->end_ptr || fmt < ctx->begin_ptr)
			parse_error(ctx, "overlapsing (grade B), one of ast parser (%s) returned an invalid length, which exceed format memory area.", it->data->key);
		if (pa == STOP_PARSER)
			break;
		if (pa && !it)
			parse_error(ctx, "unknow syntax [%.7s...].", fmt);
		//printf("applying preprocessors in... %llu %llu\n", ctx->line, ctx->collumn);
		if (pa != PARSE_NEW_LINE)
		{
			//printf("pa=%i\n", pa);
			preprocess(ctx, ast_list_last(out));
		}
	}
	if (!*fmt && oj_depth)
		parse_error(ctx, "opened pair. depth=%llu [%.10s]", oj_depth, ctx->begin_ptr);
	ull new_len = fmt - begin_fmt_ptr;
	ctx->depth -= 1;



	//printf("PARSED [depth=%llu line=%llu col=%llu] :: [%.*s]\n", ctx->depth, ctx->line, ctx->collumn, (int)new_len, fmt - new_len);
	return (new_len);
}

// TODO : also set line, col and backup and restore original positions
ull   parse_file(cedilla_context *ctx, const char *path, ast_list *out)
{
	char	*src = read_file(path);
	if (!src)
		return 0;
	ctx->begin_ptr = src;
	ctx->end_ptr = src + strlen(src);
	ull len = parse(ctx, src, out);

	free(src);
	return len;
}


#endif


