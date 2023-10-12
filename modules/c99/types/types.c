#include "types.h"

/*
	STANDARD C99 TYPESS
*/
char	*types[][5] = {
	// CHAR
	{"unsigned", 	"char", 							0},
	{"signed", 		"char", 							0},
	{				"char",								0},

	// INT
	{"unsigned", 	"long", 				"int",		0},
	{"unsigned", 	"long", 	"long", 	"int",		0},
	{"unsigned", 	"short", 				"int", 		0},
	{"unsigned",							"int",		0},

	{"signed", 		"long", 	"long", 	"int",		0},
	{"signed", 		"short", 				"int", 		0},
	{"signed", 		"long", 				"int",		0},
	{"signed",								"int",		0},

	{				"long",		"long", 	"int",		0},
	{				"long", 				"int",		0},
	{				"short", 				"int",		0},
	{										"int",		0},

	// IMPLICIT INT
	{				"long", 	"long",					0},
	{				"long",								0},
	{				"short",							0},

	{"signed", 		"long", 	"long",					0},
	{"signed", 		"long",								0},
	{"signed", 		"short",							0},
	{"signed",											0},

	{"unsigned", 	"long", 	"long",					0},
	{"unsigned", 	"long",								0},
	{"unsigned", 	"short",							0},
	{"unsigned",										0},

	// FLOAT
	{"long", 		"double",							0},
	{				"double",							0},
	{				"float",							0},

	// BOOL
	{				"_Bool",							0},

	// COMPLEX
	{"long", 		"double", 	"_Complex",				0},
	{				"double", 	"_Complex",				0},
	{				"float", 	"_Complex",				0},
	{							"_Complex",				0},
};

#include "./../c99.h"


int matches_type(char **type, ast_list *l) {
    int i = 0;
	printf("-\n");
    while (type[i] && l) {
		if (!(ast_type(l) == IDENTIFIER && !strcmp(type[i], ast_source(l))))
			return 0;
		printf("ok = %s %s\n", type[i], ast_source(l));
        l = ast_prev(l);
        i++;
    }
	//printf("end on %s\n", ast_source(l));
	if (type[i] || l)
		return 0;
    return i;
}

void	replace_ast_node_with_type(ast_list *l, char **types)
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
				printf("%i\n", r);
		        // replace the AST node's identifier with the type and set its type
                // assuming there's a function or method called 'replace_ast_node_with_type'
                replace_ast_node_with_type(l, types[i]);
				printf("match ! %p\n", ast_next(l));

			//	exit(0);
				return NEXT_PREPROCESSOR;
            }
        }
    }
    return NEXT_PREPROCESSOR;
}
