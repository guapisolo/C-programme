#include <conio.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define dd double
#define ll long long 
#define ull unsigned long long 
using namespace std;
const int N1=105;

int n;
struct Ware{
char name[40];
int num;
}a[N1];

// 1. 实现如下的菜单（按数字选择菜单功能）：
// 	- 显示存货列表 // 1
// 	- 入库 // 2
// 	- 出库 // 3
// 	- 退出程序 // 0 
// 1. 实现菜单对应功能（需记录货物的型号、数量等信息）；
// 1. 程序启动时从文件中读取当前库存数据，退出时保存库存数据；

int get_command()
{
    int input=getch(),to;
    switch(input)
    {
        case '1': to=1; break;
        case '2': to=2; break;
        case '3': to=3; break;
        case '0': to=4; break;
        default : to=-1; break; 
    }
    return to;
}
void list();
void stock(char *s,int len,int w);
void ship(char *s,int len,int w);
void save();

int main()
{
    freopen("ware.txt","r",stdin);
    scanf("%d",&n);
    char tmp[N1];
    for(int i=1;i<=n;i++) 
    {
        scanf("%s",tmp); int l=strlen(tmp);
        for(int j=0;j<l;j++) a[i].name[j]=tmp[j];
        scanf("%d",&a[i].num);
    }
    fclose(stdin);
    int to;
    while(1)
    {
        to=get_command();
        switch(to)
        {
            case 1: list(); break;
            case 2: stock(); break;
            case 3: ship(); break;
            case 4: save(); break;
        }
    }
    return 0;
}

int idx(char c){ return c-33; } //' '之后的

int id[N1];
struct Trie{
int ch[N1*40][94],id[N1],tot;
int findx(char *s,int len)
{
    int x=0; char c;
    for(int i=0;i<len;i++)
    {
        c=idx(s[i]);
        if(ch[x][c]) x=ch[x][c];
        else ch[x][c]=++tot, x=tot;
    }
    return x;
}
int upd(char *s,int len,int w)
{
    int x=findx(s,len);
    if(!id[x]) 
    {
        id[x]=++n; 
        for(int j=0;j<len;j++) a[n].name[j]=s[j];
        a[n].name[len]=' ';
    }
    if(a[id[x]].num+w<0) return 0;
    a[id[x]].num+=w;
    return 1;
}
}tr;
void list()
{
    for(int i=1;i<=n;i++)
    {
        printf("%s",a[i].name);
        printf(": %d\n",a[i].num);
    }
}
char str[40];
void stock(char *s,int len,int w)
{
    puts("Please input the goods' name and how much do you want to stock:");
    scanf("%s",str); int len=strlen(str),w; scanf("%d",w);
    int fl=tr.upd(s,len,w);
    if(!fl) printf("Invalid stock! The number of remaining boxes will be negative\n");
}
void ship(char *s,int len,int w)
{
    puts("Please input the goods' name and how much do you want to ship:");
    scanf("%s",str); int len=strlen(str),w; scanf("%d",w);
    int fl=tr.upd(s,len,-w);
    if(!fl) printf("Invalid shipment! The number of remaining boxes will be negative\n");
}
void save()
{
    freopen("ware.txt","w",stdout);
    for(int i=1;i<=n;i++) 
    {
        printf("%s",a[i].name);
        printf(" %d\n",a[i].num);
    }
    fclose(stdout);
}
