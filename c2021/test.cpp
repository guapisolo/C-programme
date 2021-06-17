#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char str[]={"●"};

int main()
{
    int len=strlen(str);
    for(int i=0;i<len;i++) printf("%d ",str[i]);
    return 0;
}
