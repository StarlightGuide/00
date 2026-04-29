/* 猜数游戏——任务6 代码 
   头文件 guess.h
*/

#ifndef GUESS_H_INCLUDED
#define GUESS_H_INCLUDED

// 添加必要的头文件
#include <windows.h>  // 提供 COLORREF 类型
#include <graphics.h> // 如果需要 EasyX 的其他类型

// 定义游戏模式
#define MODE_ONCE 1      // 只猜一次
#define MODE_UNLIMITED 2 // 直到猜对为止
#define MODE_10_TIMES 3  // 最多猜10次

// 按钮结构体
typedef struct
{
    int x, y;          // 按钮左上角坐标
    int width, height; // 按钮宽高
    char text[50];     // 按钮文本
    COLORREF color;    // 按钮颜色
} Button;

// 全局变量声明（使用extern，不分配内存）
extern int gameMode;          // 当前游戏模式
extern int magic;             // 计算机想的数(1-100)
extern int guess;             // 用户猜的数
extern int attempt;           // 当前尝试次数
extern int maxAttempts;       // 最大尝试次数
extern int gameState;         // 游戏状态：0-选择模式，1-游戏中，2-游戏结束
extern char history[100][100]; // 历史记录
extern int historyCount;      // 历史记录数量

// 函数原型声明
void InitGraphics();
void DrawMainMenu();
void DrawGameScreen();
void DrawResultScreen(int result);
void DrawButton(Button btn);
int IsButtonClicked(Button btn, int x, int y);
void GenerateNumber();
int IsValidInput(int num);
void PlayStartSound();      // 播放开始音效
void PlayWinnerSound();     // 播放胜利音效
void PlayDeadSound();       // 播放失败音效

// 模式功能函数声明
void ModeOnceFunction();      // 模式1：只猜一次
void ModeUnlimitedFunction(); // 模式2：直到猜对为止
void Mode10TimesFunction();   // 模式3：最多猜10次
#endif // GUESS_H_INCLUDED

