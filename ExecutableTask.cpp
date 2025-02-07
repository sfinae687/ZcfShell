#include "ExecutableTask.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

namespace TriwShell {
    void ExecutableTask::execute(const std::vector<RedirectFD> &additional_fd) {
        check_execute();
        check_rd(additional_fd);
        is_executing = true;

        if (pid = fork()) {
            for (auto itp : additional_fd) {
                close(itp.src);
            }
            return;
        } else {
            do_redirect(additional_fd);
            execvp(argv.front().c_str(), dupargv(argv));
        }
    }

    int ExecutableTask::wait() {
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

    void ExecutableTask::detach() {
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