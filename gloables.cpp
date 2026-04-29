/* 猜数游戏——任务6 代码 
   gloables.cpp
*/

#include "guess.h"

// 全局变量定义（这里才是真正的定义，分配内存）
int gameMode = 0;          // 当前游戏模式
int magic = 0;             // 计算机想的数(1-100)
int guess = 0;             // 用户猜的数
int attempt = 1;           // 当前尝试次数
int maxAttempts = 10;      // 最大尝试次数
int gameState = 0;         // 游戏状态：0-选择模式，1-游戏中，2-游戏结束
char history[100][100];    // 历史记录
int historyCount = 0;      // 历史记录数量