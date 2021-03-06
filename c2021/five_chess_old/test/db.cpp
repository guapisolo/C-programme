#ifndef __Double_H
#endif

#define DB_exist
#include "func.h"
using namespace std;
// extern ChessMap cur[N1];
// extern int realmap[N1][N1];

int now;
HANDLE output[2];
COORD coord = {0,0};
DWORD bytes = 0;

//以下为部分借鉴的模板
//双缓冲解决闪屏问题
int cnt=0;

void setcolor(HANDLE hCon,unsigned short ForeColor,unsigned short BackGroundColor)
{
    SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor); //设置文本及背景颜色
}
void initconsolveScreenBuffer()
{
    output[0] = CreateConsoleScreenBuffer(
        GENERIC_WRITE|GENERIC_READ,
        FILE_SHARE_WRITE|FILE_SHARE_READ,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    output[1] = CreateConsoleScreenBuffer(
        GENERIC_WRITE|GENERIC_READ,
        FILE_SHARE_WRITE|FILE_SHARE_READ,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    CONSOLE_CURSOR_INFO cci; //创建光标
    cci.bVisible = 0; //光标可见度
    cci.dwSize = 1; //光标大小
    SetConsoleCursorInfo(output[0],&cci);
    SetConsoleCursorInfo(output[1],&cci);
    now=0;
}
char str[100];

void SwitchHandle()
{
    now^=1; SetConsoleCursorPosition(output[now],coord);
}
void dprintf(const char *s,int len,int Foreground_color,int Background_color,int is_end)
{
    LPDWORD num=0; HANDLE hout=output[now];
    if(!len) len=strlen(s);
    setcolor(hout,Foreground_color,Background_color);
    WriteConsoleA(hout,s,len,num,NULL);
    if(is_end) SetConsoleActiveScreenBuffer(hout), SwitchHandle(); //把缓冲区作为显示的缓冲区
}

#ifdef __Double_H
int main()
{
    initconsolveScreenBuffer();
    dprintf("###\n",0,FG|FI,BB|BG,1);
    dprintf("●●●\n",0,FG|FI,BB,1);
    return 0;
}
#endif
