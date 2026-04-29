/* 猜数游戏——任务6 代码 
   sound.cpp
*/
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "guess.h"   //新增头文件

// 播放开始音效函数
void PlayStartSound()
{
    // 异步播放开始音效，不阻塞程序运行
    PlaySound(TEXT("D:\\code\\start.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// 播放胜利音效函数
void PlayWinnerSound()
{
    // 异步播放胜利音效，不阻塞程序运行
    PlaySound(TEXT("D:\\code\\winner.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

// 播放失败音效函数
void PlayDeadSound()
{
    // 异步播放失败音效，不阻塞程序运行
    PlaySound(TEXT("D:\\code\\dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
}