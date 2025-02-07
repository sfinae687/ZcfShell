#ifndef TRIW_SHELL_BUILTIN_TASK
#define TRIW_SHELL_BUILTIN_TASK

#include "task.h"
#include "builtin.h"

namespace TriwShell {

    class RedirectInplaceException : RedirectException {
        const char * what() const noexcept override {return "can't redirect for inplace command";}
    };

    class BuiltinTask : public AtomTask {
    public:
        BuiltinTask(main_func entry);
        BuiltinTask(builtin_command cmd);

        void execute(const std::vector<RedirectFD> &additonal_fd) override;
        int wait() override;
        void detach() override;

    private:
        bool is_inplace = false;
        pid_t pid = 0;
        main_func _main;
    };

}

#endif