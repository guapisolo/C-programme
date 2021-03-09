#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <algorithm>
#define dd double
#define ll long long 
#define ull unsigned long long 


// // 生成迷宫：生成树算法
// // 我的做法：随机边权然后最小生成树
using std::swap;
const int n=20; const int m=50; 
struct EDGE{ int x,y,w; }e[n*m*4+5];
int cmp(EDGE aa,EDGE bb)
{
    return aa.w<bb.w;
}
int id(int x,int y){ return m*x+y; }
char data[n+2][m+2];
int fx[5] = {0,-1,1,0,0}, fy[5] = {0,0,0,-1,1}; //*wsad

int randto()
{
    int to=rand()%20+1;
    if(1<=to&&to<=2) return 1; 
    if(3<=to&&to<=5) return 3;
    if(6<=to&&to<=12) return 2;
    if(13<=to&&to<=20) return 4;
}
void build_path(int x,int y,int ex,int ey,int type)
{
    int to; data[x][y]=0;
    while(!(x==ex&&y==ey))
    {
        while(1)
        {
            to=randto();
            if(!(x+fx[to]>=1 && x+fx[to]<n && y+fy[to]>=1 && y+fy[to]<m)) continue;
            if(data[x+fx[to]][y+fy[to]]=='#') 
            {
                x+=fx[to], y+=fy[to];
                data[x][y]=0;
                break;
            }else if(!data[x+fx[to]][y+fy[to]]){ 
                if(!type){ x+=fx[to], y+=fy[to]; break; }
                else{ x=ex, y=ey; break; }
            }
        }
    }
}
void build_puzzle()
{
    build_path(1,1,n-1,m-1,0); //start
    for(int i=1;i<=100;i++)
    {
        int x=rand()%(n-1)+1, y=rand()%(m-1)+1, ex=rand()%(n-1)+1, ey=rand()%(m-1)+1; 
        if(x>ex) swap(x,ex); if(y>ey) swap(y,ey);
        build_path(x,y,ex,ey,1);
    }
}

//以下为部分借鉴的模板
//双缓冲解决闪屏问题
HANDLE output[2];
COORD coord = {0,0};
DWORD bytes = 0;
void initconsolveScreenBuffer();
int show(HANDLE hout,int &x,int &y,int to);
int get_toward();

void SetColor(HANDLE hCon,unsigned short ForeColor,unsigned short BackGroundColor)
{
    // HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //获得缓冲区句柄
    bool flag=SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor); //设置文本及背景颜色
    flag=flag^1; flag=flag^1;
    // SetConsoleTextAttribute(hCon,FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN); //设置文本及背景颜色
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
    //start data
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) data[i][j]='#';
    build_puzzle();
    data[0][1]='W';
}
int get_toward()
{
    int input=getch(),to;
    switch(input)
    {
        case 'w': to=1; break;
        case 's': to=2; break;
        case 'a': to=3; break;
        case 'd': to=4; break;
        case '0': to=0; break; //退出程序
        case 224:
        {
            input=getch();
            switch(input)
            {
                case 72: to=1; break;
                case 80: to=2; break;
                case 75: to=3; break;
                case 77: to=4; break;
            }
            break; 
        }
        default : to=-1; break; 
    }
    return to;
}
int is_start;
int show(HANDLE hout,int &x,int &y,int to)
{
    if(!to) return 0; if(to==-1) return 1;
    if(x+fx[to]>=1 && x+fx[to]<n && y+fy[to]>=1 && y+fy[to]<m && !data[x+fx[to]][y+fy[to]]) //&& 
    {
        swap(data[x][y],data[x+fx[to]][y+fy[to]]);
        x+=fx[to]; y+=fy[to];
    }
    if(is_start) data[0][1]='#';
    
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    WORD wOldColorAttrs; HANDLE h; bool flag=0;
	GetConsoleScreenBufferInfo(hout, &csbiInfo); //未改变？？？？
	wOldColorAttrs = csbiInfo.wAttributes;
    SetColor(hout,FOREGROUND_RED,BACKGROUND_GREEN);
	GetConsoleScreenBufferInfo(hout, &csbiInfo); //未改变？？？？
	wOldColorAttrs = csbiInfo.wAttributes;
    
    for(int i=0;i<=n;i++) 
    {
        coord.Y=i;
        WriteConsoleOutputCharacterA(hout,data[i],m+1,coord,&bytes);
    }
    
    // h = GetStdHandle(STD_OUTPUT_HANDLE);
	// flag=GetConsoleScreenBufferInfo(hout, &csbiInfo);
	// wOldColorAttrs = csbiInfo.wAttributes;
    // puts("666");
    // SetConsoleActiveScreenBuffer(h); //把缓冲区作为显示的缓冲区
    
    // csbiInfo.wAttributes = 36;
    SetConsoleActiveScreenBuffer(hout); //把缓冲区作为显示的缓冲区
    // puts("666");
	// Save the current color
    
    
    // puts("666");
    return 1;
}



int main()
{
    // scanf("%d",&n);
    srand(time(NULL));
    // system("color 0E");
    initconsolveScreenBuffer();
    int to=2,now=1,x=0,y=1; //初始化输出一次
    is_start=1; show(output[now],x,y,to); is_start=0;
    while(to=get_toward())
    {
        show(output[now],x,y,to);
        now^=1;
    }
    return 0;
}

