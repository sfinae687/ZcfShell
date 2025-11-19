#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_long_format(const char *path, const char *filename) {
    struct stat file_stat;
    char full_path[1024];
    struct passwd *pwd;
    struct group *grp;
    struct tm *time_info;
    char time_buffer[80];
    char perm_string[11];

    // 构建完整文件路径
    snprintf(full_path, sizeof(full_path), "%s/%s", path, filename);

    // 获取文件状态信息
    if (lstat(full_path, &file_stat) == -1) {
        perror("lstat");
        return;
    }

    // 1. 文件类型与权限
    // 确定文件类型
    perm_string[0] = S_ISDIR(file_stat.st_mode) ? 'd' :
                     S_ISLNK(file_stat.st_mode) ? 'l' :
                     S_ISCHR(file_stat.st_mode) ? 'c' :
                     S_ISBLK(file_stat.st_mode) ? 'b' :
                     S_ISFIFO(file_stat.st_mode) ? 'p' :
                     S_ISSOCK(file_stat.st_mode) ? 's' : '-';
    // 转换权限位为 rwx 字符串
    perm_string[1] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-';
    perm_string[2] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-';
    perm_string[3] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-';
    perm_string[4] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-';
    perm_string[5] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-';
    perm_string[6] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-';
    perm_string[7] = (file_stat.st_mode & S_IROTH) ? 'r' : '-';
    perm_string[8] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-';
    perm_string[9] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-';
    perm_string[10] = '\0';

    // 2. 硬链接数
    nlink_t nlink = file_stat.st_nlink;

    // 3. 文件所有者与所属组
    pwd = getpwuid(file_stat.st_uid);
    grp = getgrgid(file_stat.st_gid);
    const char *user_name = pwd ? pwd->pw_name : "UNKNOWN";
    const char *group_name = grp ? grp->gr_name : "UNKNOWN";

    // 4. 文件大小
    off_t size = file_stat.st_size;

    // 5. 最后修改时间
    time_info = localtime(&(file_stat.st_mtime));
    strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", time_info);

    // 打印所有信息
    printf("%s %lu %s %s %ld %s %s\n", 
           perm_string, (unsigned long)nlink, user_name, group_name, 
           (long)size, time_buffer, filename);
}

extern "C" int ls_main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    const char *path = "."; // 默认当前目录
    int long_format = 0;    // 是否启用 -l 选项的标志

    // 简单的参数解析
    if (argc == 2 && strcmp(argv[1], "-l") == 0) {
        long_format = 1;
    } else if (argc == 2) {
        // 这里可以扩展为处理指定目录路径
        path = argv[1];
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [-l] [directory]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 打开目录
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // 读取并遍历目录中的每一个条目
    while ((entry = readdir(dir)) != NULL) {
        // 跳过隐藏文件（以 '.' 开头），如需显示可移除此条件
        if (entry->d_name[0] == '.') {
            continue;
        }

        if (long_format) {
            // 长格式输出
            print_long_format(path, entry->d_name);
        } else {
            // 简单输出文件名
            printf("%s  ", entry->d_name);
        }
    }

    // 如果不是长格式，简单输出后换行
    if (!long_format) {
        printf("\n");
    }

    // 关闭目录
    closedir(dir);
    return 0;
}