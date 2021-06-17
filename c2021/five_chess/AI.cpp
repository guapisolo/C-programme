// #ifndef __AI_H
// #endif
#define AI_exist
#include "func.h"
// #define __Double_H
// #include "Double_screen_buffer.h"
// #define __FRONT_H
// #include "front.h"

using namespace std;

int mp[N1][N1]; //0 empty   1 o   -1 x
// previous
// int anxt[]={0, 700000, 70000, 4000, 3900, 30, 28, 5};
// int anow[]={0, 300000, 30000, 3500, 3300, 24, 22, 6};
int anxt[]={0, 900000, 90000, 7500, 7000, 90, 28, 5};
int anow[]={0, 400000,  40000, 1200, 1050, 80, 22, 6};
// int anow[]={0, 900000, 90000, 7500, 7000, 30, 28, 5};
// int anxt[]={0, 400000,  40000, 3000, 2500, 24, 22, 6};
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

// struct ChessMap{ int a[N1][N1]; }cur[N1];
// int realmap[N1][N1];
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
    int fl, cnt;
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
            continue;
            // i+=4; continue;
        }
    }
    // return ans;
}
//活三 冲三 眠三
ll check45(int *row,int len)
{
    ll ans=0; int fl, cnt;
    for(int i=1;i<=len;i++) 
    {
        //活三
        fl=1;
        for(int j=0;j<3;j++) if(row[i+j]!=o){ fl=0; break; }
        if(fl && !row[i-1] && !row[i+3]){ ans+=val[4]; continue; }
        
        //中空活三 眠三
        cnt=0; fl=1;
        for(int j=0;j<4;j++) 
            if(row[i+j]==o) cnt++;
            else if(row[i+j]==x){ fl=0; break; } 
        if(!fl) continue;
        // 不要跳不要跳不要跳
        if(cnt==3)
        {
            //双向活三威胁值更高，后续调整
            //中空活三
            if(!row[i-1] && !row[i+4]){ //_ o o _ o _ 
                ans+=val[4]/2;
                continue;
            }else if(!row[i-1] || !row[i+4]){ //_ o o _ o   or    o o o _ _
            //眠三
                ans+=val[5];
                continue;
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
    ll ans=0; 
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
        if(c==10)
            de=1;
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
//   x: current player    o: next player  
ll totMap(int now,int nxt) 
{
    //calc now
    memcpy(val,anow,sizeof(anow)); 
    o=now; x=nxt;
    ll ans=Map();
    
    //calc nxt
    memcpy(val,anxt,sizeof(anxt)); 
    o=nxt; x=now;
    ans-=Map();
    
    // return ans;
    return ans;
}
};
//记录不同位置落子的结果信息

const int dfs_deep=6;
const int bfs_num=5;
struct Play{ int x,y; int val; }; 

//plan A: 迭代加深搜索，每次搜4个最优状态
int cmpmin(Play &s1,Play &s2)
{ return s1.val < s2.val; }
int cmpmax(Play &s1,Play &s2)
{ return s1.val > s2.val; }

int checkwinner();
void outputcurmap();
void savecurmap();

int posx, posy;
//改为 迭代加深 + alpha-beta剪枝
ll AlphaBeta(int dep,int now,int Alpha,int Beta)
{
    // check(now,nxt);
    ll threat, ma=-inf, tmp; 
    Play piece[N1*N1]; memset(piece,0,sizeof(piece)); int pcnt=0;
    //malloc
    int tx=0,ty=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!cur[dep-1].a[i][j]) 
    {
        if(i==6 && j==10)
            de=1;
        memcpy(mp,cur[dep-1].a,sizeof(mp)); mp[i][j]=now;
        if(i==7 && j==6)
            de=1;
        if(i==6 && j==5)
            de=1;
        threat = assess::totMap(now,-now);
        if(threat==3095)
            de=1;
        if(threat>ma) tx = i, ty = j;
        ma = max(ma,threat); 
        piece[++pcnt] = (Play){i,j,threat}; //记录当前落子的估值
    }
    //threat：当前局面评分 越高越好
    //对 对手威胁值 最大 
    sort(piece+1,piece+pcnt+1,cmpmax);
    int id=0;
    if( ma <= -anxt[1]+eps || ma >= anow[1]-eps )
    {
        if(dep==1) posx = tx, posy = ty;
        return ma;
    }
    if(dep==dfs_deep) return ma;
    // if(dep==1) swap(piece[1],piece[5]);
    for(int k=1;k <= bfs_num;k++)
    {
        int i = piece[k].x, j = piece[k].y;
        memcpy(cur[dep].a,cur[dep-1].a,sizeof(mp)); cur[dep].a[i][j]=now;
        if(dep==1)
            de=1;
        tmp = -AlphaBeta(dep+1,-now,-Beta,-Alpha);
        if(dep==1)
        {
            de=1;
            push_inform(i,j,piece[k].val,tmp);
        }
        if(tmp >= Beta) return Beta;
        if(tmp > Alpha){
            Alpha = tmp;
            id = k;
        } 
    }
    if(dep==1){ posx = piece[id].x; posy = piece[id].y; }
    return Alpha;
}
int step=0,lx=8,ly=8;

int computer_move(int now)
{
    if(step==0)
        de=1;
    int id = AlphaBeta(1,now,-inf,inf);
    realmap[posx][posy] = now;
    printmap(realmap,n);
    nx = posx, ny = posy;
    
    inform_out();
    int fl = checkwinner(); if(fl) return fl;
    step++;
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    return 0;
}
int player_move(int now)
{
    place_piece(realmap,now,n);
    realmap[nx][ny] = now;
    int fl = checkwinner(); if(fl) return fl;
    step++;
    memcpy(cur[0].a,realmap,sizeof(cur[0].a));
    return 0;
}

int tmp;
void PLAY(int type,int now)
{
    if((type&1)) tmp = computer_move(now);
    else tmp = player_move(now);
    if(tmp) return;
    if((type&2)) tmp = computer_move(-now);
    else tmp = player_move(-now);
    if(tmp) return;
    if(tmp)
    {
        Sleep(100000);
        de=1;
    }
    // if(step==10) savecurmap();
    PLAY(type, now);
}

int checkwinner() //O(map)
{
    memcpy(mp,realmap,sizeof(mp)); 
    memcpy(val,anxt,sizeof(anxt)); assess::o=-1; assess::x=1;
    ll nval = assess::Map();
    if(nval >= anxt[1]-eps) return -1;
    
    memcpy(val,anxt,sizeof(anxt)); assess::o=1; assess::x=-1;
    nval = assess::Map();
    if(nval >= anxt[1]-eps) return 1;
    
    return 0;
}

#ifdef __AI_H
int main()
{
    freopen("a.in","r",stdin);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&realmap[i][j]);
    initconsolveScreenBuffer();
    printmap(realmap,n);
    return 0;
}
#endif
