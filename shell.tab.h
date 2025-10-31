/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_SHELL_SHELL_TAB_H_INCLUDED
# define YY_SHELL_SHELL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef SHELL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SHELL_DEBUG 1
#  else
#   define SHELL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SHELL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SHELL_DEBUG */
#if SHELL_DEBUG
extern int shell_debug;
#endif

/* Token kinds.  */
#ifndef SHELL_TOKENTYPE
# define SHELL_TOKENTYPE
  enum shell_tokentype
  {
    SHELL_EMPTY = -2,
    SHELL_EOF = 0,                 /* "end of file"  */
    SHELL_error = 256,             /* error  */
    SHELL_UNDEF = 257,             /* "invalid token"  */
    TPIPE = 258,                   /* TPIPE  */
    EOL = 259,                     /* EOL  */
    SEMICOLON = 260,               /* SEMICOLON  */
    RD_IN = 261,                   /* RD_IN  */
    RD_OUT = 262,                  /* RD_OUT  */
    RD_TR = 263,                   /* RD_TR  */
    AND_SYM = 264,                 /* AND_SYM  */
    ARG = 265                      /* ARG  */
  };
  typedef enum shell_tokentype shell_token_kind_t;
#endif

/* Value type.  */
#if ! defined SHELL_STYPE && ! defined SHELL_STYPE_IS_DECLARED
union SHELL_STYPE
{
#line 12 "shell.y"

    const char *arg;
    struct AtomTask *t;
    struct PipelineTask *p;
    struct TaskList *l;

#line 89 "shell.tab.h"

};
typedef union SHELL_STYPE SHELL_STYPE;
# define SHELL_STYPE_IS_TRIVIAL 1
# define SHELL_STYPE_IS_DECLARED 1
#endif


extern SHELL_STYPE shell_lval;


int shell_parse (void);


#endif /* !YY_SHELL_SHELL_TAB_H_INCLUDED  */
