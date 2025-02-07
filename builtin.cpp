#include <string.h>

#include "builtin.h"

main_func builtin_command_entry[] = {
    cat_main,
    cd_main,
    ls_main,
    mkdir_main,
    pwd_main,
    rm_main,
    wc_main,
    echo_main,
};

const char *builtin_cmd_str[] = {
    "cat",
    "cd",
    "ls",
    "mkdir",
    "pwd",
    "rm",
    "wc",
    "echo",
    0
};

enum builtin_command get_builtin_cmd_index(const char cmd_str[]) {
    int i=0;
    while (builtin_cmd_str[i]) {
        if (strcmp(builtin_cmd_str[i], cmd_str) == 0) {
            return (builtin_command)i;
        } else {
            ++i;
        }
    }
    return (builtin_command)-1;
}

main_func get_builtin_cmd_entry(const char cmd_str[]) {
    enum builtin_command ci;
    ci = get_builtin_cmd_index(cmd_str);
    if (ci != -1) {
        return builtin_command_entry[ci];
    } else {
        return NULL;
    }
}