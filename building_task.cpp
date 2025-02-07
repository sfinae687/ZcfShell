#include "builtin.h"
#include "building_task.h"
#include "ExecutableTask.h"
#include "BuiltinTask.h"
#include "CompositeTask.h"

#include <stdlib.h>

struct TaskList *building_result = nullptr;

using namespace TriwShell;

int detach_building_task = 0;

extern "C" AtomTask* create_atom_task(const char *cmd) {
    auto bt = get_builtin_cmd_index(cmd);
    AtomTask *rt;
    if (bt == _not_builtin) {
        rt = new ExecutableTask;
    } else {
        rt = new BuiltinTask(bt);
    }
    rt->append_arg(cmd);

    free((void*) cmd);

    return rt;
}
extern "C" void push_arg_to(AtomTask *t, const char *arg) {
    t->append_arg(arg);
    free((void*) arg);
}

extern "C" void rd_task_in(AtomTask *t, const char *f) {
    t->redirect_to_file(STDIN_FILENO, f);
    free((void*) f);
}
extern "C" void rd_task_out(AtomTask *t, const char *f) {
    t->redirect_to_file(STDOUT_FILENO, f);
    free((void*) f);

}
extern "C" void rd_task_tr(AtomTask *t, const char *f) {
    remove(f);
    t->redirect_to_file(STDOUT_FILENO, f);
    free((void*) f);

}

extern "C" PipelineTask* combine_pipeline(struct AtomTask *l, struct AtomTask *r) {
    return new PipelineTask(l, r);
}
extern "C" PipelineTask* append_pipeline(struct PipelineTask *p, struct AtomTask *t) {
    return new PipelineTask(p, t);
}

extern "C" TaskList* create_task_list(void) {
    return new TaskList;
}
extern "C" TaskList* append_list_atom_task(struct TaskList *l, struct AtomTask *t) {
    l->add_task(t);
    return l;
}
extern "C" TaskList* append_list_pipeline(struct TaskList *l, struct PipelineTask *p) {
    l->add_task(p);
    return l;
}