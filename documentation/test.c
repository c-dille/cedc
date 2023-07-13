#include "sources/parser.h"

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

int main()
{
	parser_klist	*parsers = 0;

	parser_klist_set(&parsers, KV(comment));
	parser_klist_set(&parsers, KV(mlcomment));
	parser_klist_set(&parsers, KV(space));
	parser_klist_set(&parsers, KV(identifier));
	parser_klist_set(&parsers, KV(operator));
	parser_klist_set(&parsers, KV(quote));
	parser_klist_set(&parsers, KV(dquote));
	parser_klist_set(&parsers, KV(brace));
	parser_klist_set(&parsers, KV(parenthesis));
	parser_klist_set(&parsers, KV(bracket));
	parser_klist_set(&parsers, KV(endbrace));
	parser_klist_set(&parsers, KV(endparenthesis));
	parser_klist_set(&parsers, KV(endbracket));

	macro_list *macros = 0;

	//macro_list_set(&macros, KV(test));

    const char *fmt = "{{{ \"fedsefs\\\"dde\" hiiii }}}  /**/   ";
	ast_list	*ast = ast_list_root(0);
	parser_context ctx = (parser_context){
		.file_path = "<text>",
		.line = 1,
		.collumn = 0,
		.depth = 0,
		.begin_ptr = fmt,
		.end_ptr = fmt + strlen(fmt),
		.parser_name = "",
		.parsers = parsers,
		.preprocess = preprocess,
		.objects = 0,
		.macros = macros
	};

	object_klist_set(&ctx.objects, "test", (object){.ptr="test",.free=0, .clone=0, .compile=0, .decompile=0});

	if (!parse(&ctx, fmt, ast))
		return 1;

	object_klist_free(ctx.objects);

    printf("AST type: %s\n", ast_type(ast_next(ast)));
    printf("AST value: %s\n",  ast_source(ast_next(ast)));
	printf("AST STRING TYPE : %s\n", ast_type(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast)))))))));
	printf("AST STRING SOURCE : %s\n", ast_source(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast)))))))));
	printf("AST ID TYPE : %s\n", ast_type(ast_next(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast))))))))));
	printf("AST ID SOURCE : %s\n", ast_source(ast_next(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast_childs(ast_next(ast))))))))));

	//ast_get(ast, next, type)

	printf("\n\n- - - - - - - - - -\n\n");

	ast_dump(ast);

	ast_list_free(ast);
	parser_klist_free(parsers);

//	return 0;
	__auto_type l = ast_list_vnew(2,
		(ast_node) {
			.type = "ROOT",
			.source = 0,
			.childs = 0
		},
		(ast_node) {
			.type = "BRACE",
			.source = strdup("{}"),
			.childs = ast_list_vnew(2,
				(ast_node) {
					.type = "ROOT",
					.source = 0,
					.childs = 0
				},
				(ast_node) {
					.type = "BRACE",
					.source = strdup("{}"),
					.childs = ast_list_vnew(2,
						(ast_node) {
							.type = "ROOT",
							.source = 0,
							.childs = 0
						},
						(ast_node) {
							.type = "BRACE",
							.source = strdup("{}"),
							.childs = ast_list_vnew(3,
								(ast_node) {
									.type = "ROOT",
									.source = 0,
									.childs = 0
								},
								(ast_node) {
									.type = "DQUOTE",
									.source = strdup("fedsefs\"dde"),
									.childs = ast_list_vnew(1,
										(ast_node) {
											.type = "ROOT",
											.source = 0,
											.childs = 0
										}
									)
								},
								(ast_node) {
									.type = "IDENTIFIER",
									.source = strdup("hiiii"),
									.childs = ast_list_vnew(1,
										(ast_node) {
											.type = "ROOT",
											.source = 0,
											.childs = 0
										}
									)
								}
							)
						}
					)
				}
			)
		}
	);

	ast_list_free(l);

    return 0;
}
