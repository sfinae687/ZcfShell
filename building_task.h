#ifndef TRIW_SHELL_BUILDER_TASK
#define TRIW_SHELL_BUILDER_TASK


#ifdef __cplusplus
    #include "task.h"
    #include "CompositeTask.h"
    using TriwShell::AtomTask;
    using TriwShell::PipelineTask;
    using TriwShell::TaskList;

    extern "C" {

#else
    struct AtomTask;
    struct PipelineTask;
    struct TaskList;
    typedef struct TaskList TaskList;
    typedef struct AtomTask AtomTask;
    typedef struct PipelineTask PipelineTask;
#endif

extern TaskList *building_result;
extern int detach_building_task;

AtomTask* create_atom_task(const char *);
void push_arg_to(AtomTask *, const char *);
void rd_task_in(AtomTask *, const char *f);
void rd_task_out(AtomTask *, const char *f);
void rd_task_tr(AtomTask *, const char *f);

PipelineTask* combine_pipeline(AtomTask *l, AtomTask *r);
PipelineTask* append_pipeline(PipelineTask *p, AtomTask *t);

TaskList* create_task_list(void);
TaskList* append_list_atom_task(TaskList *l, AtomTask *t);
TaskList* append_list_pipeline(TaskList *l, PipelineTask *p);

#ifdef __cplusplus
}
#endif

#endif