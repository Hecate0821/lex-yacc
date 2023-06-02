/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ORIGIN = 258,
     SCALE = 259,
     ROT = 260,
     IS = 261,
     TO = 262,
     STEP = 263,
     DRAW = 264,
     FOR = 265,
     FROM = 266,
     T = 267,
     RED = 268,
     GREEN = 269,
     BLUE = 270,
     DOT = 271,
     CROSS = 272,
     DASH = 273,
     COLOR = 274,
     TYPE = 275,
     SMALL = 276,
     MID = 277,
     BIG = 278,
     SIZE = 279,
     CONST_ID = 280,
     FUNC = 281,
     SEMICO = 282,
     L_BRACKET = 283,
     R_BRACKET = 284,
     COMMA = 285,
     ERRORTOKEN = 286,
     MINUS = 287,
     PLUS = 288,
     DIV = 289,
     MUL = 290,
     UNSUB = 291,
     POWER = 292
   };
#endif
/* Tokens.  */
#define ORIGIN 258
#define SCALE 259
#define ROT 260
#define IS 261
#define TO 262
#define STEP 263
#define DRAW 264
#define FOR 265
#define FROM 266
#define T 267
#define RED 268
#define GREEN 269
#define BLUE 270
#define DOT 271
#define CROSS 272
#define DASH 273
#define COLOR 274
#define TYPE 275
#define SMALL 276
#define MID 277
#define BIG 278
#define SIZE 279
#define CONST_ID 280
#define FUNC 281
#define SEMICO 282
#define L_BRACKET 283
#define R_BRACKET 284
#define COMMA 285
#define ERRORTOKEN 286
#define MINUS 287
#define PLUS 288
#define DIV 289
#define MUL 290
#define UNSUB 291
#define POWER 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

