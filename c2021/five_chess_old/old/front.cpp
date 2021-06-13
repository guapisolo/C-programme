#include <conio.h>

int get_command()
{
    int input=getch(),to;
    switch(input)
    {
        case '1': to=1; break;
        case '2': to=2; break;
        case '3': to=3; break;
        case '4': to=4; break;
        case '0': to=0; break;
        default : to=-1; break; 
    }
    return to;
}
int get_toward()
{
    int input=getch(),to;
    switch(input)
    {
        // case '': to=5; break; 
        case 'w': to=1; break;
        case 's': to=2; break;
        case 'a': to=3; break;
        case 'd': to=4; break;
        case 13: to=5; break;
        case 'p': to=6; break;
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
// char output[1000];


void printmap(int mp[17][17],int n)
{
    int fl=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            switch(mp[i][j])
            {
                case -1 : dprintf("●",0,FB|FG|FR|FI,BB|BR,fl); break;
                case 0  : dprintf(" ",0,0,BB|BR,fl); break;
                case 1  : dprintf("●",0,0,BB|BR,fl); break;
                
                case 2  : dprintf("●",0,FB|FG|FR|FI,BG,fl); break;
                case 3  : dprintf(" ",0,0,BG,fl); break;
                case 4  : dprintf("●",0,0,BG,fl); break;
            }
        }
        if(i==n) fl=1;
        dprintf("\n",0,0,BB|BR,fl);
    }
}

const int M1=17, m=15;
int outmap[M1][M1];
int fx[6] = {0,-1,1,0,0,0}, fy[6] = {0,0,0,-1,1,0}; //*wsad

int checkposition(int x,int y)
{
    if(1<=x && x<=m && 1<=y && y<=m) return 1;
    return 0;
}
int checkchess(int x,int y)
{
    if(1<=x && x<=m && 1<=y && y<=m) return 1;
    return 0;
}

void place_piece(int mp[M1][M1],int &nx,int &ny,int now,int n)
{
    int to;
    // memcpy(outmap,mp,sizeof(outmap)); outmap[nx][ny]+=3;
    mp[nx][ny]+=3;
    printmap(mp,n);
    while(1)
    {
        to = get_toward();
        if(to==6){ savecurmap(); continue; }
        if(!checkposition(nx+fx[to],ny+fy[to])) continue;
        memcpy(outmap,mp,sizeof(outmap));
        if(1<=to && to<=4){
            mp[nx][ny]-=3;
            nx+=fx[to], ny+=fy[to];
            mp[nx][ny]+=3;
            printmap(mp,n);
        }else if(to==5){
            if(mp[nx][ny]==3){
                mp[nx][ny]=now+3;
                printmap(mp,n);
                return;
            }else{
                continue;
            }
        }else continue;
    }
}
// void place_piece(int x,int y,int now,int len)
// {
//     realmap[x][y] = now;
//     printmap(realmap,len);
// }
