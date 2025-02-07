#include "task.h"

#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace TriwShell {

    char **dupargv(const ArgumentVector &argv) {
        if (argv.size() == 0) {
            return nullptr;
        }

        auto len = argv.size();
        char **cargv = (char **) malloc(sizeof(char **) * (len + 1));
        cargv[len] = nullptr;

        for (int i=0; i<len; ++i) {
            cargv[i] = strdup(argv[i].c_str());
        }

        return cargv;

    }

    /* Task 实现 */

    void Task::execute() {
        execute({});
    }

    void Task::redirect_to_file(int fd, std::string path) {
        if (rd_file.find(fd) == end(rd_file)) {
            rd_file[fd] = std::move(path);
        } else {
            throw MultiRedirectException();
        }
    }

    bool Task::is_execute() const {
        return is_executing;
    }

    void Task::check_execute() {
        if (is_executing) {
            throw std::logic_error("The task is executing");
        }
    }

    void Task::do_redirect(const std::vector<RedirectFD> &ard) {
        for (auto  itp : rd_file) {
            int d;
            std::string sp;
            std::tie(d, sp) = itp;
            auto sp_fd = open(sp.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            if (sp_fd == -1) {
                perror("open file failed:");
                continue;
            }
            redirect_fd(d, sp_fd);
        }
        for (auto itp : ard) {
            redirect_fd(itp.dest, itp.src);
        }

    }

    void Task::check_rd(const std::vector<RedirectFD> &fds) {
        for (auto itp : fds) {
            if (rd_file.find(itp.dest) != end(rd_file)) {
                throw MultiRedirectException();
            }
        }
    }

    /* AtomTask */

    void AtomTask::set_argv(ArgumentVector v) {
        argv = std::move(v);
    }

    void AtomTask::append_arg(std::string arg) {
        argv.emplace_back(std::move(arg));
    }

    void AtomTask::clear_arg() {
        argv.clear();
    }

    /* detach */

    std::list<pid_t> detached_pid;

    void detach_pid(pid_t p) {
        detached_pid.push_back(p);
    }

    void check_detach() {
        using iter_pid = std::list<pid_t>::iterator;
        std::vector<iter_pid> to_removed;
        for (auto it = begin(detached_pid); it != end(detached_pid); ++it) {
            if (waitpid(*it, nullptr, WNOHANG)) {
                to_removed.push_back(it);
            }
        }
        for (auto it : to_removed) {
            detached_pid.erase(it);
        }
    }

    /* tool */

    int redirect_fd(int dest, int fd) {
        if (dest != fd) {
            if (dup2(fd, dest) == -1) {
                perror("redirect:");
                return -1;
            }
            if (close(fd)) {
                return -1;
            }
            return 0;
        }
        return 0;
    }

}