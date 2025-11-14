# GreenDinosaurShellR1

一个简单的Shell实现。为 “晨枫学长请和我交往v3.0”提供动力。

## 特性

- 启动进程, 程序应位于 `PATH` 变量所列出的目录之下.
- 内建基本命令
    - ls
    - echo
    - cat
    - mkdir
    - rm
    - cd
    - pwd
    - wc
- 管道： 使用与 `Bash` 相同的 `|` 串联两个命令的标准输入和输出
- 重定向: `>`, `>>`, `<` 可用于重定向到文件.
- 子进程分离: 使用后缀的 `&` 符号, 将子进程从Shell分离,使得子进程无需等待任务结束

注意:未实现 `exit` 请使用 `EOF` (Ctrl+D) 退出程序.

## 构建

构建shell

```shell
make all
```

清除临时文件

```shell
make clean
```

清除所有临时文件

```shell
make clean-all
```

> 程序依赖于 **flex** 和 **bison** 生成语法分析器. 如果环境中不存在该套件清除所有临时文件会导致无法构建

## 运行

```shell
chmod +x ./shell
./shell
```