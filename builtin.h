#ifndef TRIW_BU
#define TRIW_BU

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    #include "builtin/cat.h"
    #include "builtin/cd.h"
    #include "builtin/ls.h"
    #include "builtin/mkdir.h"
    #include "builtin/pwd.h"
    #include "builtin/rm.h"
    #include "builtin/wc.h"
    #include "builtin/echo.h"

    // 从字符串映射到内建任务入口点所需要的组件

    enum builtin_command {
        _not_builtin = -1,
        bi_cat,
        bi_cd,
        bi_ls,
        bi_mkdir,
        bi_pwd,
        bi_rm,
        bi_wc,
        bi_echo,
    };

    typedef int (*main_func)(int argc, const char *argv[]);

    extern main_func builtin_command_entry[];
    
    /**
     * 将命令的名字映射到对应的索引
     * @param cmd_str 待查找的字符串名字
     * @return 表示内建命令的枚举值，如果不存在则为 _not_builtin
     */
    enum builtin_command get_builtin_cmd_index(const char cmd_str[]);

    /**
     * 比对命令的命令，找到对应的内建命令入口的函数指针
     * @return 对应的内建命令的函数指针，如果不存在则为空指针
     */
    main_func get_builtin_cmd_entry(const char cmd_str[]);


#ifdef __cplusplus
}
#endif

#endif 