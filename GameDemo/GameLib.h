#ifndef GAMELIB_H_INCLUDE
#define GAMELIB_H_INCLUDE
/*****************************************
 *
 * Name: GameLib.h
 * Description: 用来定义一些核心的库函数
 * Date: 2018-06-25
 *
 ****************************************/
#include<stdio.h>
//模仿window的getch()函数
int getch(int d);
//设置光标位置
void SetPosition(char direct, int n);
//设置标题函数
void SetConsoleTitle(char * name);
//设置文字的前景色和背景色
void SetColor(const char *msg, const int displayStyle, const int foreColor, const int backColor);
//得到随机数
int GetRandom(int min, int max); 

#endif  // GAMELIB_H_INCLUDE
