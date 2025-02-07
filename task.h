#ifndef TRIW_SHELL_TASK
#define TRIW_SHELL_TASK

#include <unistd.h>
#include <cstddef>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <stdexcept>

namespace TriwShell {


    class RedirectException : std::exception {
    public:
        const char* what() const noexcept override  {return "redirection failed";}
    };

    class MultiRedirectException : RedirectException {
    public:
        const char* what() const noexcept override  {return "There is a redirection repeated.";}
    };

    class CopyTaskException : std::exception {
        const char * what() const noexcept override {return "Exception during copy a task";}
    };

    using ArgumentVector = std::vector<std::string>; ///< 参数向量，表示命令行参数

    /**
     * 将参数向量转换为C风格的参数向量
     * @return 字符指针的数组， 表示C风格的参数向量，由外部释放
     */
    char **dupargv(const ArgumentVector &argv);

    struct RedirectFD {
        int dest;
        int src;
    };

    /**
     * 任务，可以被执行。并且维护了文件重定向的信息
     * @details 多次重定向一个文件是错误。
     */
    class Task {
    public:
        Task() = default;
        Task(const Task &) = delete;
        Task& operator= (const Task &) = delete;

        virtual ~Task() {}

        /**
         * 使得任务开始执行
         */
        void execute();
        /**
         * 执行任务并带有额外的，由文件描述符描述的重定向信息。
         * @param 附加的，使用文件描述符定义的重定向信息，文件描述符的所有权将会转移给任务
         * @details 该函数时任务执行语义的原语，定义执行语义的子类应当重写该方法
         */
        virtual void execute(const std::vector<RedirectFD> &additonal_fd) = 0;

        /**
         * 获取任务的中止状态
         */
        virtual int wait() = 0;

        /**
         * 分离一个任务，不再等待
         */
        virtual void detach() = 0;

        /**
         * 维护一个重新定向信息
         */
        void redirect_to_file(int fd, std::string);

        bool is_execute() const;

    protected:
        /**
         * 检查当前所具有的文件重定向是否与给定的重定向列表冲突，如果冲突将会抛出一个异常
         */
        void check_rd(const std::vector<RedirectFD> &);
        void check_execute();

        void do_redirect(const std::vector<RedirectFD> &);

        std::unordered_map<int, std::string> rd_file;

        bool is_executing = false;
    };

    /**
     * 实际执行任务的单元，维护了命令行参数
     */
    class AtomTask : public Task {
    public:
        void set_argv(ArgumentVector v);
        void append_arg(std::string arg);
        void clear_arg();

    protected:
        ArgumentVector argv = {};

    };

    extern std::list<pid_t> detached_pid;

    /**
     * 分离一个子进程
     */
    void detach_pid(pid_t);
    /**
     * 检查并清除多余的分离子进程
     */
    void check_detach();

    /**
     * 将 dest 重定向为 fd, fd将会被关闭
     */
    int redirect_fd(int dest, int fd);

}


#endif