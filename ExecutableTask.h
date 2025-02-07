#ifndef TRIW_SHELL_EXE_TASK
#define TRIW_SHELL_EXE_TASK

#include "task.h"

namespace TriwShell {

    class ExecutableTask : public AtomTask {
    public:
        void execute(const std::vector<RedirectFD> &additonal_fd) override;
        int wait() override;
        void detach() override;

    private:
        pid_t pid;
    };

}

#endif