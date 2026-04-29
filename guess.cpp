/* 猜数游戏——任务6 代码 
   源文件 guess.cpp
*/
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "guess.h"   //新增头文件

// 模式1：只猜一次功能
void ModeOnceFunction()
{
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("请输入1~100之间的整数"), _T("猜数游戏"), "", 0, 0, false);

    if (strlen(inputStr) > 0)
    {
        guess = atoi(inputStr);

        if (IsValidInput(guess))
        {
            if (guess == magic)
            {
                sprintf_s(history[historyCount], "第%d次: %d -> 正确！", attempt, guess);
            }
            else if (guess > magic)
            {
                sprintf_s(history[historyCount], "第%d次: %d -> 错误！太大了", attempt, guess);
            }
            else
            {
                sprintf_s(history[historyCount], "第%d次: %d -> 错误！太小了", attempt, guess);
            }
            historyCount++;

            if (guess == magic)
            {
                DrawResultScreen(1);
                gameState = 2;
            }
            else
            {
                DrawResultScreen(0);
                gameState = 2;
            }
        }
        else
        {
            MessageBox(GetHWnd(), _T("请输入1~100之间的整数！"), _T("输入无效"), MB_OK);
        }
    }
}

// 模式2：直到猜对为止功能
void ModeUnlimitedFunction()
{
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("请输入1~100之间的整数"), _T("猜数游戏"), "", 0, 0, false);

    if (strlen(inputStr) > 0)
    {
        guess = atoi(inputStr);
        if (IsValidInput(guess))
        {
            if (guess == magic)
            {
                sprintf_s(history[historyCount], "第%d次: %d -> 正确！", attempt, guess);
                historyCount++;
                DrawResultScreen(1);
                gameState = 2;
            }
            else
            {
                if (guess > magic)
                {
                    sprintf_s(history[historyCount], "第%d次: %d -> 错误！太大了", attempt, guess);
                }
                else
                {
                    sprintf_s(history[historyCount], "第%d次: %d -> 错误！太小了", attempt, guess);
                }
                historyCount++;
                attempt++;
                DrawGameScreen();
            }
        }
        else
        {
            MessageBox(GetHWnd(), _T("请输入1~100之间的整数！"), _T("输入无效"), MB_OK);
        }
    }
}

// 模式3：最多猜10次功能
void Mode10TimesFunction()
{
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("请输入1~100之间的整数"), _T("猜数游戏"), "", 0, 0, false);

    if (strlen(inputStr) > 0)
    {
        guess = atoi(inputStr);

        if (IsValidInput(guess))
        {
            if (guess == magic)
            {
                sprintf_s(history[historyCount], "第%d次: %d -> 正确！", attempt, guess);
                historyCount++;
                DrawResultScreen(1);
                gameState = 2;
            }
            else
            {
                if (guess > magic)
                {
                    sprintf_s(history[historyCount], "第%d次: %d -> 错误！太大了", attempt, guess);
                }
                else
                {
                    sprintf_s(history[historyCount], "第%d次: %d -> 错误！太小了", attempt, guess);
                }
                historyCount++;

                if (attempt >= maxAttempts)
                {
                    DrawResultScreen(0);
                    gameState = 2;
                }
                else
                {
                    attempt++;
                    DrawGameScreen();
                }
            }
        }
        else
        {
            MessageBox(GetHWnd(), _T("请输入1~100之间的整数！"), _T("输入无效"), MB_OK);
        }
    }
}
