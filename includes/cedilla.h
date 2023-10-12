#ifndef CE_MODULE_H
# define CE_MODULE_H
# include <dlfcn.h>

# include "macros/macros.h"

# include "ast.h"
# include "parser.h"
# include "preprocessor.h"
# include "compiler.h"

typedef int(*module_loader)(cedilla_context *ctx);

int _load_module(const char *path, cedilla_context *ctx)
{
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle)
    {
        print("Error loading module: %s\n", dlerror());
        return -1;
    }

    module_loader load = (module_loader) dlsym(handle, "load_module");
    char *error = dlerror();
    if (error)
    {
        fprintf(stderr, "Error finding function: %s\n", error);
        dlclose(handle);
        return -1;
    }

    load(ctx);

	// TODO : add .so in a list and free em on exit
   // dlclose(handle);
    return 0;
}

#endif
