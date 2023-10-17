#include "c99.h"


DEF(TYPE);
DEF(OP);

#include "types/types.c"

typedef struct s_lpstr
{
	size_t	len;
	char	*str;
} lpstr;

lpstr	lp(char *str)
{
	return ((lpstr){strlen(str), str});
}

void	lpstr_free(lpstr str)
{
	str.len = 0;
	free(str.str);
}

lpstr	lpstr_clone(lpstr str)
{
	return (lpstr){.len = str.len, .str = strdup(str.str)};
}

DEF_LIST_PROTO(lpstr, lpstr_list);
DEF_LIST(lpstr, lpstr_list, lpstr_free, lpstr_clone);

bool	lpstr_begins_with(lpstr haystack, const char *needle)
{
	return (!strncmp(haystack.str, needle, haystack.len));
}

typedef struct s_token_representation
{
	union
	{
		lpstr		token;
		lpstr		to;
	};
	lpstr		to;
	const char 	*type;
	bool		until_unescaped;
}	token_representation;

DEF_LIST_PROTO(token_representation, token_representation_list);
DEF_LIST(token_representation, token_representation_list, 0, 0);

lpstr_list 	*g_tokens = 0;

parser_action  token(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	token_representation_list	*it;

	it = g_tokens;
	while (it)
	{
		it = it->next;
	}
	if ((len = lpstr_list_contains_begin(g_eols, fmt)))
	{
		(void) len;
		// todo : handle lines longer than one
		return PARSE_NEW_LINE;
	}
	return NEXT_SYNTAX;
}

DEF(EOL)
token_representation_list *define_eol(cedilla_context *ctx, const char *src)
{
	return token_representation_list_add(g_tokens, (token_representation){
		.token = {.str = src, .len = strlen(src)},
		.to = {.len = 0},
		.type = EOL,
		.until_escaped = false
	});
	return 1;
}

int define_space(cedilla_context *ctx, const char *src)
{
	(void) ctx;
	str_list_add(g_spaces, strdup(src));
	return 1;
}

parser_action   space(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	lpstr_list	*it;
	size_t len;

	if ((len = lpstr_list_contains_begin(g_eols, fmt)))
	{
		// todo : handle lines longer than one
		return len;
	}
	return NEXT_SYNTAX;
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
