#include <cstdio>
#include <windows.h>

int main()
{
    while(1){
    for(int i=1;i<=50;i++)
    {
        for(int j=1;j<=50;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    system("cls");}
    return 0;
}
