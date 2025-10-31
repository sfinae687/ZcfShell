Task_OBJ := building_task.o \
	BuiltinTask.o \
	CompositeTask.o \
	ExecutableTask.o \
	task.o \

builtin_cmd_OBJ := builtin/cat.o \
        builtin/cd.o \
        builtin/ls.o \
        builtin/mkdir.o \
        builtin/pwd.o \
        builtin/rm.o \
        builtin/wc.o \
		builtin/echo.o

parser_OBJ := shell.tab.o \
	lex.shell.o

CFLAGS := "-g" "-static-libgcc"
CXXFLAGS := "-std=c++11" "-g" "-static-libstdc++"

all: shell

shell: shell.cpp $(builtin_cmd_OBJ) builtin.o $(Task_OBJ) $(parser_OBJ)
	$(CXX) $(CXXFLAGS) -o shell $^
	chmod +x ./shell

builtin.o : builtin.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(Task_OBJ) : %.o : %.cpp builtin.o
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$(parser_OBJ) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

shell.tab.c : shell.y
	bison -H shell.y

lex.shell.c : shell.l
	flex shell.l

$(builtin_cmd_OBJ) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean: 
	rm $(parser_OBJ) $(builtin_cmd_OBJ) $(Task_OBJ) ./shell

clean-all: clean
	rm shell.tab.h lex.shell.c shell.tab.c