#include "parser.h"

parser_list	*parsers = 0;

const char
	*IDENTIFIER = "IDENTIFIER",
	*OPERATOR = "OPERATOR",
	*QUOTE = "DQUOTE",
	*DQUOTE = "DQUOTE",
	*BRACE = "BRACE";

parser_action   space(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (isspace(*fmt))
	{
		return NEXT_CHAR;
	}
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

parser_action   block(parser_context *ctx, const char *fmt, ast_list *ast)
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

parser_action   endblock(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '}')
	{
		return STOP;
	}
	return NEXT_SYNTAX;
}

int main()
{


	parser_list_add(&parsers, space);
	parser_list_add(&parsers, identifier);
	parser_list_add(&parsers, operator);
	parser_list_add(&parsers, quote);
	parser_list_add(&parsers, dquote);

	parser_list_add(&parsers, block);
	parser_list_add(&parsers, endblock);

    const char *fmt = "  {  {      {  \"stri\\\"ng\" hiii } } }";
	ast_list	*ast = ast_list_root(0);
	parser_context ctx = (parser_context){
		.file_name = "<text>",
		.line = 1,
		.collumn = 1,
		.depth = 0
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
