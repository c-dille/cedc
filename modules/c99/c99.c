#include "c99.h"

DEF(RAW)
DEF(SPACE)
DEF(EOL)

DEF(BRACE)
DEF(PARENTHESIS)
DEF(BRACKET)
//DEF(COMMENT)
DEF(OP)
DEF(DQUOTE)
DEF(QUOTE)
DEF(KEYWORD)
DEF(TYPE)

DEF(NUM)
DEF(ID)

DEF(CHAR)

typedef struct
{
	const char	*type;
	lpstr 		token;
}	token_representation;

DEF_LIST_PROTO(token_representation, token_representation_list);
DEF_LIST(token_representation, token_representation_list, 0, 0);

token_representation_list	*g_tokens = 0;

parser_action  token(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) 						ctx;
	size_t 						len;
	token_representation_list	*it;

	it = g_tokens;
	while (it)
	{
		if ((len = lpstr_prefix_str(it->data.token, fmt)))
		{
			if (it->data.type == EOL)
				ctx->is_eol = true;
			else if (it->data.type == SPACE)
				;
			else
				ast_push(ast, it->data.type, strndup(fmt, len));
			return len;
		}
		it = it->next;
	}
	return NEXT_SYNTAX;
}

token_representation_list	*define_token(const char *type, char *str)
{
	return token_representation_list_add(
		&g_tokens,
		(token_representation){ type, lp(str) }
	);
}

bool _define_tokens(const char *type, ...) {
    va_list ap;
    const char *str;

    va_start(ap, type);
    while ((str = va_arg(ap, const char *))) { // const char* as we're expecting a pointer
        if (!define_token(type, (char*)str)) {
            va_end(ap);
            return false;
        }
    }
    va_end(ap);
    return true;
}

#define define_tokens(...) _define_tokens(__VA_ARGS__, NULL) // use NULL, not 0


parser_action   comment(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	(void) ast;
	if (*fmt == '/' && fmt[1] == '/' && ctx->collumn == 1)
	{
		ull len = 0;
		while (fmt && fmt[len] != '\n')
			len   += 1;
		return len;
	}
	return NEXT_SYNTAX;
}

parser_action   mlcomment(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	(void) ast;
	if (fmt[0] == '/' && fmt[1] == '*')
	{
		ull len = 0;
		while (fmt[len] && !(fmt[len] == '*' && fmt[len + 1] == '/'))
			len   += 1;
		if (!fmt[len])
			parse_error(ctx, "unclosed mlcomment.");
		return len + 2;
	}
	return NEXT_SYNTAX;
}

char *findfirstunescaped(const char *str, const char *c)
{
	int i = 0;

	while (str[i])
	{
		if (!strncmp(str + i, c, strlen(c))
			&& (
				!(
				(i >= 1) && (str[i - 1] == '\\')
				)
			|| (
					(i >= 2) && (str[i - 1] == '\\' && str[i - 2] == '\\')
				)
			)
		)
			return (char *)&str[i];
		i += 1;
	}
	return NULL;
}

