#include "parser.h"

named_parser_list	*parsers = 0;

const char
	*IDENTIFIER = "IDENTIFIER",
	*OPERATOR = "OPERATOR",
	*QUOTE = "DQUOTE",
	*DQUOTE = "DQUOTE",
	*BRACE = "BRACE",
	*PARENTHESIS = "PARENTHESIS",
	*BRACKET = "BRACKET";

parser_action   space(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (isspace(*fmt))
		return NEXT_CHAR;
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
		return lastunescaped - fmt + 2;// + 500;
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
		ast_push(ast, DQUOTE, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 2;
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
		return len + 1;
	}
	return NEXT_SYNTAX;
}

parser_action   brace(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '{')
	{
		return
			2 +
			parse(ctx, parsers, fmt + 1,
				ast_push(ast, BRACE, "{}")->data->childs
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
			parse(ctx, parsers, fmt + 1,
				ast_push(ast, PARENTHESIS, "()")->data->childs
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
			parse(ctx, parsers, fmt + 1,
				ast_push(ast, BRACKET, "[]")->data->childs
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
		return STOP;
	}
	return NEXT_SYNTAX;
}

parser_action   endparenthesis(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ')')
	{
		if (ast_type(ast_parent(ast)) != PARENTHESIS)
			parse_error(ctx, "unexpected closing parenthesis.");
		return STOP;
	}
	return NEXT_SYNTAX;
}

parser_action   endbracket(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ']')
	{
		if (ast_type(ast_parent(ast)) != BRACKET)
			parse_error(ctx, "unexpected closing bracket.");
		return STOP;
	}
	return NEXT_SYNTAX;
}



int main()
{
	named_parser_list_add(&parsers, alloc_named_parser(comment));
	named_parser_list_add(&parsers, alloc_named_parser(mlcomment));

	named_parser_list_add(&parsers, alloc_named_parser(space));
	named_parser_list_add(&parsers, alloc_named_parser(identifier));
	named_parser_list_add(&parsers, alloc_named_parser(operator));

	named_parser_list_add(&parsers, alloc_named_parser(quote));
	named_parser_list_add(&parsers, alloc_named_parser(dquote));

	named_parser_list_add(&parsers, alloc_named_parser(brace));
	named_parser_list_add(&parsers, alloc_named_parser(parenthesis));
	named_parser_list_add(&parsers, alloc_named_parser(bracket));

	named_parser_list_add(&parsers, alloc_named_parser(endbrace));
	named_parser_list_add(&parsers, alloc_named_parser(endparenthesis));
	named_parser_list_add(&parsers, alloc_named_parser(endbracket));

    const char *fmt = "{{{ \"fedsefs\\\"dde\" hiiii }}}  /**/   ";
	ast_list	*ast = ast_list_root(0);
	parser_context ctx = (parser_context){
		.file_path = "<text>",
		.line = 1,
		.collumn = 0,
		.depth = 0,
		.begin_ptr = fmt,
		.end_ptr = fmt + strlen(fmt),
		.parser_name = ""
	};

	if (!parse(&ctx, parsers, fmt, ast))
		return 1;

    printf("AST type: %s\n", ast_type(ast_next(ast)));
    printf("AST value: %s\n",  ast_source(ast_next(ast)));
	printf("AST STRING TYPE : %s\n", ast_type(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast)))))))));
	printf("AST STRING SOURCE : %s\n", ast_source(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast)))))))));
	printf("AST ID TYPE : %s\n", ast_type(ast_next(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast))))))))));
	printf("AST ID SOURCE : %s\n", ast_source(ast_next(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast))))))))));


    return 0;
}
