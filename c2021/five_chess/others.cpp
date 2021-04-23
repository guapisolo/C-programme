#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define ull unsigned long long

const int N=19;
const int INF=1e8;
const int CountLimit=40;
const int DeepLimit=5;
const int CountLimit2=1;
const int DeepLimit2=3;
int Board[N][N];
ull Hash[N][N];
//-1: unused
// 0: black 
// 1: white 

int x,y;
int Step;

int dx[]={-1,0,0,1};
int dy[]={0,-1,1,0};

int GetDirection(){
    while(1){
        Sleep(20);
        if(_kbhit()){
            switch(_getch()){
                case 72:return 0;
                case 'w':return 0;
                case 75:return 1;
                case 'a':return 1;
                case 77:return 2;
                case 'd':return 2;
                case 80:return 3;
                case 's':return 3;
                case 13:return 4;
                case ' ':return 4;
                case 'g':return 5;
                case 'h':return 6;
                case 27:exit(0);
            }
        }
    }
}

int GetChoice1(){
    while(1){
        Sleep(20);
        if(_kbhit()){
            switch(_getch()){
                case '1':return 1;
                case '2':return 2;
                case '3':return 3;
                case 27 :exit(0);
            }
        }
    }
}

int GetChoice2(){
    while(1){
        Sleep(20);
        if(_kbhit()){
            switch(_getch()){
                case 'b':return 0;
                case 'w':return 1;
                case 27 :exit(0);
            }
        }
    }
}

int KeyToValue(){
    while(1){
        Sleep(20);
        if(_kbhit()){
            return _getch();
        }
    }
}

inline void Print(){
    system("cls");
    printf("\033[43m\033[30m");
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(x==i&&y==j)printf("\033[44m");
            if(~Board[i][j])printf(Board[i][j]?"\033[37m●\033[30m":"●");
            else printf("＋");
            if(x==i&&y==j)printf("\033[43m");
        }
        putchar('\n');
    }
    printf("\033[0m");
}

inline bool Check(){
    for(int i=0;i<N;++i){
        for(int j=0;j+4<N;++j){
            if(~Board[i][j]&&Board[i][j]==Board[i][j+1]&&Board[i][j+1]==Board[i][j+2]&&Board[i][j+2]==Board[i][j+3]&&Board[i][j+3]==Board[i][j+4])return 1;
            if(~Board[j][i]&&Board[j][i]==Board[j+1][i]&&Board[j+1][i]==Board[j+2][i]&&Board[j+2][i]==Board[j+3][i]&&Board[j+3][i]==Board[j+4][i])return 1;
        }
    }
    for(int i=0;i+4<N;++i){
        for(int j=0;j+4<N;++j){
            if(~Board[i][j]&&Board[i][j]==Board[i+1][j+1]&&Board[i+1][j+1]==Board[i+2][j+2]&&Board[i+2][j+2]==Board[i+3][j+3]&&Board[i+3][j+3]==Board[i+4][j+4])return 1;
        }
    }
    for(int i=0;i+4<N;++i){
        for(int j=4;j<N;++j){
            if(~Board[i][j]&&Board[i][j]==Board[i+1][j-1]&&Board[i+1][j-1]==Board[i+2][j-2]&&Board[i+2][j-2]==Board[i+3][j-3]&&Board[i+3][j-3]==Board[i+4][j-4])return 1;
        }
    }
    return 0;
}

int dxx[]={1,1,1,0};
int dyy[]={1,-1,0,1};
int dxxx[]={1,1,1,0,-1,-1,-1,0};
int dyyy[]={1,-1,0,1,-1,1,0,-1};

inline int Risk(bool Color,int x,int y){
    int Sum=0;
    for(int d=0;d<4;++d){
        int len=1,cnt=0,nx=x,ny=y;
        for(int i=1;;++i){
            nx+=dxx[d];
            ny+=dyy[d];
            if(nx>=N||nx<0||ny>=N||ny<0||Board[nx][ny]==(Color^1)){
                ++cnt;
                break;
            }
            if(Board[nx][ny]==-1||i==5)break;
            ++len;
        }
        nx=x,ny=y;
        for(int i=1;;++i){
            nx-=dxx[d];
            ny-=dyy[d];
            if(nx>=N||nx<0||ny>=N||ny<0||Board[nx][ny]==(Color^1)){
                ++cnt;
                break;
            }
            if(Board[nx][ny]==-1||i==5)break;
            ++len;
        }
        if(len>=5)return INF;
        if(len==4&&!cnt)return INF/10;
        else if(cnt==2)Sum+=(len!=1);
        else Sum+=pow(10,len-cnt);
    }
    return Sum;
}

