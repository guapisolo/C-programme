#include<iostream>
#include <cstdio>
#include <algorithm>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

char comm[20];
int main()
{
    comm[0]='c', comm[1]='o', comm[2]='l', comm[3]='o', comm[4]='r'; comm[5]=32; comm[6]='0'; comm[8]='\n';
    printf("666\n");
    for(int i=0;i<=9;i++)
    {
        comm[7]='0'+i;
        // char tmp[]="color 02";
        // system(tmp);
        // system("color 02");
        system(comm);
        Sleep(1000);
    }
    return 0;
}

// #include <cstdio>
// #include <cstring>
// #include <iostream>
// #include <algorithm>
// using namespace std;

// const char s[]={'\0','\1','\2','\3','\4','\5','\6','\7','\8','\9','\10'};
// int main()
// {
//     // freopen("a.out","w",stdout);
//     // printf("\1");
//     // for(int i=0;i<=10;i++) printf("%c",s[i]);
//     // for(int i=1;i<255;i++)  printf("%d:%c\n",i,(unsigned char)i);
//     for(char i=1;i<255;i++)  cout << i  << '\n' << endl;
//     return 0;
// }
