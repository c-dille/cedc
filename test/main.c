#include <stdio.h>
#include <dlfcn.h>

int main() {
    void* lib1_handle = dlopen("lib1.so", RTLD_LAZY);
    void* lib2_handle = dlopen("lib2.so", RTLD_LAZY);

    // Perform error handling if needed

    // Access the shared_variable from lib2.so directly
    int* shared_variable_ptr = (int*)dlsym(lib1_handle, "shared_variable");
    void (*set_shared_variable_ptr)() = (void (*)(int))dlsym(lib2_handle, "set_shared_variable");

	printf("value=%p\n", set_shared_variable_ptr);

    // Access the shared_variable and modify it
    printf("Value: %d\n", *shared_variable_ptr);

    set_shared_variable_ptr();

    // Access the modified shared_variable
    printf("Modified Value: %d\n", *shared_variable_ptr);

    // Close the libraries when done
    dlclose(lib1_handle);
    dlclose(lib2_handle);

    return 0;
}
