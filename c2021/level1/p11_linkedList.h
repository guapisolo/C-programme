#include <conio.h>

struct node{
int val; node *nxt;
};

int get_command()
{
    int input=getch(),to;
    switch(input)
    {
        case '1': to=1; break;
        case '2': to=2; break;
        case '3': to=3; break;
        case '4': to=4; break;
        case '5': to=5; break;
        case '6': to=6; break;
        case '/': to=7; break;
        case '0': to=0; break;
        default : to=-1; break; 
    }
    return to;
}
void releasenode(node* now)
{
    int cnt=tot; node *nxt;
    for(;cnt;cnt--)
    {
        nxt = (*now).nxt;
        delete now;
        if(cnt>1) now = nxt;
    }
}
node* createnode(int x)
{
    node *buf = new node ((node){x,NULL});
    return buf;
}
node* insert(int pos,int x)
{
    node* now=head; 
    if((*now).nxt==NULL){ (*now).val=x; (*now).nxt=now; tot++; return now; } //原链表没有元素
    pos--;
    for(;pos;now=(*now).nxt,pos--);
    node *nxt = (*now).nxt, *cur = createnode(x);
    (*now).nxt = cur; (*cur).nxt = nxt;
    tot++;
    return cur;
}
void DEL(int pos)
{
    node* now=head; 
    if(pos==1) pos=tot; else pos--;
    for(;pos>1;now=(*now).nxt,pos--);
    node *cur = (*now).nxt;
    (*now).nxt = (*cur).nxt; 
    delete cur;
    tot--;
}
void print(int type)
{
    node *now; now=head; int cnt=tot;
    for(;cnt;cnt--,now=(*now).nxt)
    {
        printf("%d ",(*now).val);
    }
    if(type==0) puts("");
    if(type==1) abnor();
}
node* inverse()
{
    node *cur = createnode((*head).val), *now, *tmp, *nxt, *st; 
    (*cur).nxt = cur;
    now = head; st = cur;
    int cnt = tot;
    for(;cnt;cnt--,now=(*now).nxt)
    {
        nxt = (*now).nxt;
        if(cnt!=1) tmp = createnode((*nxt).val); else tmp = st;
        (*tmp).nxt = cur;
        cur = tmp;
    }
    releasenode(head);
    head = cur;
    print(1); 
    return cur;
}
int find_first(int w)
{
    node* now = head; int cnt=1;
    for(;cnt<=tot;cnt++,now=(*now).nxt)
    {
        if((*now).val==w) break;
    }
    if(cnt==tot+1) return -1;
    return cnt;
}
int find_nxt(int pos,int w) //pos之后的第一个w值
{
    node* now = head; int cnt=pos;
    for(;cnt;now=(*now).nxt,cnt--); cnt=pos+1;
    for(;cnt<=tot;cnt++,now=(*now).nxt)
    {
        if((*now).val==w) break;
    }
    if(cnt==tot+1) return -1;
    return cnt;
}
