#include <cstdio>
#include <cstring>
#include <algorithm>
#define dd double
#define ll long long 
#define ull unsigned long long 
using namespace std;
const int N1=105;

// // 生成迷宫：生成树算法
// // 我的做法：随机边权然后最小生成树
int n;
struct node{
int val; node *nxt;
};
node *head;
// void newpoint()
// {
    
// }
void print()
{
    node *now; now=head;
    for(;now!=NULL;now=(*now).nxt)
    {
        printf("%d ",(*now).val);
    }
}

int main()
{
    printf("Plz input the size of your linkedlist:");
    scanf("%d",&n);
    puts("Plz input the elements in order in your linkedlist:");
    puts("It's guarantee that the last element is linked with the first element.");
    memset(head,0,sizeof(head));
    node *now; now=head;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&(*now).val);
        void *buf = malloc(sizeof(node)); memset(buf,0,sizeof(node));
        if(i<n) (*now).nxt = (node*)buf; else (*now).nxt=NULL;
    }
    return 0;
}

