#include <stdio.h>
#include <unistd.h>

extern "C" int rm_main(int argc, const char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Builtin Uage: %s [files...]", argv[0]);
        return -1;
    }

    for (int i=1; i<argc; ++i) {
        if (remove(argv[i])) {
            perror("builtin-rm:");
        }
    }
    return 0;
}