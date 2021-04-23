#ifndef __AI_H
#endif

#include <conio.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <algorithm>
#define __Double_H
#include "Double_screen_buffer.h"
#define __FRONT_H
#include "front.h"

#define ll long long 
#define dd double 
using namespace std;

const int n=15, N1=17, inf=0x3f3f3f3f;

int mp[N1][N1]; //0 empty   1 o   -1 x
// int anxt[]={0, 100000, 10000, 1500, 1400, 30, 28, 5};
// int anow[]={0, 90000,  9000, 1300, 1200, 24, 22, 6};
int anxt[]={0, 200000, 30000, 4000, 3400, 30, 28, 5};
int anow[]={0, 180000,  29000, 2600, 1700, 24, 22, 6};
int val[N1];
//val: 
// 1:连5
// 2:活4
// 3:冲4
// 4:活3
// 5:眠3
// 6:活2
// 7:活1
int de;

namespace assess{
int end4[N1][N1], ed[N1] ,num[N1], o,x;


//连五
ll check1(int *row,int len) 
{
    ll ans=0; int fl;
    for(int i=1;i<=len;i++) 
    {
        fl=1; for(int j=0;j<5;j++) if(row[i+j]!=o){ fl=0; break; } 
        if(fl){ ans+=val[1]; i+=4; continue; }
    }
    return ans;
}
//连四 冲四
void check23(int *row,int len) 
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        //活四
        fl=1; 
        for(int j=0;j<4;j++) if(row[i+j]!=o){ fl=0; break; } 
        if(fl && (!row[i-1] || !row[i+4]) )
        {
            if(!row[i-1]) ed[i-1]=1;
            if(!row[i+4]) ed[i+4]=1;
            i+=4; continue;
        } 
        //冲四
        cnt=0; fl=1;
        for(int j=0;j<5;j++) 
            if(row[i+j]==o) cnt++;
            else if(row[i+j]==x){ fl=0; break; }
        if(!fl) continue;
        if(cnt==4)
        {
            for(int j=0;j<5;j++) 
            {
                if(!row[i+j]){ ed[i+j]=1; break; }
            }
            i+=4; continue;
        }
    }
    // return ans;
}
//冲三 眠三
ll check45(int *row,int len)
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        cnt=0; fl=1;
        for(int j=0;j<4;j++) 
            if(row[i+j]==o) cnt++;
            else if(row[i+j]==x){ fl=0; break; } 
        if(!fl) continue;
        if(cnt==3)
        {
            //双向活三威胁值更高，后续调整
            //活三
            if(!row[i-1] && !row[i+4]){ //_ o o _ o _ 
                ans+=val[4];
                i+=4; continue;
            }else if(!row[i-1] || !row[i+4]){ //_ o o _ o   or    o o o _ _
            //眠三
                ans+=val[5];
                i+=4; continue;
            }
        }
        
    }
    return ans;
}
//二 一
ll check67(int *row,int len) 
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        fl=1; cnt=0;
        for(int j=0;j<6;j++) 
            if(row[i+j]==o){ cnt++; }
            else if(row[i+j]==x){ fl=0; break; }
        if(!fl) continue;
        if(cnt==2) ans+=val[6]; else if(cnt==1) ans+=val[7];
    }
    return ans;
}
ll Row(int *row,int len) 
{
    ll ans=0; int fl,cnt;
    memset(ed,0,sizeof(ed));
    ans+=check1(row,len);
    check23(row,len);
    ans+=check45(row,len);
    ans+=check67(row,len);
    return ans;
}
int row[N1];
ll Direct(int cs,int rs,int px,int py)
{
    ll ans=0; 
    if(!(px==1&&py==0))
    for(int r=1;r<=n;r++)
    {
        row[0]=x; int cnt=1;
        for(int i=r,j=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,cnt++)
        {
            row[cnt]=mp[i][j]; 
        }
        row[cnt]=x; // 堵
        if(mp[9][6]==1)
            de=1;
        ans+=Row(row,cnt);
        for(int i=r,j=1,k=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,k++)
        {
            if(ed[k]) 
                end4[i][j]=1;
        }
    }
    for(int c=cs;c<=n;c++)
    {
        row[0]=x; int cnt=1;
        for(int i=rs,j=c;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,cnt++)
        {
            row[cnt]=mp[i][j]; 
        }
        row[cnt]=x;// 堵
        ans+=Row(row,cnt);
        for(int i=rs,j=c,k=1;i>=1&&i<=n&&j>=1&&j<=n;i+=px,j+=py,k++)
        {
            if(ed[k]) 
                end4[i][j]=1;
        }
    }
    return ans;
}
ll Map()
{
    ll ans=0;
    memset(end4,0,sizeof(end4));
    if(mp[9][6]==1)
        de=1;
    ans+=Direct(2,1,1,1); //向右下
    ans+=Direct(2,n,-1,1); //向右上
    ans+=Direct(n+1,0,0,1); //向右
    ans+=Direct(1,1,1,0); //向下
    num[4]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(end4[i][j]) num[4]++;
    if(num[4]>1) ans+=val[2]; else if(num[4]==1) ans+=val[3];
    return ans;
}
// char str[N1][N1];
// int check()
// {
//     freopen("map.in","r",stdin);
//     val[1]=50000; val[2]=4320; val[3]=720; val[4]=720; val[5]=120; val[6]=120; val[7]=20;
//     assess::o=1; assess::x=-1; 
//     for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
//     for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) mp[i][j]=str[i][j]-'0';
//     ll ans=assess::Map();
//     printf("%lld\n",ans);
//     return 0;
// }
//   x: current player    o: next player  
ll totMap(int now,int nxt) 
{
    //calc now
    memcpy(val,anow,sizeof(val)); 
    o=now; x=nxt;
    ll ans=-Map();
    
    //calc nxt
    memcpy(val,anxt,sizeof(val)); 
    o=nxt; x=now;
    ans+=Map();
    
    return ans;
}
};
//记录不同位置落子的结果信息

