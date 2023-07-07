#include "parser.h"

parser_list	*parsers = 0;

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
		char *lastunescaped = findlastunescaped(fmt, '\'');
		ast_push(ast, QUOTE, strndup(fmt + 1, lastunescaped - fmt - 1));
		return lastunescaped - fmt + 2;
	}
	return NEXT_SYNTAX;
}

parser_action   dquote(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '"')
	{
		char *lastunescaped = findlastunescaped(fmt, '"');
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
		{
			len   += 1;
		}
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
		{
			len   += 1;
		}
		if (!fmt[len])
		{
			printf("UNCLOSED MLCOMMENT\n");
			exit(0);
		}
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
		{
			printf("Error, unexpected closing brace.\n");
			exit(0);
		}
		return STOP;
	}
	return NEXT_SYNTAX;
}

parser_action   endparenthesis(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ')')
	{
		if (!ast->data->parent || ast->data->parent->data->type != PARENTHESIS)
		{
			printf("Error, unexpected closing parenthesis.\n");
			exit(0);
		}
		return STOP;
	}
	return NEXT_SYNTAX;
}

parser_action   endbracket(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == ']')
	{
		if (!ast->data->parent || ast->data->parent->data->type != BRACKET)
		{
			printf("Error, unexpected closing bracket.\n");
			exit(0);
		}
		return STOP;
	}
	return NEXT_SYNTAX;
}

int main()
{
	parser_list_add(&parsers, comment);
	parser_list_add(&parsers, mlcomment);

	parser_list_add(&parsers, space);
	parser_list_add(&parsers, identifier);
	parser_list_add(&parsers, operator);
	parser_list_add(&parsers, quote);
	parser_list_add(&parsers, dquote);

	parser_list_add(&parsers, brace);
	parser_list_add(&parsers, parenthesis);
	parser_list_add(&parsers, bracket);



	parser_list_add(&parsers, endbrace);
	parser_list_add(&parsers, endparenthesis);
	parser_list_add(&parsers, endbracket);

    const char *fmt = "  {{{  \"stri\\\"ng\" hiii }}}  /**/   ";
	ast_list	*ast = ast_list_root(0);
	parser_context ctx = (parser_context){
		.file_name = "<text>",
		.line = 1,
		.collumn = 1,
		.depth = 0,
		.begin_ptr = fmt,
		.end_ptr = fmt + strlen(fmt)
	};

	if (!parse(&ctx, parsers, fmt, ast))
		return 1;

    printf("AST type: %s\n", ast->next->data->type);
    printf("AST value: %s\n", ast->next->data->source);
	printf("AST STRING TYPE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->data->type);
	printf("AST STRING SOURCE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->data->source);

	printf("AST ID TYPE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->next->data->source);

	printf("AST ID SOURCE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->next->data->source);


    return 0;
}
