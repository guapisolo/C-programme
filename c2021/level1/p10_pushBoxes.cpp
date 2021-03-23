#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <algorithm>
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
int n,m,Score;

HANDLE output[2];
COORD coord = {0,0};
DWORD bytes = 0;
int checkx(int x,int y)
{
    if(x>=1 && x<n && y>=1 && y<m) return 1;
    return 0;
}
int id(int x,int y){ return m*x+y; }
char data[32][102];
int fx[5] = {0,-1,1,0,0}, fy[5] = {0,0,0,-1,1}; //*wsad

void init_hard_version()
{
    puts("press any key to start");
    int input=getch();
    switch(input)
    {
        // case '1': n=10,m=10; system("mode con cols=30 lines=30"); break;
        // case '2': n=20,m=20; system("mode con cols=25 lines=25"); break;
        // case '3': n=30,m=50; system("mode con cols=35 lines=55"); break;
        case '1': n=10,m=10; break;
        case '2': n=20,m=20; break;
        case '3': n=26,m=50; break;
        case '4': 
        {
            puts("Plz input game map size:");
            printf("Number of Rows:"); scanf("%d",&n);
            printf("Number of Columns:"); scanf("%d",&m);
            n=min(n,26); m=min(m,50);
            break;
        }
    }
}

//以下为部分借鉴的模板
//双缓冲解决闪屏问题
void initconsolveScreenBuffer();
int show(HANDLE hout,int &x,int &y,int to);
int get_toward();
int cnt=0;

int checkok(int x,int y)
{
    return x>=1 && x<n && y>=1 && y<m;
}
void setcolor(HANDLE hCon,unsigned short ForeColor,unsigned short BackGroundColor)
{
    bool flag=SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor); //设置文本及背景颜色
}
void initconsolveScreenBuffer(int &x,int &y)
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
    memset(data,0,sizeof(data));
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;i++)
    {
        scanf("%s",data[i]);
        for(int j=0;j<=m;j++) if(data[i][j]=='@') 
            x=i, y=j;
    }
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
void print_unique(HANDLE hout,int i,int y,int color)
{
    LPDWORD num=0;
    setcolor(hout,color,0); //|BACKGROUND_RED |FOREGROUND_INTENSITY
    WriteConsoleA(hout,data[i]+y,1,num,NULL);
}
int is_start;
int show(HANDLE hout,int &x,int &y,int to)
{
    if(!to) return 0; if(to==-1) return 1; char c;
    if(checkok(x+fx[to],y+fy[to])) //&& 
    {
        c=data[x+fx[to]][y+fy[to]];
        if(!c){ //目标是空
            swap(data[x][y],data[x+fx[to]][y+fy[to]]);
        }else if(c=='$'){ //目标是箱子
            if(checkok(x+2*fx[to],y+2*fy[to]))
            {
                if(data[x+2*fx[to]][y+fy[to]]=='?'){
                    data[x+fx[to]][y+fy[to]]=data[x][y]; data[x][y]=0; 
                    data[x+2*fx[to]][y+fy[to]]='%';
                    Score++;
                }else if(!data[x+2*fx[to]][y+2*fy[to]]){
                    swap(data[x+fx[to]][y+fy[to]],data[x+2*fx[to]][y+2*fy[to]]);
                    swap(data[x+fx[to]][y+fy[to]],data[x][y]);
                }
            }
        }
        x+=fx[to]; y+=fy[to];
    }
    
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    setcolor(hout,FOREGROUND_GREEN|FOREGROUND_INTENSITY,0); //|BACKGROUND_RED |FOREGROUND_INTENSITY
    
    LPDWORD num=0;
    SetConsoleCursorPosition(hout,coord);
    for(int i=0;i<=n;i++) 
    {
        coord.Y=i; 
        for(int j=0;j<=m;j++)
        {
            switch(data[i][j])
            {
                case '#': print_unique(hout,i,j,FG|FI);
                case '$': print_unique(hout,i,j,FG|FR|FI);
                case '?': print_unique(hout,i,j,FR|FB|FI);
                case '@': print_unique(hout,i,j,FR|FI);
                case 0 : print_unique(hout,i,j,0);
            }
        }
    }
    coord.Y=0;
    // h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleActiveScreenBuffer(hout); //把缓冲区作为显示的缓冲区
    // Sleep(2000);
    cnt++;
    return 1;
}

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
        initconsolveScreenBuffer(x,y);
        show(output[now],x,y,to); is_start=0; now^=1;
        while(to=get_toward())
        {
            show(output[now],x,y,to);
            if(x==n-1 && y==m-1) 
                { n=n; break; }
            now^=1;
        }
        LPDWORD num=0;
        // coord.Y=n+3;
        WriteConsoleA(output[now],"\n",1,num,NULL);
        WriteConsoleA(output[now],"Congratulations!\n",19,num,NULL);
        SetConsoleActiveScreenBuffer(output[now]); //把缓冲区作为显示的缓冲区
        Sleep(3000);
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

