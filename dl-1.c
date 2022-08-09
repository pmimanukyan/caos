#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    double (*func)(double);
    void *lib = dlopen("libm.so.6", RTLD_LAZY);
    if (!lib) {
        return 1;
    }
    char *error;
    func = dlsym(lib, argv[1]);
    if ((error = dlerror()) != NULL)  {
        return 1;
    }
    int res;
    double number;
    while ((res = scanf("%lf", &number)) == 1) {
        printf("%.10g\n", (*func)(number));
    }
    if (res != EOF) {
        return 1;
    }

    dlclose(lib);
}