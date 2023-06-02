#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#include "semantics.h"

double Scale_x = 1;
double Scale_y = 1;
double Origin_x = 0;
double Origin_y = 0;
double Rot_angle = 0;
double Parameter = 0;

char pixColor[20] = "blue";
char pixType[20] = ".";
int pixSize = 5;


ExprNode_Ptr makeExprNode(enum yytokentype opcode, ...)
{
    ExprNode_Ptr ptr = (ExprNode_Ptr)malloc(sizeof(ExprNode));
    ptr->OpCode = opcode;
    va_list arg_ptr;
    va_start(arg_ptr, opcode);
    switch (opcode)
    {
    case CONST_ID:
        ptr->content.CaseConst = (double)va_arg(arg_ptr, double);
        break;
    case T:
        ptr->content.CaseParmPtr = &Parameter;
        break;
    case FUNC:
        ptr->content.CaseFunc.MathFuncPtr = (t_func)va_arg(arg_ptr, t_func);
        ptr->content.CaseFunc.child = (ExprNode_Ptr)va_arg(arg_ptr, ExprNode_Ptr);
        break;    
    default:
        ptr->content.CaseOperator.left = (ExprNode_Ptr)va_arg(arg_ptr, ExprNode_Ptr);
        ptr->content.CaseOperator.right = (ExprNode_Ptr)va_arg(arg_ptr, ExprNode_Ptr);
        break;
    }
    va_end(arg_ptr);
    return ptr;
}

double getExprValue(ExprNode_Ptr root)
{
    if(NULL == root) {
        return 0.0;
    }
    switch(root->OpCode)
    {
    case PLUS:
        return getExprValue(root->content.CaseOperator.left) 
               + getExprValue(root->content.CaseOperator.right);
    case MINUS:
        return getExprValue(root->content.CaseOperator.left) 
               - getExprValue(root->content.CaseOperator.right);
    case MUL:
        return getExprValue(root->content.CaseOperator.left) 
               * getExprValue(root->content.CaseOperator.right);
    case DIV:
        return getExprValue(root->content.CaseOperator.left) 
               / getExprValue(root->content.CaseOperator.right);
    case POWER:
        return pow(getExprValue(root->content.CaseOperator.left),
                   getExprValue(root->content.CaseOperator.right));
    case FUNC:
        return (*(root->content.CaseFunc.MathFuncPtr))(getExprValue(root->content.CaseFunc.child));
    case CONST_ID:
        return root->content.CaseConst;
    case T:
        return *(root->content.CaseParmPtr);

    default: return 0.0;
    }
}

void drawLoop(ExprNode_Ptr start_tree, ExprNode_Ptr end_tree,
              ExprNode_Ptr step_tree,
              ExprNode_Ptr x_tree, ExprNode_Ptr y_tree)
{
    FILE* canvas;
    FILE* style;

    canvas = fopen("./canvas.txt", "w");
    style = fopen("./style.txt", "w");

    if(canvas == NULL)
    {
        printf("dreaw canvas is NULL!\n");

    }
    double x_val, y_val,
           start_val, end_val, step_val;
    double *p_T_value = &Parameter;

    start_val = getExprValue(start_tree);
    end_val   = getExprValue(end_tree);
    step_val  = getExprValue(step_tree);

    for(*p_T_value = start_val; *p_T_value < end_val; *p_T_value += step_val)
    {
        calcCoord(x_tree, y_tree, &x_val, &y_val);
        //drawPixel((unsigned long)x_val, (unsigned long)y_val);  //in ui.h

        char str_x[100];
        char str_y[100];

        sprintf(str_x, "%lu\n", (unsigned long)x_val);
        sprintf(str_y, "%lu\n", (unsigned long)y_val);

        fputs(str_x, canvas);
        fputs(str_y, canvas);


    }

    char str_size[20];
    sprintf(str_size, "%d", pixSize);

    fputs(pixColor, style);
    fputs("\n", style);
    fputs(pixType, style);
    fputs("\n", style);
    fputs(str_size, style);
    fputs("\n", style);

    fclose(style);

    fclose(canvas);
}

void calcCoord(ExprNode_Ptr x_tree, ExprNode_Ptr y_tree,
               double *ptr_x_value, double *ptr_y_value)
{
    double x_val, x_temp, y_val;

    x_val = getExprValue(x_tree);
    y_val = getExprValue(y_tree);

    x_val *= Scale_x;
    y_val *= Scale_y;

    x_temp = x_val * cos(Rot_angle) + y_val * sin(Rot_angle);
    y_val  = y_val * cos(Rot_angle) - x_val * sin(Rot_angle);
    x_val = x_temp;

    x_val += Origin_x;
    y_val += Origin_y;

    if(NULL != ptr_x_value) *ptr_x_value = x_val;
    if(NULL != ptr_y_value) *ptr_y_value = y_val;
}

