#include <stdio.h>

void do_cat(FILE *file);

extern "C" int cat_main(int argc, const char *argv[]) {
    FILE *in;
    if (argc == 1) {
        in = stdin;
    } else {
        in = fopen(argv[1], "r");
        if (!in) {
            perror("builtin-cat:");
            return -1;
        }
    }

    do_cat(in);
    return 0;
}

void do_cat(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
}