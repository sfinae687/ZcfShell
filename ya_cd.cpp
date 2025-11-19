#include <stdio.h>
#include <unistd.h>

extern "C" int cd_main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: cd <dir>\n");
        return -1;
    } else {
        if (chdir(argv[1])) {
            perror("builtin-cd:");
            return -1;
        }
        return 0;
    }
}