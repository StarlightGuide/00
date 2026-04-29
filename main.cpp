/* 猜数游戏——任务6 代码 
   源文件main.cpp
*/
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "guess.h"   //新增头文件

int main()
{
    srand(time(NULL));
    InitGraphics();
    DrawMainMenu();

    while (true)
    {
        // 检查鼠标消息
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                int x = msg.x;
                int y = msg.y;

                Button btnMode1 = { 100, 200, 300, 60, "模式1: 只猜一次", RGB(100, 200, 100) };
                Button btnMode2 = { 100, 280, 300, 60, "模式2: 直到猜对为止", RGB(100, 150, 200) };
                Button btnMode3 = { 100, 360, 300, 60, "模式3: 最多猜10次", RGB(200, 150, 100) };

                if (gameState == 0)
                {
                    if (IsButtonClicked(btnMode1, x, y))
                    {
                        gameMode = MODE_ONCE;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    }
                    else if (IsButtonClicked(btnMode2, x, y))
                    {
                        gameMode = MODE_UNLIMITED;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        maxAttempts = 100;
                        DrawGameScreen();
                    }
                    else if (IsButtonClicked(btnMode3, x, y))
                    {
                        gameMode = MODE_10_TIMES;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        maxAttempts = 10;
                        DrawGameScreen();
                    }
                }

                if (gameState == 1)
                {
                    Button btnBack = { 350, 500, 100, 40, "返回", RGB(200, 100, 100) };
                    Button btnInput = { 350, 400, 100, 40, "输入数字", RGB(100, 200, 100) };
                    Button btnReset = { 350, 450, 100, 40, "重置", RGB(200, 150, 100) };

                    if (IsButtonClicked(btnBack, x, y))
                    {
                        gameState = 0;
                        DrawMainMenu();
                    }
                    else if (IsButtonClicked(btnInput, x, y))
                    {
                        // 根据当前游戏模式调用对应的功能函数
                        switch (gameMode)
                        {
                        case MODE_ONCE:
                            ModeOnceFunction();
                            break;
                        case MODE_UNLIMITED:
                            ModeUnlimitedFunction();
                            break;
                        case MODE_10_TIMES:
                            Mode10TimesFunction();
                            break;
                        }
                    }
                    else if (IsButtonClicked(btnReset, x, y))
                    {
                        // 重置当前游戏
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    }
                }

                if (gameState == 2)
                {
                    Button btnPlayAgain = { 200, 350, 150, 50, "再玩一次", RGB(100, 200, 100) };
                    Button btnBackToMenu = { 200, 420, 150, 50, "返回菜单", RGB(200, 150, 100) };

                    if (IsButtonClicked(btnPlayAgain, x, y))
                    {
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    }
                    else if (IsButtonClicked(btnBackToMenu, x, y))
                    {
                        gameState = 0;
                        DrawMainMenu();
                    }
                }
            }
        }

        Sleep(10);
    }

    closegraph();
    return 0;
}
