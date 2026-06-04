#include <stdio.h>

int main(void)
{
    char name[50];
    char board[50];
    
    printf("========================================\n");
    printf("   Embedded System Lab - HelloWorld v2.0\n");
    printf("========================================\n");
    
    // 使用 scanf 实现键盘输入
    printf("请输入您的名字: ");
    scanf("%s", name);
    
    printf("请输入开发板型号: ");
    scanf("%s", board);
    
    // 显示输出
    printf("\n--- 输出信息 ---\n");
    printf("你好, %s!\n", name);
    printf("使用的开发板: %s\n", board);
    printf("程序运行成功!\n");
    printf("========================================\n");
    
    return 0;
}