parser_action   quote(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	if (*fmt == '\'')
	{
		char *lastunescaped = findfirstunescaped(fmt + 1, "'");
		if (!lastunescaped)
			parse_error(ctx, "unclosed quote.");
	//	printf("lastUnesc: [%s\n]", lastunescaped);
		ast_push(ast, CHAR, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 1;
	}
	return NEXT_SYNTAX;
}

parser_action   dquote(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	if (*fmt == '"')
	{
		char *lastunescaped = findfirstunescaped(fmt + 1, "\"");
		if (!lastunescaped)
			parse_error(ctx, "unclosed double quotes.");
	//	printf("lastUnesc: [%s\n]", lastunescaped);
		ast_push(ast, DQUOTE, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 1;
	}
	return NEXT_SYNTAX;
}

// TODO : comment why 2, one for each sybol ?
parser_action   brace(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '{')
	{
		return
			2 + parse(ctx, fmt + 1,
				ast_push(ast, BRACE, strdup("{}"))->data.childs
			);
	}
	return NEXT_SYNTAX;
}

parser_action   endbrace(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '}')
	{
		if (ast_type(ast_parent(ast)) != BRACE)
			parse_error(ctx, "unexpected closing brace.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}

parser_action   parenthesis(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '(')
	{
		return
			2 +
			parse(ctx, fmt + 1,
				ast_push(ast, PARENTHESIS, strdup("()"))->data.childs
			);
	}
	return NEXT_SYNTAX;
}

parser_action   endparenthesis(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ')')
	{
		if (ast_type(ast_parent(ast)) != PARENTHESIS)
			parse_error(ctx, "unexpected closing parenthesis.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}

parser_action   bracket(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '[')
	{
		return
			2 +
			parse(ctx, fmt + 1,
				ast_push(ast, BRACKET, strdup("[]"))->data.childs
			);
	}
	return NEXT_SYNTAX;
}

parser_action   endbracket(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ']')
	{
		// when stopping parser, also increment fmt ...
		if (ast_type(ast_parent(ast)) != BRACKET)
			parse_error(ctx, "unexpected closing bracket.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}


parser_action   identifier(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx; (void) ast;
	int len = 0;
	if (isalpha(*fmt) || *fmt == '_')
	{
		len += 1;
		while (isalpha(fmt[len]) || isdigit(fmt[len]) || fmt[len] == '_')
		{
			len += 1;
		}
		ast_push(ast, ID, strndup(fmt, len));
		return len;
	}
	return NEXT_SYNTAX;
}

parser_action   number(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	int len = 0;
	if (isdigit(*fmt) || fmt[len] == '.')
	{
		len += 1;
		while (isalpha(fmt[len]) || isdigit(fmt[len]) || fmt[len] == '.')
		{
			len += 1;
		}
		ast_push(ast, NUM, strndup(fmt, len));
		return len;
	}
	return NEXT_SYNTAX;
}

preprocessor_action   matchtest(cedilla_context *ctx, ast_list *ast)
{
	(void) ctx;
	ast_macro_result out;

	out = match(ast, OP, ID);
	//return NEXT_PREPROCESSOR;

	//exit(1);
	if (out.match_size)
	{
		printf("match size = %i\n", out.match_size);
		while (out.match_size--)
		{
			ast = ast->prev;
		}

		//ast_list_free(ast->next);
		//ast_push(ast, OP, "test");

		// printf("// !\n");
		return NEXT_PREPROCESSOR;
	}
	return NEXT_PREPROCESSOR;
}

int	load_module(cedilla_context *ctx, ...)
{
	(void) ctx;

	print("Loading c99 module... \n");

	parser_klist_set(&(ctx->parsers), KV(comment));
	parser_klist_set(&(ctx->parsers), KV(mlcomment));
	parser_klist_set(&(ctx->parsers), KV(quote));
	parser_klist_set(&(ctx->parsers), KV(dquote));
	parser_klist_set(&(ctx->parsers), KV(parenthesis));
	parser_klist_set(&(ctx->parsers), KV(endparenthesis));
	parser_klist_set(&(ctx->parsers), KV(bracket));
	parser_klist_set(&(ctx->parsers), KV(endbracket));
	parser_klist_set(&(ctx->parsers), KV(brace));
	parser_klist_set(&(ctx->parsers), KV(endbrace));
	parser_klist_set(&(ctx->parsers), KV(token));
	parser_klist_set(&(ctx->parsers), KV(identifier));
	parser_klist_set(&(ctx->parsers), KV(number));

	preprocessor_klist_set(&(ctx->preprocessors), KV(matchtest));

	// Spaces
	define_token(EOL, "\n");
	define_tokens(SPACE, "\t", " ");


	// Comparison operators
	define_tokens(OP, "<=", ">=", "==", ">", "<");

	// Assignment operators
	define_tokens(OP, "+=", "-=", "*=", "/=", "^=", "&=", "%=", "|=", "=");

	// Logical operators
	define_tokens(OP, "||", "&&", "|", "&", "!");

	// Arithmetic operators
	define_tokens(OP, "+", "-", "*", "/", "^", "&", "%", "|");

	// Other operators
	define_tokens(OP, ",", ";", "?", ":", ".", "...", "#", "\\");

	// Control flow keywords
	define_tokens(KEYWORD, "return", "continue", "break", "goto");

	// Data types
	define_tokens(TYPE, "void", "signed", "unsigned", "short", "long", "int",
		"auto", "char", "_Bool", "float", "double", "_Complex");


	//define_tokens(KEYWORD, "alignof", "_Alignof", "sizeof", "typeof");

	print("done.\n");
	return 0;
}
