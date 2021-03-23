#include <cstdio>
#include <cstring>
#include <algorithm>
#define dd double
#define ll long long 
#define ull unsigned long long 
using namespace std;
const int N1=105;

int n, tot;
struct node{
int val; node *nxt;
};
node *head;
// void newpoint()
// {
    
// }
node* createnode(int x)
{
    node *buf = new node ((node){x,NULL});
    return buf;
}
node* insert(int pos,int x)
{
    node* now=head; pos--;
    if((*now).nxt==NULL){ (*now).nxt=now; return now; }
    for(;pos;now=(*now).nxt,pos--);
    node *nxt = (*now).nxt, *cur = createnode(x);
    (*now).nxt = cur; (*cur).nxt = nxt;
    tot++;
    return cur;
}
void del(int pos)
{
    node* now=head; 
    if(pos==1) pos=tot; else pos--;
    // if((*now).nxt==NULL){ (*now).nxt=now; return now; }
    for(;pos>1;now=(*now).nxt,pos--);
    node *cur = (*now).nxt;
    (*now).nxt = (*cur).nxt; 
    delete cur;
}
void print()
{
    node *now; now=head; int cnt=tot;
    for(;cnt;cnt--,now=(*now).nxt)
    {
        printf("%d ",(*now).val);
    }
}
node* inverse()
{
    node *cur = createnode((*head).val), *now, *tmp, *nxt, *st; 
    now = head; st = cur;
    int cnt=tot-1;
    for(;cnt;cnt--,now=(*now).nxt)
    {
        nxt = (*now).nxt;
        if(cnt!=1) tmp = createnode((*nxt).val); else tmp = st;
        (*tmp).nxt = cur;
        cur = tmp;
    }
    head = cur;
    return cur;
}
int find_first(int w)
{
    node* now = head; int cnt=1;
    for(;cnt<=n;cnt++,now=(*now).nxt)
    {
        if((*now).val==w) break;
    }
    if(cnt==n+1) return -1;
    return cnt;
}
int find_nxt(int pos,int w)
{
    node* now = head; int cnt=pos-1;
    for(;cnt;now=(*now).nxt,cnt--);
    for(;cnt++,now=(*now).nxt)
    {
        if((*now).val==w) break;
    }
    if(cnt==n+1) return -1;
    return cnt;
}

int main()
{
    freopen("a.in","r",stdin);
    printf("Plz input the size of your linkedlist:");
    scanf("%d",&n);
    puts("Plz input the elements in order in your linkedlist:");
    puts("It's guarantee that the last element is linked with the first element.");
    head = new node ((node){0,NULL}); 
    node *now; now=head;
    for(int i=0;i<n;i++) 
    {
        int x;
        scanf("%d",&(*now).val);
        insert(i,x);
        node *buf = new node ((node){0,NULL});
        if(i<n) (*now).nxt = buf, now=buf;
        else (*now).nxt = head, now=head;
    }
    return 0;
}

