#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

unsigned long long line_count;
unsigned long long word_count;
unsigned long long byte_count;

void do_wc(FILE *file);
void summary();

extern "C" int wc_main(int argc, const char *argv[]) {

    if (argc == 1) {
        do_wc(stdin);
    } else {
        for (int i=1; i<argc; ++i) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                fprintf(stderr, "Can't open %s:", argv[i]);
                perror("");
            }
            do_wc(file);
        }
    }
    summary();
    return 0;
}

void do_wc(FILE *file) {
    int prev_char = ' ';
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(prev_char) && isgraph(ch)) {
            ++word_count;
        }
        if (ch == '\n') {
            ++line_count;
        }
        ++byte_count;
        prev_char = ch;
    }
}

void summary() {
    printf("%llu %llu %llu\n", line_count, word_count, byte_count);
}