#include "c99.h"

/*
typedef struct s_module
{
	char 		*name;
	float		version;

	struct s_module	dependancies[];
}	module;

module c99 = {
	"c99",
	0.1,
	.dependancies = {
		{"preprocessor", 0.2},

	},
	"cc -Wall -Werror -Wextra"
};
*/

#include "types/types.c"

int	load_module(cedilla_context *ctx)
{
	print("Loading c99 module... ");



	parser_klist_set(&(ctx->parsers), KV(space));
	parser_klist_set(&(ctx->parsers), KV(identifier));
	parser_klist_set(&(ctx->parsers), KV(operator));
	parser_klist_set(&(ctx->parsers), KV(quote));
	parser_klist_set(&(ctx->parsers), KV(dquote));
	parser_klist_set(&(ctx->parsers), KV(comment));
	parser_klist_set(&(ctx->parsers), KV(mlcomment));

	parser_klist_set(&(ctx->parsers), KV(brace));
	parser_klist_set(&(ctx->parsers), KV(parenthesis));
	parser_klist_set(&(ctx->parsers), KV(bracket));

	parser_klist_set(&(ctx->parsers), KV(endbrace));
	parser_klist_set(&(ctx->parsers), KV(endparenthesis));
	parser_klist_set(&(ctx->parsers), KV(endbracket));

	preprocessor_klist_set(&(ctx->preprocessors), KV(is_type));

	printf("done. \n");

	return 0;
}
