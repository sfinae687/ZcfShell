#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int mkdir_main(int argc, const char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: builtin-%s [dirs...]\n", argv[0]);
        return -1;
    } else {
        for (int i=1; i<argc; ++i) {
            if (mkdir(argv[i], 0)) {
                perror("builtin-mkdir:");
            }
        }
    }

    return 0;

}