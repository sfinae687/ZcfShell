#include "echo.h"

#include <stdio.h>

int echo_main(int argc, const char *argv[])
{
    if (argc == 1) {
        int ch;
        while ((ch = getchar()) != EOF)
            putchar(ch);
        return 0;
    } else for (int i=1; i<argc; ++i) {
        fputs(argv[i], stdout);
    }
    return 0;
}
