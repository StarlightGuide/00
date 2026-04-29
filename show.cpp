/* 猜数游戏——任务6 代码 
   源文件 show.cpp
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

// 初始化图形窗口
void InitGraphics()
{
    initgraph(500, 600);
    setbkcolor(RGB(240, 240, 245));
    cleardevice();
    settextstyle(20, 0, _T("宋体"));
}

// 绘制主菜单
void DrawMainMenu()
{
    cleardevice();
    // 播放开始界面音效
    PlayStartSound();

    // 绘制标题 - 居中放置
    settextcolor(RGB(0, 0, 0));
    settextstyle(36, 0, _T("黑体"));

    // 计算标题居中位置
    int titleWidth = textwidth(_T("猜数游戏"));
    int titleX = (500 - titleWidth) / 2;
    outtextxy(titleX, 60, _T("猜数游戏"));

    settextstyle(22, 0, _T("黑体"));
    settextcolor(RGB(20, 20, 20));
    outtextxy(100, 130, _T("请选择游戏模式："));

    // 绘制模式选择按钮
    setbkmode(TRANSPARENT);
    Button btnMode1 = { 100, 200, 300, 60, "模式1: 只猜一次", RGB(100, 200, 100) };
    Button btnMode2 = { 100, 280, 300, 60, "模式2: 直到猜对为止", RGB(100, 150, 200) };
    Button btnMode3 = { 100, 360, 300, 60, "模式3: 最多猜10次", RGB(200, 150, 100) };

    DrawButton(btnMode1);
    DrawButton(btnMode2);
    DrawButton(btnMode3);

    // 绘制游戏规则
    settextstyle(14, 0, _T("宋体"));
    settextcolor(BLUE);
    outtextxy(100, 450, _T("游戏规则："));
    outtextxy(120, 470, _T("1. 计算机随机生成1~100之间的整数"));
    outtextxy(120, 490, _T("2. 你需要在限定次数内猜出这个数"));
    outtextxy(120, 510, _T("3. 每次猜测会提示太大或太小"));
    outtextxy(120, 530, _T("4. 根据模式不同，猜数次数限制不同"));
}

// 绘制游戏界面
void DrawGameScreen()
{
    cleardevice();
    // 绘制标题和模式信息
    settextcolor(RGB(0, 0, 0));
    settextstyle(24, 0, _T("黑体"));

    char modeText[50];
    if (gameMode == MODE_ONCE)
        sprintf_s(modeText, "模式1: 只猜一次");
    else if (gameMode == MODE_UNLIMITED)
        sprintf_s(modeText, "模式2: 直到猜对为止");
    else if (gameMode == MODE_10_TIMES)
        sprintf_s(modeText, "模式3: 最多猜10次");

    outtextxy(150, 30, modeText);

    // 绘制当前尝试次数
    settextstyle(18, 0, _T("宋体"));
    char attemptText[50];
    sprintf_s(attemptText, "第 %d 次尝试", attempt);
    outtextxy(200, 80, attemptText);

    // 绘制输入框（显示最后一次输入的数字）
    setfillcolor(RGB(255, 255, 255));
    fillrectangle(150, 150, 350, 200);

    setlinecolor(RGB(100, 100, 100));
    rectangle(150, 150, 350, 200);

    settextstyle(28, 0, _T("Arial"));
    settextcolor(RGB(0, 0, 0));

    // 显示最后一次猜测的数字
    if (historyCount > 0)
    {
        char lastGuess[10] = "";
        char* p = strchr(history[historyCount - 1], ':');
        if (p)
        {
            p += 2;
            for (int i = 0; i < 3 && p[i] >= '0' && p[i] <= '9'; i++)
            {
                lastGuess[i] = p[i];
            }
            outtextxy(180, 160, lastGuess);
        }
        else
        {
            outtextxy(180, 160, _T(" "));
        }
    }
    else
    {
        outtextxy(180, 160, _T(" "));
    }

    // 绘制输入提示
    settextstyle(14, 0, _T("宋体"));
    settextcolor(RGB(0, 0, 0));
    outtextxy(150, 210, _T("请点击【输入数字】按钮开始猜数"));

    // 绘制按钮
    Button btnBack = { 350, 500, 100, 40, "返回", RGB(200, 100, 100) };
    Button btnInput = { 350, 400, 100, 40, "输入数字", RGB(100, 200, 100) };
    Button btnReset = { 350, 450, 100, 40, "重置", RGB(200, 150, 100) };

    DrawButton(btnBack);
    DrawButton(btnInput);
    DrawButton(btnReset);

    // 绘制历史记录
    settextstyle(14, 0, _T("宋体"));
    settextcolor(BLUE);
    outtextxy(50, 250, _T("历史记录："));

    int startY = 280;
    int maxDisplay = 8;
    int startIdx = (historyCount > maxDisplay) ? historyCount - maxDisplay : 0;
    for (int i = startIdx; i < historyCount && i < startIdx + maxDisplay; i++)
    {
        outtextxy(70, startY, history[i]);
        startY += 25;
    }

    // 绘制剩余次数提示
    if (gameMode == MODE_10_TIMES)
    {
        char remainingText[50];
        sprintf_s(remainingText, "剩余次数: %d", maxAttempts - attempt + 1);
        settextcolor(RGB(0, 0, 0));
        outtextxy(150, 120, remainingText);
    }
}

// 绘制结果屏幕
void DrawResultScreen(int result)
{
    cleardevice();
    // 根据游戏结果播放对应音效
    if (result == 1)
    {
        PlayWinnerSound();  // 胜利音效
    }
    else
    {
        PlayDeadSound();    // 失败音效
    }

    settextcolor(RGB(0, 0, 0));
    settextstyle(28, 0, _T("黑体"));

    if (result == 1)
    {
        // 计算"正确！"的居中位置
        int textWidth1 = textwidth(_T("正确！"));
        int textX1 = (500 - textWidth1) / 2;
        outtextxy(textX1, 100, _T("正确！"));

        // 显示答案
        settextstyle(20, 0, _T("Arial"));
        char answerText[50];
        sprintf_s(answerText, "答案: %d", magic);
        int textWidth2 = textwidth(answerText);
        int textX2 = (500 - textWidth2) / 2;
        outtextxy(textX2, 160, answerText);

        // 显示尝试次数
        char attemptsText[50];
        sprintf_s(attemptsText, "共尝试了 %d 次", attempt);
        int textWidth3 = textwidth(attemptsText);
        int textX3 = (500 - textWidth3) / 2;
        outtextxy(textX3, 200, attemptsText);
    }
    else
    {
        // 计算"游戏结束！"的居中位置
        int textWidth1 = textwidth(_T("游戏结束！"));
        int textX1 = (500 - textWidth1) / 2;
        outtextxy(textX1, 100, _T("游戏结束！"));

        // 显示答案
        settextstyle(20, 0, _T("Arial"));
        char answerText[50];
        sprintf_s(answerText, "正确答案: %d", magic);
        int textWidth2 = textwidth(answerText);
        int textX2 = (500 - textWidth2) / 2;
        outtextxy(textX2, 160, answerText);

        // 显示尝试次数
        if (gameMode == MODE_ONCE)
        {
            int textWidth3 = textwidth(_T("只猜一次模式结束"));
            int textX3 = (500 - textWidth3) / 2;
            outtextxy(textX3, 200, _T("只猜一次模式结束"));
        }
        else if (gameMode == MODE_10_TIMES)
        {
            int textWidth3 = textwidth(_T("10次机会已用完"));
            int textX3 = (500 - textWidth3) / 2;
            outtextxy(textX3, 200, _T("10次机会已用完"));
        }
    }

    // 计算按钮的居中x坐标
    int btnWidth = 150;  // 按钮宽度
    int btnX = (500 - btnWidth) / 2;  // 按钮居中的x坐标

    // 绘制按钮 - 上下排列，水平居中
    Button btnPlayAgain = { btnX, 350, btnWidth, 50, "再玩一次", RGB(100, 200, 100) };
    Button btnBackToMenu = { btnX, 420, btnWidth, 50, "返回菜单", RGB(200, 150, 100) };

    DrawButton(btnPlayAgain);
    DrawButton(btnBackToMenu);
}

// 绘制按钮
void DrawButton(Button btn)
{
    setfillcolor(btn.color);
    fillrectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);

    setlinecolor(RGB(50, 50, 50));
    rectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);

    settextcolor(RGB(255, 255, 255));
    settextstyle(18, 0, _T("宋体"));
    setbkmode(TRANSPARENT);

    // 计算文本居中位置
    int textWidth = textwidth(btn.text);
    int textHeight = textheight(btn.text);
    int textX = btn.x + (btn.width - textWidth) / 2;
    int textY = btn.y + (btn.height - textHeight) / 2;

    outtextxy(textX, textY, btn.text);
}

// 检查按钮是否被点击
int IsButtonClicked(Button btn, int x, int y)
{
    return (x >= btn.x && x <= btn.x + btn.width && y >= btn.y && y <= btn.y + btn.height);
}

// 生成一个1~100之间的随机数
void GenerateNumber()
{
    magic = rand() % 100 + 1;
}

// 检查用户输入是否有效
int IsValidInput(int num)
{
    return (num >= 1 && num <= 100);
}
