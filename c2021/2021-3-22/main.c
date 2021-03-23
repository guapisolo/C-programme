#include "nibolan.h"
int main()
{
    Q Q1;
    S S1;
    char m1;
    int m2, m3, m4;
    initQueue(&Q1);
    initStack(&S1);
    input(&Q1);
    do 
    {
        m1 = Qpop(&Q1);
        if (m1 > '0' && m1 < '9')
            Sappend(&S1, m1);
        else
        {
            m2 = Spop(&S1);
            m3 = Spop(&S1);
            m4 = calculate(m1, m2, m3);
            Sappend(&S1, m4);
        }
    }
    while (m1);
    printf("%d", m4);
}

void input(Q* myqueue)
{
    initQueue(myqueue);
    char str[100] = { '\0' };
    gets(str); int i;
    for (i = 0;str[i] != 0;i++)
        Qappend(myqueue, str[i]);
}

int calculate(char p1,int p2,int p3)
{
    int p;

    switch(p1)
    {
    case '+':   p = p3 + p2; break;
    case '-':   p = p3 - p2; break;
    case '*':   p = p3 * p2; break;
    case '/':   p = p3 / p2; break;
    case '%':   p = p3 % p2; break;
    case '^':   p = pow(p3, p2);break;
    }
    return p;
}

void initQueue(Q* myqueue)
{
    myqueue->front = myqueue->rear = 0;
}

void Qappend(Q* myqueue, char y)
{
    if (myqueue->rear == N)
    {
        printf("失败");
        // return -1;
        return; 
    }
    else
    {
        myqueue->dataQ[myqueue->rear] = y;
        myqueue->rear += 1;
    }
}

 int Qpop(Q* myqueue)
 {
    if (myqueue->front == myqueue->rear)
    {
        printf("Error");
        return -1;
    }
    else
    {
        myqueue->front += 1;
        return (myqueue->dataQ[myqueue->front - 1]) - '0';
    }
 }

 void initStack(S* mystack)
 {
     mystack->top = -1;
 }
 void Sappend(S* mystack, char z)
 {
     if (mystack->top == N - 1)
     {
        //  return -1;
        printf("Error\n");
     }
     mystack->top++;
     int z2 = z - '0';
     mystack->dataS[mystack->top] = z2;
 }
 int Spop(S* mystack)
 {
     int q;
     if (mystack->top == -1)
     {
         return -1;
     }
     //利用传出参数传出栈顶元素
     q = mystack->dataS[mystack->top];
     mystack->top--;
     return q;
 }

