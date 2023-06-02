%{
    #define YYSTYPE struct ExprNode *
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include "semantics.h"


    extern unsigned char *yytext;
    extern struct Token tokens;
    extern FILE *yyin;
    extern unsigned int LineNo;
    char SrcFilePath[2000];

    extern int yylex(void);
    void yyerror(const char* Msg);
    

    extern int initScanner(const char * FileName);
    extern void closeScanner();
%}
%token ORIGIN SCALE ROT IS TO STEP DRAW FOR FROM T RED GREEN BLUE DOT CROSS DASH COLOR TYPE SMALL MID BIG SIZE//保留字
%token CONST_ID FUNC
%token SEMICO L_BRACKET R_BRACKET COMMA  //分隔符
%token ERRORTOKEN
%left PLUS MINUS
%left MUL DIV
%right UNSUB
%right POWER

%%
program : 
        | program statement SEMICO
        {
            printf("program statement SEMICO read\n");
        }
        ;
statement : originStatement 
          | scaleStatement 
          | rotStatement    
          | forStatement
          | colorStatement
          | typeStatement
          | sizeStatement
          ;
originStatement : ORIGIN IS L_BRACKET 
                  expression COMMA expression R_BRACKET
                  {
                    Origin_x = getExprValue($4);
                    Origin_y = getExprValue($6);
                  }
                ;
scaleStatement : SCALE IS L_BRACKET 
                 expression COMMA expression R_BRACKET
                 {
                    printf("scale read\n");
                    printf("origin read\n");
                    Scale_x = getExprValue($4);
                    Scale_y = getExprValue($6);
                  }
               ;
rotStatement : ROT IS expression
               {
                printf("rot read\n");
                Rot_angle = getExprValue($3);
               }
             ;
forStatement : FOR T FROM expression TO expression STEP expression 
               DRAW L_BRACKET expression COMMA expression R_BRACKET
               {
                    printf("for read\n");
                    drawLoop($4, $6, $8, $11, $13);
                    printf("draw finished\n");
               }
             ;
colorStatement: COLOR IS RED        {strcpy(pixColor, "red");}
              | COLOR IS GREEN      {strcpy(pixColor, "red");}
              | COLOR IS BLUE       {strcpy(pixColor, "red");}
typeStatement: TYPE IS CROSS        {strcpy(pixType, "+");}
             | TYPE IS DOT          {strcpy(pixType, ".");}
             | TYPE IS DASH         {strcpy(pixType, "_");}
sizeStatement: SIZE IS SMALL        {pixSize = 1}
             | SIZE IS MID          {pixSize = 5}
             | SIZE IS BIG          {pixSize = 20}

expression : T                                       {$$ = makeExprNode(T);}
           | CONST_ID                                {$$ = makeExprNode(CONST_ID, tokens.value);}
           | expression PLUS expression              {$$ = makeExprNode(PLUS, $1, $3);}
           | expression MINUS expression             {$$ = makeExprNode(MINUS, $1, $3);}
           | expression MUL expression               {$$ = makeExprNode(MUL, $1, $3);}
           | expression DIV expression               {$$ = makeExprNode(DIV, $1, $3);}
           | expression POWER expression             {$$ = makeExprNode(POWER, $1, $3);}
           | L_BRACKET expression R_BRACKET          {$$ = $2;}
           | PLUS expression %prec UNSUB             {$$ = $2;}
           | MINUS expression                        {$$ = makeExprNode(MINUS, makeExprNode(CONST_ID, 0), $2);}
           | FUNC L_BRACKET expression R_BRACKET     {$$ = makeExprNode(FUNC, tokens.FuncPtr, $3);}
%%

void yyerror(const char* Msg) 
{
  printf("ERROR: %s on line %u: %s", Msg, LineNo, yytext);
}

extern int initScanner(const char * FileName)
{
    yyin = fopen(FileName, "r");
    return 1;
}

extern void closeScanner()
{
    fclose(yyin);
}



int InitScanner(char* filename){

    yyin = fopen(filename, "r");

    if(yyin == NULL ){
        printf("Failed to open file %s\n", filename);
        return 0;
    }

    printf("open succeed\n");

    return 1;
}

int CloseScanner(){
    fclose(yyin);
    return 0;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage: %s file\n", argv[1]);
    }

    strcpy(SrcFilePath, argv[1]);

    printf("Src = %s\n", SrcFilePath);

    if( 1 != InitScanner(SrcFilePath)){
        printf("init failed\n");
        return 1;
    }


    printf("yyparse start\n");
    yyparse();

    printf("yyparse finish\n");
    CloseScanner();

    printf("Finish\n");
    return 0;
}