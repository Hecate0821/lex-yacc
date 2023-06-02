适用于Apple Silicon的MacOS
MacBook Air M2
MacOS:13.2.1 (22D68)
CLion 2022.3.2
bison (GNU Bison) 2.3
flex 2.6.4 Apple(flex-34)

与Win平台的区别：
yywrap会自动声明定义，不需要自己写
yyparse不会在y.tab.h中声明，要在.h中加声明或者直接把主函数加在.y文件辅助函数部分
yyerror不会用

输出点坐标文件canvas.txt和样式文件style.txt

command:
flex -o scanner.c scanner.l
bison -d parser.y
gcc -o main semantics.c scanner.c parser.tab.c -lstdc++

增加了设定绘图颜色，点的大小和样式
代码有参考