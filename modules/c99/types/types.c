#include "types.h"

DEF(TYPE)

typedef struct {
	int	len;
	char *arr[5];
} c_primitive_types;

/*
	STANDARD C99 TYPESS
*/
c_primitive_types	types[] = {
	// CHAR
	{2, {"unsigned", 	"char"}},
	{2, {"signed",		"char"}},
	{1, { 				"char"}},

	// INT
	{4, {"unsigned",	"long",		"long", 	"int"}},
	{3, {"unsigned",	"long",		"int"}},
	{3, {"unsigned",	"short",	"int"}},
	{2, {"unsigned",	"int"}},

	{4, {"signed",		"long",		"long", 	"int"}},
	{3, {"signed",		"long",		"int"}},
	{3, {"signed",		"short",	"int"}},
	{2, {"signed",		"int"}},

	{3, {"long",		"long", 	"int"}},
	{2, {"long",		"int"}},
	{2, {"short",		"int"}},
	{1, {"int"}},

	// IMPLICIT INT
	{3, {"unsigned",	"long",		"long"}},
	{2, {"unsigned",	"long"}},
	{2, {"unsigned",	"short"}},
	{1, {"unsigned"}},

	{3, {"signed",		"long",		"long"}},
	{2, {"signed",		"long"}},
	{2, {"signed",		"short"}},
	{1, {"signed"}},

	{2, {"long",		"long"}},
	{1, {"long"}},
	{1, {"short"}},

	// FLOAT
	{2, {"long",		"double"}},
	{1, {"double"}},
	{1, {"float"}},

	// BOOL
	{1,	{"_Bool"}},

	// COMPLEX
	{3, {"long", 		"double", 	"_Complex"}},
	{2, {"double", 		"_Complex"}},
	{2, {"float", 		"_Complex"}},
	{1, {"_Complex"}},
};

#include "./../c99.h"

int matches_type(c_primitive_types type, ast_list *l) {
	int	type_len = type.len;
	if (!type_len)
		return 0;
	int i = type_len - 1;
    while (i >= 0 && l) {
		if (!(ast_type(l) == IDENTIFIER && !strcmp(type.arr[i], ast_source(l))))
		{
			if (!strcmp(type.arr[type_len - 1], "long"))
			printf("no! %s == ID? %s == %s ? prev=%s\n", ast_type(l), type.arr[i], ast_source(l), ast_source(ast_prev(l)));
			return 0;
		}
        l = ast_prev(l);
        i -= 1;
    }
 	printf("%i\n", i);
	return type_len;
}

void	replace_ast_node_with_type(ast_list *l, c_primitive_types types)
{
	(void) l;
	(void) types;

	return ;
}

preprocessor_action is_type(cedilla_context *ctx, ast_list *l) {
	(void) ctx;
    if (ast_type(l) == IDENTIFIER) {
        for (int i = 0; i < (int)(sizeof(types) / sizeof(types[0])); i++) {
            int r = matches_type(types[i], l);
			if (r) {
				//while (r = )

				printf("%i\n", r);

		        // replace the AST node's identifier with the type and set its type
                // assuming there's a function or method called 'replace_ast_node_with_type'
                replace_ast_node_with_type(l, types[i]);


				if (r > 1)
				{
					printf("match ! [%s] [%s] %s\n",ast_source(ast_prev(ast_prev(l))) , ast_source(ast_prev(l)), ast_source(l));
					exit(0);
				}
			//	if ()
			//	l->data.type = TYPE;

			//	exit(0);
				return NEXT_PREPROCESSOR;
            }
        }
    }
    return NEXT_PREPROCESSOR;
}
