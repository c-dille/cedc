#ifndef PREPROCESSOR_H
# define PREPROCESSOR_H
# include "parser.h"

typedef enum
{
	RESTART_PREPROCESSOR = -1,
	STOP_PREPROCESSOR = 0,
	NEXT_PREPROCESSOR = 1
}	preprocessor_action;
typedef preprocessor_action (*macro)(cedilla_context *, ast_list *);
DEF_KLIST_PROTO(macro, preprocessor_klist)
DEF_KLIST(macro, preprocessor_klist, free, ((void*(*)(void*))0))

DEF(COMMENT)

/*
*	TODO:
*
*		Perform matches in reverse order in one pass,
*		Or apply preprocessor in a second pass
*/
bool preprocess(cedilla_context *ctx, ast_list *l)
{
	preprocessor_klist	*it = ctx->preprocessors;
	int	depth = 0;
	while (it)
	{
		if (depth++ > 25)
			parse_error(ctx, "depth exceed while running macro name '%s'.", it->data->key);

		preprocessor_action pa = it->data->value(ctx, l);

		if (pa == RESTART_PREPROCESSOR)
		{
			it = ctx->preprocessors;
			continue;
		}
		if (!pa)
			break ;

		it = it->next;
	}
	return false;
}


DEF(ANY)
DEF(UNTIL)
DEF(NOT)

typedef struct s_ast_macro_result
{
	int			match_size;

	ast_list	*l;
}	ast_macro_result;

ast_macro_result _match(ast_list *l, ...) {
    ast_macro_result out = {0, 0};
    va_list ap;
	ast_list 		*lb = l;
    const char *str;

	va_start(ap, l);
    while ((str = va_arg(ap, const char*))) {
        if (str == UNTIL) {
            str = va_arg(ap, const char *);

            if (!str) {
                va_end(ap);
                // We can decide to handle this error according to the logic of the rest of our application
                exit(EXIT_FAILURE); // or return an error code
            }

            // handle NOT after UNTIL
            if (str == NOT) {
                str = va_arg(ap, const char *); // the type to NOT match
                while (l && ast_type(l) != str) {
                    out.match_size += 1;
                    l = l->prev;
                }
            } else { // regular UNTIL
                while (l && ast_type(l) != str) {
                    out.match_size += 1;
                    l = l->prev;
                }
            }

            if (!l || ast_type(l) != str) {
                va_end(ap);
                // Handle error: either return an error code or take appropriate action
                return (ast_macro_result) {0, 0}; // for instance
            }
        } else if (str == NOT) {
            str = va_arg(ap, const char *);
            if (!str || ast_type(l) == str) { // failed NOT match
                va_end(ap);
                return (ast_macro_result) {0, 0};
            }
            out.match_size += 1;
        } else if (str == ANY || ast_type(l) == str) {
            out.match_size += 1;
        } else  { // no match
            va_end(ap);
            return (ast_macro_result) {0, 0};
        }
		lb = l;
        l = l->prev;
    }
    va_end(ap);
	//out.l = 0;


	out.l = ast_list_clone(lb);
	if (out.l)
		ast_set_parent(out.l->data.childs, out.l);
    // clone matched nodes
    //int match_size = out.match_size;
    /*while (lb && match_size--) {
		printf("%p : %p\n", out.l, lb);
		//ast_push(out.l, "lol", "+");
		printf("data %p\n", lb->data.childs->data.data.ptr);
		printf("type %s\n", lb->data.childs->data.type);
		printf("src %s\n", lb->data.childs->data.source);
		printf("parent %p\n", lb->data.childs->data.parent);
		//strdup(0);
		printf("childs %p\n", lb->data.childs->data.childs);


	//ast_node_clone(lb->data);
		ast_list_add_front(&(out.l), ast_node_clone(lb->data));
		ast_set_parent(out.l->data.childs, out.l);



        lb = lb->prev; // move back through the original list
    }
*/
    return out;
}

#define match(...) _match(__VA_ARGS__, NULL)

#endif
