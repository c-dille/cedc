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

ast_list *ast_list_vnew(ast_node first, ...)
{
	ast_list	*r;


	return (r);
}

void ast_dump(ast_list *l)
{
	ast_dump_helper(l, 0);
}

#endif
