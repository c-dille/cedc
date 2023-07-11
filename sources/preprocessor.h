#ifndef MACRO_H
# define MACRO_H
# include "parser.h"

typedef ast_list *(*macro)(parser_context*, ast_list *);

// may returns:
//	- STOP
//	- NEXT_MACRO
//	- RESTART (from first macro)
bool preprocess(parser_context*ctx, ast_list *l)
{
	return false;
}

#endif
