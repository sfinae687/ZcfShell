#include <stdio.h>
#include <unistd.h>
#include <limits.h>

static char buf[PATH_MAX];

extern "C" int pwd_main(int argc, const char *argv[]) {
    getcwd(buf, PATH_MAX);
    fputs("builtin-pwd:", stderr);
    puts(buf);
    return 0;
}