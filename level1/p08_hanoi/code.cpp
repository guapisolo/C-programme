#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#define dd double
#define ll long long 
#define ull unsigned long long 
using namespace std;
const int maxn=100,N1=maxn+5,base=63;

int n;
ull f[N1];

int main()
{
    // scanf("%d",&n);
    n=64;
    f[1]=1;
    for(int i=2;i<=n;i++) f[i]=f[i-1]*2+1;
    printf("%llu\n",f[n]);
    return 0;
}

