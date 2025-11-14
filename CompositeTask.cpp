#include "CompositeTask.h"

#include <cassert>

namespace TriwShell {
    
    /* Pipeline */

    PipelineTask::PipelineTask(Task *src, Task *dest)
        : src(src)
        , dest(dest)
    {

    }

    PipelineTask::~PipelineTask() {
        delete src;
        delete dest;
    }
    void PipelineTask::execute(const std::vector<RedirectFD> &additonal_fd) {
        if (! (src && dest)) {
            return ;
        }

        check_execute();
        assert(rd_file.empty());

        is_executing = true;

        int pipefd[2];

        pipe(pipefd);

        src->execute({{STDOUT_FILENO, pipefd[1]}});
        dest->execute({{STDIN_FILENO, pipefd[0]}});

        return;
    }
    int PipelineTask::wait() {
        assert(is_executing);

        int s1 = src->wait();
        int s2 = dest->wait();

        return s1 || s2;

    }

    void PipelineTask::detach() {
        assert(is_executing);
        src->detach();
        dest->detach();
    }

    /* task list */

    TaskList::~TaskList()
    {
        for (auto t : _list) {
            delete t;
        }
    }

    void TaskList::add_task(Task *t)
    {
        _list.push_back(t);
    }

    void TaskList::execute(const std::vector<RedirectFD> &additonal_fd)
    {
        assert(additonal_fd.empty());
        assert(rd_file.empty());
        assert(!is_execute());

        is_executing = true;

        for (auto t : _list) if (t) {
            t->execute();
        }
    }
    int TaskList::wait()
    {
        assert(is_executing);
        int ans = 0;
        for (auto t : _list) if (t) {
            int s = t->wait();
            ans = (ans || s);
        }
        is_executing = false;
        return ans;
    }
    void TaskList::detach()
    {
        assert(is_execute());
        for (auto t : _list) if(t) {
            t->detach();
        }
    }
}