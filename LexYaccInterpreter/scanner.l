%{
    #include "parser.tab.h"
    #include "semantics.h"
    #include <stdlib.h>
    #include <math.h>
    void yyerror(char*);
    unsigned int LineNo;
    struct Token tokens;
%}

%option case-insensitive

name    [a-z]([_a-z0-9])*
number  [0-9]+
ws      [ \t]+
newline \n


%x comment_entry c_comment_entry

%%
"//"|"--" {BEGIN comment_entry;}
<comment_entry>.
<comment_entry>\n {BEGIN 0; LineNo ++;}

"/*" {BEGIN c_comment_entry;}
<c_comment_entry>"*/" {BEGIN 0;}
<c_comment_entry>.
<c_comment_entry>"\n" {LineNo ++;}

"+"  {return PLUS;}
"-"  {return MINUS;}
"*"  {return MUL;}
"/"  {return DIV;}
","  {return COMMA;}
";"  {return SEMICO;}
"("  {return L_BRACKET;}
")"  {return R_BRACKET;}
"**" {return POWER;}

{ws}
{newline} {LineNo ++;}

"origin"  {return ORIGIN;}
"scale"   {return SCALE;}
"rot"     {return ROT;}
"is"      {return IS;}
"for"     {return FOR;}
"from"    {return FROM;}
"to"      {return TO;}
"step"    {return STEP;}
"draw"    {return DRAW;}
"t"       {return T;}
"color"   {return COLOR;}
"type"    {return TYPE;}
"size"    {return SIZE;}

"red"       {return RED;}
"green"     {return GREEN;}
"blue"      {return BLUE;}

"dot"       {return DOT;}
"cross"     {return CROSS;}
"dash"      {return DASH;}

"small"     {return SMALL;}
"mid"       {return MID;}
"BIG"       {return BIG;}

"pi"   {tokens.type = CONST_ID; tokens.value = 3.1415926; return CONST_ID;}
"e"    {tokens.type = CONST_ID; tokens.value = 2.71828;return CONST_ID;}
"sin"  {tokens.type = FUNC; tokens.FuncPtr = sin; return FUNC;}
"cos"  {tokens.type = FUNC; tokens.FuncPtr = cos; return FUNC;}
"tan"  {tokens.type = FUNC; tokens.FuncPtr = tan; return FUNC;}
"ln"   {tokens.type = FUNC; tokens.FuncPtr = log; return FUNC;}
"exp"  {tokens.type = FUNC; tokens.FuncPtr = exp; return FUNC;}
"sqrt" {tokens.type = FUNC; tokens.FuncPtr = sqrt; return FUNC;}

{number}(\.{number})? {tokens.type = CONST_ID; tokens.value = atof(yytext); return CONST_ID;}
{name} {return ERRORTOKEN;}
. {return ERRORTOKEN;}

%%

int yywrap(void)
{
    return 1;
}