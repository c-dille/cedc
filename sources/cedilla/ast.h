#ifndef AST_MACRO_H
# define AST_MACRO_H
# include "./../macros.h"
# include "./../object/object_klist.h"

typedef struct s_ast_node ast_node;
typedef struct s_ast_list ast_list;
typedef struct  s_ast_node
{
    const char      *type;			// string object
    char      		*source;		// static string object OOORRR no need ...  because easier to read without for no sens
	object_klist	*objects;
	ast_list 		*parent;		// ast list object ?
	ast_list		*childs;		// ast list object ?
}   ast_node;
DEF_LIST_PROTO(ast_node, ast_list);
void ast_free_node(ast_node );
DEF_LIST(ast_node, ast_list, ast_free_node);
								// def ast_list_object ?
void ast_free_node(ast_node node)
{
	ast_list_free(node.childs);
	object_klist_free(node.objects);
	if (node.source)
		free((void*)node.source);
}

ast_list *ast_list_vnew(ull i, ...)
{
	ast_list	*r = 0;
	va_list		ap;
	va_start(ap, i);
	while (i)
	{
		ast_node n = va_arg(ap, ast_node);
		ast_list_add(&r, (ast_node) {.type = n.type, .source = n.source, .objects=0, .childs = n.childs});
		i -= 1;
	}
	va_end(ap);
	return (r);
}

void ast_set_parent(ast_list *l, ast_list *parent)
{
	ast_list *it = l;
	while (it)
	{
		it->data.parent = parent;
		ast_set_parent(it->data.childs, it);
		it = it->next;
	}
}

void ast_dump_helper(ast_list *l, int depth)
{
	ast_list *it = l;

	if (!l)
	{
		printf("0\n");
		return ;
	}
	printf("ast_list_vnew(%llu, \n", ast_list_count(l));
	while (l)
	{
		printf("%*s(ast_node) {\n", (depth + 1) * 4, "");
		printf("%*s.type = \"%s\",\n", (depth + 2) * 4, "", l->data.type);
		if (l->data.source)
			printf("%*s.source = strdup(\"%s\"),\n", (depth + 2) * 4, "", l->data.source);
		else
			printf("%*s.source = 0,\n", (depth + 2) * 4, "");
		printf("%*s.childs = ", (depth + 2) * 4, "");
		ast_dump_helper(l->data.childs, depth + 2);
		printf("%*s}", (depth + 1) * 4, "");
		if (l->next)
			printf(",");
		printf("\n");
		l = l->next;
	}
	printf("%*s)\n", (depth) * 4, "");
}

void ast_dump(ast_list *l)
{
	printf("ast_set_parent(");
	ast_dump_helper(l, 1);
	printf(");\n");
}

#endif
