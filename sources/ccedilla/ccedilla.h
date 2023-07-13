#ifndef C_H
# define C_H
# include "../cedilla/parser.h"

char* findlastunescaped(const char* str, char c) {
    int i = 0;

    while (str[i]) {
        if (str[i] == c && (i == 0 || str[i - 1] != '\\')) {
            return (char*)&str[i];
        }
        i += 1;
    }

    return NULL;
}

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

parser_action   space(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '\n')
		return PARSE_NEW_LINE;
	if (isspace(*fmt))
		return PARSE_NEXT_CHAR;

	return NEXT_SYNTAX;
}

parser_action	identifier(parser_context *ctx, const char *fmt, ast_list *ast)
{
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

parser_action	operator(parser_context *ctx, const char *fmt, ast_list *ast)
{
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

parser_action   quote(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '\'')
	{
		char *lastunescaped = findlastunescaped(fmt + 1, '\'');
		if (!lastunescaped)
			parse_error(ctx, "unclosed simple quote.");
		ast_push(ast, QUOTE, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 1;// + 500;
	}
	return NEXT_SYNTAX;
}

parser_action   dquote(parser_context *ctx, const char *fmt, ast_list *ast)
{
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

parser_action   comment(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '/' && fmt[1] == '/' && ctx->collumn == 1)
	{
		ull len = 0;
		while (fmt && fmt[len] != '\n')
			len   += 1;
		return len;
	}
	return NEXT_SYNTAX;
}

parser_action   mlcomment(parser_context *ctx, const char *fmt, ast_list *ast)
{
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

parser_action   brace(parser_context *ctx, const char *fmt, ast_list *ast)
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

parser_action   parenthesis(parser_context *ctx, const char *fmt, ast_list *ast)
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

parser_action   bracket(parser_context *ctx, const char *fmt, ast_list *ast)
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

parser_action   endbrace(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '}')
	{
		if (ast_type(ast_parent(ast)) != BRACE)
			parse_error(ctx, "unexpected closing brace.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}

parser_action   endparenthesis(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ')')
	{
		if (ast_type(ast_parent(ast)) != PARENTHESIS)
			parse_error(ctx, "unexpected closing parenthesis.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}

parser_action   endbracket(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ']')
	{
		if (ast_type(ast_parent(ast)) != BRACKET)
			parse_error(ctx, "unexpected closing bracket.");
		return STOP_PARSER;
	}
	return NEXT_SYNTAX;
}

preprocessor_action	test(parser_context *ctx, ast_list *l)
{
	printf(".");
	return (STOP_PREPROCESSOR);
}
#endif
