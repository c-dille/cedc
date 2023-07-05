#include "parser.h"

parser_list	*parsers = 0;




parser_action   block(parser_context *ctx, ast_list **ast, const char *fmt)
{
	if (*fmt == '{')
	{
		printf("BRACE %i!\n", ctx->deep);

		ast_list *l = ast_list_add(ast, ALLOC(ast_node,
			.type = "BRACE",
			.source = "{}",
			.childs = 0
		));

		ULL oj_len = ctx->collumn;
		ULL deep =  ctx->deep;
		ctx->deep += 1;
		void *oj_parent = ctx->parent;
		ctx->collumn += 0;
		ctx->parent = l;
		l->data->childs = parse(ctx, parsers, fmt + 1, *ast);
		printf("\n\ngot str :: [%.*s]\n\n", ctx->collumn - oj_len , fmt + 1);
		printf("\n\ngot end :: [%s]\n\n", fmt + ctx->collumn - oj_len+  1);
		ULL new_len = ctx->collumn - oj_len;
		ctx->collumn = oj_len;
		ctx->deep = deep;
		ctx->parent = oj_parent;

		return NEXT_CHAR + new_len + 1;
	}
	return NEXT_SYNTAX;
}

char* findLastUnescapedQuote(const char* str) {
    int len = strlen(str);
    int i = len - 1;

    while (i >= 0) {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')) {
            return (char*)&str[i];
        }
        i--;
    }

    return NULL;
}

parser_action   quote(parser_context *ctx, ast_list **ast, const char *fmt)
{
	if (*fmt == '"')
	{
		ast_list_add(ast, ALLOC(ast_node,
			.type = "STRING",
			.source = strndup(fmt + 1, findLastUnescapedQuote(fmt) - fmt - 1),
			.childs = 0
		));
		printf("src=%s\n", ast_list_last(*ast)->data->source);
		return findLastUnescapedQuote(fmt) - fmt + 2;
	}
	return NEXT_SYNTAX;
}

parser_action   space(parser_context *ctx, ast_list **ast, const char *fmt)
{
	printf("is space : [%.5s] -> %i\n", fmt, isspace(*fmt));
	if (isspace(*fmt))
	{
		return NEXT_CHAR;
	}
	return NEXT_SYNTAX;
}

parser_action   endblock(parser_context *ctx, ast_list **ast, const char *fmt)
{
	// check if ast parent is a brace
	//printf("--> type : %s\n", (*ast)->data->type);
	//printf("--> parent : %p\n", ctx->parent);//->data->type);

	if (*fmt == '}')
	{
			printf("--- end with depth = %i\n", ctx->deep);
		/*if (ctx->deep > 1 && !ctx->parent)
		{
			printf("issue : deep=%i and not parent!\n", ctx->deep);
			exit(0);
		}
		if (ctx->deep == 0)
		{
			printf("ERR\n");
			exit(0);
		}
		if (ctx->deep > 1 && strcmp(ctx->parent->data->type, "BRACE"))
		{
			printf("Parse error %i!\n", ctx->deep);
			return STOP;
		}*/

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

	parser_context ctx = (parser_context){
		.file_name = "<text>",
		.line = 1,
		.collumn = 1,
		.deep = 0
	};
    ast_list *ast = parse(&ctx, parsers, fmt, 0);
	if (!ast)
		return 1;

    printf("AST type: %s\n", ast->data->type);
    printf("AST value: %s\n", ast->data->source);
	printf("AST FIRST CHILD TYPE : %s\n", ast->data->childs->data->childs->data->childs->data->type);

    return 0;
}
