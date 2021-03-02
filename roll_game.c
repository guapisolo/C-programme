#include <stdio.h>
#include <string.h>
#include <windows.h>
#define N1 105
const int X=20,Y=20;

char str[N1];
char mp[N1][N1];
void print()
{
    int i,j;
    for(i=0;i<X;i++)
    {
        for(j=0;j<Y;j++) printf("%c",mp[i][j]);
        puts("");
    }
}

int main()
{
    printf("Please input a string:\n");
    scanf("%s",str);
    int len=strlen(str),i,j,x,y,tx,ty; char tmp;
    for(i=0;i<X;i++) for(j=0;j<Y;j++) mp[i][j]='*';
    for(i=0;i<len;i++) mp[0][i]=str[i];
    x=0, y=0;
    print();
    while(str[0]=getchar()){ //scanf("%s",str)!=EOF
        if(str[0]=='z') break;
        system("cls");
        if(str[0]=='w'){
            if(x==0) tx=X-1; else tx=x-1;
            for(j=0;j<Y;j++) mp[tx][j]=mp[x][j], mp[x][j]='*';
            x=tx;
        }
        if(str[0]=='s'){
            if(x==X-1) tx=0; else tx=x+1;
            for(j=0;j<Y;j++) mp[tx][j]=mp[x][j], mp[x][j]='*';
            x=tx;
        }
        if(str[0]=='a'){
            tmp=mp[x][0];
            for(j=0;j<Y-1;j++) mp[x][j]=mp[x][j+1];
            mp[x][Y-1]=tmp;
        }
        if(str[0]=='d'){
            tmp=mp[x][Y-1];
            for(j=Y-1;j>=1;j--) mp[x][j]=mp[x][j-1];
            mp[x][0]=tmp;
        }
        print();
    }
    return 0;
}