int realmap[N1][N1];
const int dfs_deep=4;
const int bfs_num=4;

//plan A: 迭代加深搜索，每次搜4个最优状态
struct Play{ 
int x,y; ll val;
}; //int pcnt;
int cmpmin(Play &s1,Play &s2)
{ return s1.val < s2.val; }
struct ChessMap{
int a[N1][N1];
}cur[N1];

int checkwinner();
void outputcurmap();

int posx, posy;
ll minmax_dfs(int dep,int now)
{
    // check(now,nxt);
    ll threat, ma=-inf, mi=inf, tmp; 
    Play piece[N1*N1]; memset(piece,0,sizeof(piece)); int pcnt=0;
    //malloc
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!cur[dep-1].a[i][j]) 
    {
        memcpy(mp,cur[dep-1].a,sizeof(mp)); mp[i][j]=now;
        if(i==9&&j==6)
            de=1;
        threat = assess::totMap(now,-now);
        mi = min(mi,threat);
        piece[++pcnt] = (Play){i,j,threat}; //记录当前落子的估值
    }
    sort(piece+1,piece+pcnt+1,cmpmin);
    int id=0;
    if(dep==dfs_deep) return mi;
    for(int k=1;k <= bfs_num;k++)
    {
        int i = piece[k].x, j = piece[k].y;
        memcpy(cur[dep].a,cur[dep-1].a,sizeof(mp)); cur[dep].a[i][j]=now;
        tmp = minmax_dfs(dep+1,-now);
        if(dep==1)
            de=1;    
        if(tmp>ma) ma=tmp, id=k;
    }
    if(dep==1){ posx = piece[id].x; posy = piece[id].y; }
    return piece[id].val;
}
int step=0;

void fkcomputer(int now)
{
    // minmax_dfs(nxt,now);
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    // if(step==6)
    // {
    //     outputcurmap();
    //     de=1;2
    // }
    int id = minmax_dfs(1,now);
    realmap[posx][posy]=now;
    printmap(realmap,n);
    int fl = checkwinner(); if(fl) return; 
    step++;
    
    int nx=8,ny=8; 
    player_move(realmap,nx,ny,-now,n);
    realmap[nx][ny]=-now;
    fl = checkwinner(); if(fl) return; 
    // printmap();
    step++;
    
    fkcomputer(now);
}

void inputmap()
{
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) 
        scanf("%d",&realmap[i][j]);
}
void outputcurmap()
{
    char outstr[5];
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=n;j++)
        {
            sprintf(outstr,"%d ",mp[i][j]); 
            dprintf(outstr,0,FG|FB|FR|FI,0,0);
        }
        dprintf("\n",0,FG|FB|FR|FI,0,i==n?1:0);
    }
}
int checkwinner()
{
    memcpy(mp,realmap,sizeof(mp)); 
    memcpy(val,anow,sizeof(val)); assess::o=1; assess::x=-1;
    ll nval = assess::Map();
    if(nval >= anow[1]) return 1;
    
    memcpy(val,anow,sizeof(val)); assess::o=-1; assess::x=1;
    nval = assess::Map();
    if(nval >= anow[1]) return -1;
    
    return 0;
}

#ifndef __AI_H
int main()
{
    freopen("a.in","r",stdin);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&realmap[i][j]);
    initconsolveScreenBuffer();
    printmap(realmap,n);
    return 0;
}
#endif

// int cmpmax(Play &s1,Play &s2)
// { return s1.val > s2.val; }

// struct ChessMap{
// int fa,a[N1][N1];
// }cur[N1][N1],son[N1*N1*N1]; int ccnt,scnt;

// void get_cur_son(int dep,int num,int now)
// {
//     ll threat; 
//     if(!cur[dep][num].fa) return;
//     for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!cur[dep][num].a[i][j]) 
//     {
//         memcpy(mp,cur[dep][num].a,sizeof(mp)); mp[i][j]=now;
//         threat=assess::totMap(now,-now);
//         piece[++pcnt]=(Play){i,j,++scnt,threat}; //记录当前落子的估值
//         memcpy(son[scnt].a,mp,sizeof(mp));  //记录当前落子的棋盘
//         son[scnt].fa=num;
//     }
// }
// void iterative_dfs(int st)
// {
//     int now=st;
//     for(int dep=0;dep < dfs_deep;dep++)
//     {
//         pcnt=0; scnt=0;
//         for(int num=1;num <= bfs_num;num++) get_cur_son(dep,num,now);
//         sort(piece+1,piece+pcnt+1,cmpmin);
//         for(int i=1;i<=bfs_num;i++)
//         {
//             cur[dep+1][i]=son[piece[i].id];
//         }
//         now = -now;
//     }
// }