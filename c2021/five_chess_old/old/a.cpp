#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int a[3][3]={1,2,3,4,5,6,7,8,9};
    int b[3][3]={0,0,0,0,0,0,0,0,0};
    // memcpy(b,a,sizeof(b));
    for(int i=0;i<3;i++,puts("")) for(int j=0;j<3;j++) printf("%d ",b[i][j]);
    return 0;
}

