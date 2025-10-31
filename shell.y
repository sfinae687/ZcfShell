%define api.prefix {shell_}
%{
#include "building_task.h"
#include <stddef.h>
#include <stdio.h>

// int yydebug = 1;
int yylex(void);
int yyerror(char*);
%}

%union {
    const char *arg;
    struct AtomTask *t;
    struct PipelineTask *p;
    struct TaskList *l;
}

%token TPIPE EOL SEMICOLON RD_IN RD_OUT RD_TR AND_SYM
%token <arg> ARG
%type <t> task
%type <p> pipeline
%type <l> list

%%

input
    : EOL {building_result = NULL; YYACCEPT;}
    | list EOL {detach_building_task = 0; building_result = $1; YYACCEPT;}
    | list AND_SYM EOL {detach_building_task = 1; building_result = $1; YYACCEPT;}
    ;

list
    : task {$$ = append_list_atom_task(create_task_list(), $1); }
    | pipeline {$$ = append_list_pipeline(create_task_list(), $1); }
    | list SEMICOLON task {$$ = append_list_atom_task($1, $3); }
    | list SEMICOLON pipeline {$$ = append_list_pipeline($1, $3); }
    ;

pipeline
    : task TPIPE task {$$ = combine_pipeline($1, $3);} 
    | pipeline TPIPE task {$$ = append_pipeline($1, $3);}
    ;

task
    : ARG {$$ = create_atom_task($1);}
    | task ARG {$$ = $1; push_arg_to($1, $2);}
    | task RD_IN ARG {$$ = $1; rd_task_in($$, $3);}
    | task RD_OUT ARG {$$ = $1; rd_task_out($$, $3);}
    | task RD_TR ARG {$$ = $1; rd_task_tr($$, $3);}
    ;
%%

int yyerror(char *errmsg) {
    fprintf(stderr, "%s\n", errmsg);
    return 0;
}