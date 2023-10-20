#include "cedilla.h"

// TODO : store arguments in a klist of char* so that modules could use em
const char *base_include_keyword = "cedilla_load";

parser_action   cedilla_load(cedilla_context *ctx, const char *fmt, ast_list *ast)
{
	(void) ctx;
	(void) ast;
	if (ctx->collumn == 1)
	{
		size_t keyword_len = strlen(base_include_keyword);
		if (!strncmp(fmt, base_include_keyword, keyword_len))
		{
			const char *path_start = fmt + keyword_len;
			while (isspace(*path_start))
				path_start++;

			const char *line_end = strchr(path_start, '\n');
			if (!line_end)
				line_end = path_start + strlen(path_start);

			size_t path_len = line_end - path_start;
			while (path_len > 0 && isspace(path_start[path_len - 1]))
				path_len--;

			char full_path[path_len + 4 + 1];
			strncpy(full_path, path_start, path_len);
			strcpy(full_path + path_len, ".so");

			printf("Loaded module path: %s\n", full_path);
			_load_module(full_path, ctx);

			ctx->is_eol = true;

			return (line_end - fmt + 1);
		}
	}
	return NEXT_SYNTAX;
}

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
	preprocessor_klist 		*preprocessors = 0;

	parser_klist_set(&parsers, KV(cedilla_load));

	ast_list	*ast = ast_list_root(0);	// really needed ?? or play with ptr ** ??

	// todo : also set preprocessors and/compiler in it
	cedilla_context ctx = (cedilla_context)
	{
		.file_path = "<text>",
		.line = 1,
		.collumn = 1,
		.depth = 0,
		.parsers = parsers,
		.preprocessors = preprocessors,
	// TODO: .compilers = ...
		.data = {0,0,0, 0, 0},
		.is_eol = false
	};


	if (!parse_file(&ctx, av[1], ast))
	{
		parser_klist_free(parsers);
		return 1;
	}
	if (ac == 2)
	{
		ast_dump(ast);
	}
	else if (ac == 3)
	{
		// compile ast to output file
	}

	ast_list_free(ast);
	parser_klist_free(parsers);

	return (0);
}