unordered_map<ull,pair<int,pair<int,int> > >F;

pair<int,pair<int,int> > dfs2(int dep,bool Color,int MaxLimit,ull state){
    if(F.count(state))return F[state];
    vector<pair<pair<int,int>,pair<int,int> > >Points;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(~Board[i][j])continue;
            int Rating=Risk(Color,i,j);
            if(Rating==INF)return F[state]={INF,{i,j}};
            if(dep&&Rating==INF/10){
                Board[i][j]=Color;
                int tmp=dfs2(0,Color^1,INF,state^Hash[i][j]).first;
                Board[i][j]=-1;
                if(tmp!=INF){
                    return F[state]={INF,{i,j}};
                }
                Rating=-INF;
            }
            Points.push_back({{Rating+Risk(Color^1,i,j),Rating},{i,j}});
        }
    }
    sort(Points.begin(),Points.end(),greater<pair<pair<int,int>,pair<int,int> > >());
    if(Points.size()>CountLimit2)Points.resize(CountLimit2);
    int x=-1,y=-1;
    int Max=-1e9;
    for(auto P:Points){
        int i=P.second.first;
        int j=P.second.second;
        int Rating=P.first.second;
        if(dep){
                Board[i][j]=Color;
                Rating-=dfs2(dep-1,Color^1,Rating-Max,state^Hash[i][j]).first;
                Rating=min(Rating,INF);
                Rating=max(Rating,-INF);
                Board[i][j]=-1;
        } 
        if(Rating>Max)x=i,y=j,Max=Rating;
        if(Max>=MaxLimit){
            return F[state]={Max,{x,y}};
        }
    }
    return F[state]={Max,{x,y}};
}

pair<int,pair<int,int> > dfs(int dep,bool Color,int MaxLimit,ull state){
    if(F.count(state))return F[state];
    vector<pair<pair<int,int>,pair<int,int> > >Points;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            if(~Board[i][j])continue;
            int Rating=Risk(Color,i,j);
            if(Rating==INF)return F[state]={INF,{i,j}};
            if(dep&&Rating==INF/10){
                Board[i][j]=Color;
                int tmp=dfs(0,Color^1,INF,state^Hash[i][j]).first;
                Board[i][j]=-1;
                if(tmp!=INF){
                    return F[state]={INF,{i,j}};
                }
                Rating=-INF;
            }
            Points.push_back({{Rating+Risk(Color^1,i,j),Rating},{i,j}});
        }
    }
    sort(Points.begin(),Points.end(),greater<pair<pair<int,int>,pair<int,int> > >());
    if(Points.size()>dep*10+10)Points.resize(dep*10+10);
    int x=-1,y=-1;
    int Max=-1e9;
    for(auto P:Points){
        int i=P.second.first;
        int j=P.second.second;
        int Rating=P.first.second;
        if(dep){
            Board[i][j]=Color;
            Rating-=dfs(dep-1,Color^1,Rating-Max,state^Hash[i][j]).first;
            Rating=min(Rating,INF);
            Rating=max(Rating,-INF);
            Board[i][j]=-1;
        }
        // else if(Step>=10){
        //     Board[i][j]=Color;
        //     Rating-=dfs2(DeepLimit2,Color^1,Rating-Max,state^Hash[i][j]).first;
        //     Rating=min(Rating,INF);
        //     Rating=max(Rating,-INF);
        //     Board[i][j]=-1;
        // }
        if(Rating>Max)x=i,y=j,Max=Rating;
        if(Max>=MaxLimit){
            return F[state]={Max,{x,y}};
        }
    }
    return F[state]={Max,{x,y}};
}

string Name[2];
double Time[2];

inline void PrintPlayer(const string &s,const double &x){
    int n=s.length();
    for(int i=0;i<n;++i)putchar(s[i]);
    printf("\t%.4lfs\n",x);
}

inline bool Computer(const bool &Color){
    clock_t start=clock();
    printf("Step %d\n",Step);
    PrintPlayer("★ "+Name[Color],Time[Color]);
    PrintPlayer("☆ "+Name[Color^1],Time[Color^1]);
    if(Step>=2){
        F.clear();
        auto tmp=dfs(DeepLimit,Color,INF,0);
        x=tmp.second.first;
        y=tmp.second.second;
        if(tmp.first<=-INF*0.9)return 1;
    }
    else if(Step==1){
        while(1){
            int d=rand()%8;
            int nx=x+dxxx[d];
            int ny=y+dyyy[d];
            if(nx>=0&&ny>=0&&nx<N&&ny<N){
                x=nx,y=ny;
                break;
            }
        }
    }
    Board[x][y]=Color;
    ++Step;
    clock_t end=clock();
    Time[Color]=(double)(end-start)/CLOCKS_PER_SEC;
    Print();
    return 0;
}

