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

#endif
