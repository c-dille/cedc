#ifndef CEDILLA_H
# define CEDILLA_H
# include <cedilla.h>


int isidentifier(char ch) {
    return isalnum(ch) || ch == '_';
}

// todo : remove #
bool isoperator(char ch) {
    return	 ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
			 ch == '=' || ch == '<' || ch == '>' || ch == '&' || ch == '|' ||
		 	 ch == '^' || ch == '!' || ch == '~' || ch == '.' || ch == '?' ||
			 ch == ':' || ch == ',' || ch == ';' || ch == '#';
}

/////

DEF(IDENTIFIER)
DEF(OPERATOR)
DEF(QUOTE)
DEF(DQUOTE)
DEF(BRACE)
DEF(PARENTHESIS)
DEF(BRACKET)

parser_action   space(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	(void) ast;
	if (*fmt == '\n')
		return PARSE_NEW_LINE;
	if (isspace(*fmt))
		return PARSE_NEXT_CHAR;

	return NEXT_SYNTAX;
}

parser_action	identifier(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	ull	len = 0;
	while (isidentifier(fmt[len]))
		len += 1;
	if (len)
	{
		ast_push(ast, IDENTIFIER, strndup(fmt, len));
		return len;
	}
	return NEXT_SYNTAX;
}

parser_action	operator(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	ull	len = 0;
	while (isoperator(fmt[len]))
		len += 1;
	if (len)
	{
		ast_push(ast, OPERATOR, strndup(fmt, len));
		return len;
	}
	return NEXT_SYNTAX;
}



parser_action   dquote(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	if (*fmt == '"')
	{
		char *lastunescaped = findlastunescaped(fmt + 1, '"');
		if (!lastunescaped)
			parse_error(ctx, "unclosed double quotes.");
	//	printf("lastUnesc: [%s\n]", lastunescaped);
		ast_push(ast, DQUOTE, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 1;
	}
	return NEXT_SYNTAX;
}

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

preprocessor_action	test(cedilla_context *ctx, ast_list *l)
{
	(void)	ctx;
	(void) l;
	printf(".");
	return (STOP_PREPROCESSOR);
}

/*

here nothin after define ... either use {} and then call parse, or proceed at each colons

*/
preprocessor_action	define(cedilla_context *ctx, ast_list *l)
{

	if (ast_type(l) == BRACE && !strcmp(ast_source(ast_prev(l)), "define"))
	{
		// todo : remove preprocess  and replace by parse(...) stdout of .so call
		printf("Trying... %s %p l=%llu c=%llu ", ast_type(l), l, ctx->line, ctx->collumn);
		printf("Found ! %s\n", l->prev->data.source);
		return (STOP_PREPROCESSOR);
	}
	return (NEXT_PREPROCESSOR);
}

/*
preprocessor_action	preprocess(cedilla_context *ctx, ast_list *l)
{

	if (ast_type(l) == BRACE && !strcmp(ast_source(ast_prev(l)), "preprocess"))
	{
		// todo : remove preprocess  and replace by parse(...) stdout of .so call
		printf("Trying... %s %p l=%llu c=%llu ", ast_type(l), l, ctx->line, ctx->collumn);
		printf("Found ! %s\n", l->prev->data.source);
		return (STOP_PREPROCESSOR);
	}
	return (NEXT_PREPROCESSOR);
}
*/

#endif
