#include "tools.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>
// #include <windows.h>


void SetWindowSize(int cols, int lines)//设置窗口大小
{
    // system("title 贪吃蛇");//设置窗口标题
    // char cmd[30];
    // sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);//一个图形■占两个字符，故宽度乘以2
    // system(cmd);//system(mode con cols=88 lines=88)设置窗口宽度和高度
    // Linux下不需要设置窗口大小，终端大小由用户控制
    printf("\033[2J");
    printf("please set window size is %d x %d \n", cols, lines);
    fflush(stdout);
}

void SetCursorPosition(const int x, const int y)//设置光标位置
{
    // COORD position;
    // position.X = x * 2;
    // position.Y = y;
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    // 使用ANSI转义序列设置光标位置
    printf("\033[%d;%dH", y + 1, x + 1);
    fflush(stdout);
}

void SetColor(int colorID)//设置文本颜色
{
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
    // 在Linux下使用ANSI颜色代码
    switch(colorID) {
        case 0:  // 黑色
            printf("\033[30m");
            break;
        case 1:  // 蓝色
            printf("\033[34m");
            break;
        case 2:  // 绿色
            printf("\033[32m");
            break;
        case 3:  // 青色
            printf("\033[36m");
            break;
        case 4:  // 红色
            printf("\033[31m");
            break;
        case 5:  // 紫色
            printf("\033[35m");
            break;
        case 6:  // 黄色
            printf("\033[33m");
            break;
        case 7:  // 白色
            printf("\033[37m");
            break;
        case 8:  // 灰色
            printf("\033[90m");
            break;
        case 9:  // 亮蓝色
            printf("\033[94m");
            break;
        case 10: // 亮绿色
            printf("\033[92m");
            break;
        case 11: // 亮青色
            printf("\033[96m");
            break;
        case 12: // 亮红色
            printf("\033[91m");
            break;
        case 13: // 亮紫色
            printf("\033[95m");
            break;
        case 14: // 亮黄色
            printf("\033[93m");
            break;
        case 15: // 亮白色
            printf("\033[97m");
            break;
        default:
            printf("\033[0m"); // 默认颜色
            break;
    }
    fflush(stdout);
}

void SetBackColor()//设置文本背景色
{
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    //                         FOREGROUND_BLUE |
    //                         BACKGROUND_BLUE |
    //                         BACKGROUND_GREEN |
    //                         BACKGROUND_RED );
    printf("\033[40;37m");
    fflush(stdout);
}

int kbhit()//判断是否有按键按下
{
    static bool initialized = false;
    static struct termios original_termios;

    if (!initialized) {
        tcgetattr(STDIN_FILENO, &original_termios);
        initialized = true;
    } 

    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0;
}

int getch()
{
    struct termios old_termios, new_termios;
    int ch;

    // 获取当前终端属性
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    // 设置为非规范模式，关闭回显
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    ch = getchar();

    // 恢复原始终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

    return ch;
}