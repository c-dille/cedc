#ifndef AST_MACRO_H
# define AST_MACRO_H
# include "tools.h"

typedef struct s_ast_node ast_node;
DEF_LIST_PROTO(ast_node*, ast_list);
DEF_LIST(ast_node*, ast_list, 0);
typedef struct  s_ast_node
{
    const char      *type;
    const char      *source;
	ast_list 		*parent;
	ast_list		*childs;
}   ast_node;
// todo : implement a function to set parent to all childs
#endif
