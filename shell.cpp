#include "builtin.h"
#include "BuiltinTask.h"
#include "ExecutableTask.h"
#include "building_task.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>

extern "C" {
    #include "shell.tab.h"
}

using namespace TriwShell;

void clear_stdin();
ArgumentVector spilit_argv(std::string command);
AtomTask* build_task(const ArgumentVector &v);

int main() {
    

#ifdef SIMPLE_IMPL

    while (true) {
        std::cout << "$";
        std::string cml;
        if (!std::getline(std::cin, cml)) {
            std::exit(0);
        }
        auto argv = spilit_argv(cml);
        AtomTask *t = build_task(argv);
        if (t) {
            t->execute({});
            t->wait();
        }
    }

#else 
    while (true) {
        std::cout << "$";
        if (shell_parse()) {
            clear_stdin();
            continue;
        }

        if (building_result) {
            building_result->execute({});
            if (detach_building_task) {
                building_result->detach();
            } else {
                building_result->wait();
            }
            delete building_result;
            building_result = nullptr;
        }

        clear_stdin();

        check_detach();

        std::cout << "\n";
    }
#endif

}

void clear_stdin() {
    fflush(stdin);
}

ArgumentVector spilit_argv(std::string command) {
    std::stringstream ss(command);
    std::string word;
    ArgumentVector v;
    while (ss >> word) {
        v.push_back(std::move(word));
    }
    return v;
}

AtomTask* build_task(const ArgumentVector &v) {
    if (v.empty()) {
        return nullptr;
    } else {
        const char *c_arg = strdup(v[0].c_str());
        AtomTask *t;
        t = create_atom_task(c_arg);

        auto vlen = v.size();
        for (int i=1; i<vlen; ++i) {
            push_arg_to(t, strdup(v[i].c_str()));
        }

        return t;
    }
}