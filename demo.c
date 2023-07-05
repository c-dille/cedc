#include "parser.h"

parser_list	*parsers = 0;

parser_action   block(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '{')
	{
		printf("BRACE! %llu\n", ctx->deep);
		return
			2 +
			parse(ctx, parsers, fmt + 1,
				ast_push(ast, "BRACE", "{}")->data->childs
			);
	}
	return NEXT_SYNTAX;
}

parser_action   quote(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '"')
	{
		printf("FMT:%.5s\n", fmt);
		printf("STR\n---%s\n", ast_list_last(ast)->data->type);
		ast_list *l = ast_push(ast, "STRING", strndup(fmt + 1, findLastUnescapedQuote(fmt) - fmt - 1));
		printf("---%s\n", l->data->source);

		printf("src=%s\n", ast_list_last(ast)->data->source);
		return findLastUnescapedQuote(fmt) - fmt + 2;
	}
	return NEXT_SYNTAX;
}

parser_action   space(parser_context *ctx, const char *fmt, ast_list *ast)
{
	printf("is space : [%.5s] -> %i\n", fmt, isspace(*fmt));
	if (isspace(*fmt))
	{
		return NEXT_CHAR;
	}
	return NEXT_SYNTAX;
}

parser_action   endblock(parser_context *ctx, const char *fmt, ast_list *ast)
{
	if (*fmt == '}')
	{
			printf("--- end with depth = %llu\n", ctx->deep);
		return STOP;
	}
	return NEXT_SYNTAX;
}

int main()
{

	parser_list_add(&parsers, block);
	parser_list_add(&parsers, quote);
	parser_list_add(&parsers, space);
	parser_list_add(&parsers, endblock);


    const char *fmt = "  {  {      {  \"stri\\\"ng\"  } } }";


	ast_list	*ast = ast_list_root(0);


	parser_context ctx = (parser_context){
		.file_name = "<text>",
		.line = 1,
		.collumn = 1,
		.deep = 0
	};

	parse(&ctx, parsers, fmt, ast);

	if (!ast)
		return 1;

    printf("AST type: %s\n", ast->next->data->type);
    printf("AST value: %s\n", ast->next->data->source);
	printf("AST  CHILD TYPE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->data->type);

	printf("AST  CHILD SOURCE : %s\n", ast->next->data->childs->next->data->childs->next->data->childs->next->data->source);

    return 0;
}