inline bool Player(int Color){
    clock_t start=clock();
    while(1){
        Print();
        printf("Step %d\n",Step);
        PrintPlayer("★ "+Name[Color],Time[Color]);
        PrintPlayer("☆ "+Name[Color^1],Time[Color^1]);
        int d=GetDirection();
        if(d==4){
            if(~Board[x][y])continue;
            Board[x][y]=Color;
            ++Step;
            clock_t end=clock();
            Time[Color]=(double)(end-start)/CLOCKS_PER_SEC;
            Print();
            return 0;
        }
        if(d==5)return 1;
        if(d==6){
            system("cls");
            Print();
            return Computer(Color);
        }
        int nx=x+dx[d];
        int ny=y+dy[d];
        if(nx<0||nx>=N||ny<0||ny>=N)continue;
        x=nx,y=ny;
    }
    return 0;
}

inline void PlayerVSPlayer(){
    Name[0]="Player 1";
    Name[1]="Player 2";
    memset(Board,-1,sizeof(Board));
    x=y=N/2;
    Step=0;
    Print();
    while(1){
        if(Player(0)){
            puts("Player 1 (black) give up!");
            break;
        }
        if(Check()){
            puts("Player 1 (black) win!");
            break;
        }
        if(Step==N*N){
            puts("Tie!");
            break;
        }
        if(Player(1)){
            puts("Player 2 (white) give up!");
            break;
        }
        if(Check()){
            puts("Player 2 (white) win!");
            break;
        }
    }
}

inline void PlayerVSComputer(){
    memset(Board,-1,sizeof(Board));
    system("cls");
    puts("Please choose a game mode");
    puts("Press [ B ] choose black");
    puts("Press [ W ] choose white");
    puts("Press [ ESC ] anytime to exit");
    bool Color=GetChoice2();
    Name[Color]="Player";
    Name[Color^1]="Computer";
    x=y=N/2;
    Step=0;
    Print();
    if(Color){
        while(1){
            if(Computer(0)){
                puts("Computer gives up! You win!");
                break;
            }
            if(Check()){
                puts("You lose!");
                break;
            }
            if(Step==N*N){
                puts("Tie!");
                break;
            }
            if(Player(1)){
                puts("You give up! You lose!");
                break;
            }
            if(Check()){
                puts("You win!");
                break;
            }
        }
    }
    else {
        while(1){
            if(Player(0)){
                puts("You give up! You lose!");
                break;
            }
            if(Check()){
                puts("You win!");
                break;
            }
            if(Step==N*N){
                puts("Tie!");
                break;
            }
            if(Computer(1)){
                puts("Computer gives up! You win!");
                break;
            }
            if(Check()){
                puts("You lose!");
                break;
            }
        }
    }
}

inline void ComputerVSComputer(){
    Name[0]="Computer 1";
    Name[1]="Computer 2";
    memset(Board,-1,sizeof(Board));
    x=y=N/2;
    Step=0;
    Print();
    while(1){
        if(Computer(0)){
            puts("Computer 1 (black) give up!");
            break;
        }
        if(Check()){
            puts("Computer 1 (black) wins!");
            break;
        }
        if(Step==N*N){
            puts("Tie!");
            break;
        }
        if(Computer(1)){
            puts("Computer 2 (white) give up!");
            break;
        }
        if(Check()){
            puts("Computer 2 (white) wins!");
            break;
        }
    }
}

inline void Game(){
    system("cls");
    puts("Please choose a game mode");
    puts("Press [ 1 ] for the Player Vs Player Mode");
    puts("Press [ 2 ] for the Player Vs Computer Mode");
    puts("Press [ 3 ] for the Computer Vs Computer Mode");
    puts("Press [ ESC ] anytime to exit");
    switch(GetChoice1()){
        case 1:PlayerVSPlayer();break;
        case 2:PlayerVSComputer();break;
        case 3:ComputerVSComputer();break;
    }
    system("pause");
}

inline void Menu(){
    system("mode con cols=60 lines=30");
    system("cls");
    puts("Welcome to the Wuziqi game!");
    puts("Press Arrow Key or [ W ], [ A ], [ S ], [ D ] to move");
    puts("Press [ Enter or Space ] to confirm");
    puts("Press [ H ] to get hint");
    puts("Press [ G ] to give up");
    system("pause");
    srand(time(0));
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            for(int k=0;k<5;++k){
                Hash[i][j]<<=15;
                Hash[i][j]|=rand();
            }
        }
    }
    while(1)Game();
}

int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    Menu();
    return 0;
}