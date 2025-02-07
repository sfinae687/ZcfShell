#ifndef TRIW_SHELL_COMP_TASK
#define TRIW_SHELL_COMP_TASK

#include "task.h"

namespace TriwShell {

    class PipelineTask : public Task {
    public:
        /**
         * 构造一个管道重定向的任务，获取参数任务的所有权。
         */
        PipelineTask(Task *src, Task *dest);
        PipelineTask(const PipelineTask &) = delete;
        ~PipelineTask() override;

        /**
         * @attention 该函数只处理，指向标准输入，标准输出，标准错误的重定向
         */
        void execute(const std::vector<RedirectFD> &additonal_fd) override;
        int wait() override;
        void detach() override;

    private:
        Task *src;
        Task *dest;
    };

    class TaskList : public Task {
    public:
        
        ~TaskList() override;
        
        void add_task(Task *t);

        void execute(const std::vector<RedirectFD> &additonal_fd) override;
        int wait() override;
        void detach() override;


    private:
        std::vector<Task *> _list;
    };

}

#endif