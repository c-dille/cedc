#ifndef AST_MACRO_H
# define AST_MACRO_H
# include "ft.h"

typedef struct s_ast_node ast_node;
DEF_LIST_PROTO(ast_node*, ast_list);
void ast_free_node(ast_node *);
DEF_LIST(ast_node*, ast_list, ast_free_node);
typedef struct  s_ast_node
{
    const char      *type;
    char      		*source;
	ast_list 		*parent;
	ast_list		*childs;
}   ast_node;

void ast_free_node(ast_node *node)
{
	ast_list_free(node->childs);
	if (node->source)
		free((void*)node->source);
	free(node);
}

void ast_dump_helper(ast_list *l, int depth)
{
	ast_list *it = l;


	if (!l)
	{
		printf("0\n");
		return ;
	}
	printf("ast_list_vnew(\n");
	while (l)
	{
		printf("%*s(ast_node) {\n", (depth + 1) * 4, "");
		printf("%*s.type = \"%s\",\n", (depth + 2) * 4, "", l->data->type);
		printf("%*s.source = \"%s\",\n", (depth + 2) * 4, "", l->data->source);
		printf("%*s.childs = ", (depth + 2) * 4, "");
		ast_dump_helper(l->data->childs, depth + 2);
		printf("%*s}", (depth + 1) * 4, "");
		if (l->next)
			printf(",");
		printf("\n");
		l = l->next;
	}
	printf("%*s)\n", (depth) * 4, "");
}

#include "stdarg.h"

#define COUNT_ARGS(...) COUNT_ARGS_HELPER(__VA_ARGS__, COUNT_ARGS_SEQ())

#define COUNT_ARGS_HELPER(...) COUNT_ARGS_IMPL(__VA_ARGS__)

#define COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, count, ...) count

#define COUNT_ARGS_SEQ() \
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, \
    34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1

#define ast_list_vnew(...) _ast_list_vnew(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
ast_list *_ast_list_vnew(int n, ...)
{
	ast_list	*r = 0;

	va_list		ap;
	int 		i = 0;

	va_start(ap, n);

	while (i < n)
	{
		ast_node n = va_arg(ap, ast_node);
		ast_list_add(&r, ALLOC(ast_node, .type = n.type, .source = n.source, .childs = 0));
		i += 1;
	}

	va_end(ap);
	return (r);
}

void ast_dump(ast_list *l)
{
	ast_dump_helper(l, 0);
}

#endif
