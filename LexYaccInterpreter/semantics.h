#ifndef _SEMANTICS_H
#define _SEMANTICS_H

#include "parser.tab.h"

extern double Scale_x;
extern double Scale_y;
extern double Origin_x;
extern double Origin_y;
extern double Rot_angle;
extern double Parameter;

extern char pixColor[20];
extern char pixType[20];
extern int pixSize;

extern FILE *yyin;

typedef double (*t_func)(double);

typedef struct ExprNode ExprNode;
typedef struct ExprNode * ExprNode_Ptr;

typedef struct Token
{
    enum yytokentype type;              //记号类别
    double value;                  //数值
    t_func FuncPtr;                //函数指针  
}Token;

struct ExprNode
{
    enum yytokentype OpCode;   //记号种类
    union 
    {
        //二元运算
        struct { ExprNode_Ptr left, right;} CaseOperator;
        //函数
        struct { ExprNode_Ptr child; t_func MathFuncPtr;} CaseFunc;
        //常数
        double CaseConst;
        //参数T
        double * CaseParmPtr;
    }content;
    
};



ExprNode_Ptr makeExprNode(enum yytokentype opcode, ...);

double getExprValue(ExprNode_Ptr root);

void drawLoop(ExprNode_Ptr start_tree, ExprNode_Ptr end_tree,
              ExprNode_Ptr step_tree,
              ExprNode_Ptr x_tree, ExprNode_Ptr y_tree);

void calcCoord(ExprNode_Ptr x_tree, ExprNode_Ptr y_tree,
               double *ptr_x_value, double *ptr_y_value);


#endif