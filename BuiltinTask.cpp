#include "BuiltinTask.h"

#include <unistd.h>
#include <sys/wait.h>


namespace TriwShell {
    BuiltinTask::BuiltinTask(main_func entry)
        : is_inplace(entry == cd_main)
        , _main(entry)
    {

    }

    BuiltinTask::BuiltinTask(builtin_command cmd)
        : BuiltinTask(builtin_command_entry[cmd])
    {

    }

    void BuiltinTask::execute(const std::vector<RedirectFD> &additonal_fd) {

        if (is_inplace) {
            if (additonal_fd.empty() && rd_file.empty()) {
                return ;
            } else {
                throw RedirectInplaceException();
            }
        }

        check_execute();
        check_rd(additonal_fd);
        is_executing = true;

        if (pid = fork()) {
            for (auto itp : additonal_fd) {
                close(itp.src);
            }
            return;
        } else {
            do_redirect(additonal_fd);
            exit(_main(argv.size(), (const char**)dupargv(argv)));
        }
    }
    
    int BuiltinTask::wait() {
        if (is_inplace) {
            return _main(argv.size(), (const char**)dupargv(argv));
        } else {
            if (is_executing && pid) {
                int s;
                waitpid(pid, &s, WUNTRACED);
                is_executing = false;
                pid = 0;

                return s;
            } else {
                throw std::logic_error("await unwaitable task");
            }
        }
    }

    void BuiltinTask::detach()  {
        if (is_inplace) {
            throw std::logic_error("Try detach a inplace command");
        } else {
            if (is_executing && pid) {
                detach_pid(pid);
                pid = 0;
                is_executing = false;
                return ;
            } else {
                throw std::logic_error("await unwaitable task");
            }
        }

    }


}