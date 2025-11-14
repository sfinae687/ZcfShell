#ifndef TRISHELL_UTIL
#define TRISHELL_UTIL

#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

#ifdef __cplusplus
extern "C" {
#endif

void shell_panic(const char *msg) {
    fprintf(stderr, "Panic: %s\n", msg);
}

#ifdef __cplusplus
}
#endif

#endif