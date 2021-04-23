#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#define ll long long 
using namespace std;

ll fact(int x)
{
    return x<=2 ? 1ll*x : fact(x-1)*x;
}

TEST_CASE ("Testing ")
{
    CHECK(fact(1)==1);
    CHECK(fact(2)==2);
    CHECK(fact(3)==6);
    CHECK(fact(5)==24);
}
