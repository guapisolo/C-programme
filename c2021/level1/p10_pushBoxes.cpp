#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <algorithm>
#include "p10_push.h"
#define FG FOREGROUND_GREEN
#define FR FOREGROUND_RED
#define FB FOREGROUND_BLUE
#define FI FOREGROUND_INTENSITY
#define dd double
#define ll long long 
#define ull unsigned long long 
using namespace std;

// // 生成迷宫：生成树算法
// // 我的做法：随机边权然后最小生成树

int main()
{
    // init_hard_version();
    int task=3;
    while(task<=5)
    {
        switch(task)
        {
            case 1: freopen("round1.in","r",stdin); break;
            case 2: freopen("round2.in","r",stdin); break;
            case 3: freopen("round3.in","r",stdin); break;
            case 4: freopen("round4.in","r",stdin); break;
            case 5: freopen("round5.in","r",stdin); break;
        }
        int to=0,now=1,x,y; //初始化输出一次
        initconsolveScreenBuffer(x,y); Score=0;
        fclose(stdin); 
        to=5; show(output[now],x,y,to); now^=1;
        while(to=get_toward())
        {
            show(output[now],x,y,to);
            if(Score==End) 
                { n=n; break; }
            now^=1;
        }
        LPDWORD num=0;
        // coord.Y=n+3;
        setcolor(output[now],FOREGROUND_GREEN|FOREGROUND_INTENSITY,0); //|BACKGROUND_RED |FOREGROUND_INTENSITY
        WriteConsoleA(output[now],"\n",1,num,NULL);
        WriteConsoleA(output[now],"Congratulations!\n",17,num,NULL);
        SetConsoleActiveScreenBuffer(output[now]); //把缓冲区作为显示的缓冲区
        Sleep(5000);
        task++;
    }
    // puts("YOU WIN!");
    Sleep(1000000);
    return 0;
}

// #：墙
// @：玩家位置
// $：箱子
// ?：目标地点
// %：已经得分

