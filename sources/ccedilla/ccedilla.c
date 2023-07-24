#include "ccedilla.h"
/*
 *	USAGE :
 *
 *		- cedilla input_path [output_path]
 *		will compile input path to output path
 *
 *		- cedilla input_path
 *		will dump ast three to stdout
 *
 */
int main(int ac, char **av)
{
	if (ac != 2 && ac != 3)
	{
		printf("Error, usage is %s input [output]\n", av[0]);
		return (1);
	}
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

	macro_list_set(&macros, KV(ce_preprocess));

	ast_list	*ast = ast_list_root(0);
	parser_context ctx = (parser_context)
	{
		.file_path = "<text>",
		.line = 1,
		.collumn = 1,
		.depth = 0,
		.parser_name = "",
		.parsers = parsers,
		.preprocess = preprocess,
		.objects = 0,
		.macros = macros
	};

	object_klist_set(&ctx.objects, "test", (object){.ptr="test", .free=0, .clone=0, .compile=0});

	if (!parse_file(&ctx, av[1], ast))
	{
		parser_klist_free(parsers);
		object_klist_free(ctx.objects);
		return 1;
	}
	if (ac == 2)
	{
		//ast_dump(ast);
	}
	else if (ac == 3)
	{
		// compile ast to output file
	}

	ast_list_free(ast);
	parser_klist_free(parsers);
	object_klist_free(ctx.objects);

	return (0);
}
