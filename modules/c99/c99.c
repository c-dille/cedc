#include "c99.h"


DEF(TYPE);
DEF(OP);

#include "types/types.c"

int define_eol(cedilla_context *ctx, const char *src)
{
	(void) ctx;
	(void) src;
	return 1;
}

int define_space(cedilla_context *ctx, const char *src)
{
	(void) ctx;
	(void) src;
	return 1;
}

int	define_comment(cedilla_context *ctx, const char *from, const char *to)
{
	(void) ctx;
	(void) from;
	(void) to;
	return 1;
}

int	define_token(cedilla_context *ctx, const char *type, const char *src)
{
	(void) ctx;
	(void) type;
	(void) src;
	return 1;
}

int	define_token_group(cedilla_context *ctx, const char *type, const char *src)
{
	(void) ctx;
	(void) type;
	(void) src;
	return 1;
}

int	define_token_string(cedilla_context *ctx, const char *type, const char *src)
{
	(void) ctx;
	(void) type;
	(void) src;
	return 1;
}


ast_macro_result	type_prefixing(cedilla_context *ctx, ast_list *l)
{

	(void) ctx;
	// should have a special rturn type for match so that we keep original match size
	ast_macro_result	out = {0, 0};

	out = match(l, TYPE, ANY, TYPE, UNTIL, IDENTIFIER);
	if (out.match_size)
	{
		//...

		return (out);
	}

	return out;
}

int define_macro(cedilla_context *ctx, void *f)
{
	(void) ctx;
	(void) f;
	return 1;
}

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

	define_eol(ctx, "\n");

	define_space(ctx, "\t");
	define_space(ctx, " ");

	define_comment(ctx, "//", 	"\n");
	define_comment(ctx, "/*",	"*/");

	define_token_group(ctx, "{", "}");
	define_token_group(ctx, "(", ")");
	define_token_group(ctx, "[", "]");

	define_token_string(ctx, "\"", "\"");
	define_token_string(ctx, "'", "'");

	define_token(ctx, OP, "+");
	define_token(ctx, OP, "-");
	define_token(ctx, OP, "*");
	define_token(ctx, OP, "/");
	define_token(ctx, OP, "<");
	define_token(ctx, OP, ">");
	define_token(ctx, OP, "=");
	define_token(ctx, OP, "^");
	define_token(ctx, OP, "&");
	define_token(ctx, OP, "%");

	define_token(ctx, TYPE, "signed");
	define_token(ctx, TYPE, "unsigned");
	define_token(ctx, TYPE, "short");
	define_token(ctx, TYPE, "long");
	define_token(ctx, TYPE, "int");
	define_token(ctx, TYPE, "auto");
	define_token(ctx, TYPE, "char");
	define_token(ctx, TYPE, "_Bool");
	define_token(ctx, TYPE, "float");
	define_token(ctx, TYPE, "double");
	define_token(ctx, TYPE, "_Complex");




	define_macro(ctx, type_prefixing);

/*
	ast_define_macro({m(BRACE, name)}, ^ (klist ... ){

		ast_get(name)
		ast_get

		...

		return new ast ...
	});

*/
	return 0;
}
