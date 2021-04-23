#include <cstdio>
#include <algorithm>
#include <windows.h>
using namespace std;

#define __AI_H
#include "AI.h"

// #define __Double_H
// #include "Double_screen_buffer.h"


int main()
{
    // freopen("map.in","r",stdin);
    // inputmap();
    int to;
    initconsolveScreenBuffer();
    while(1)
    {
        system("cls");
        puts("Press [1] to start a two-player battle");
        puts("Press [2] to play with computer");
        puts("Press [0] to exit");
        to=get_command();
        switch(to)
        {
            // case 1: two_player(); break;
            case 2: fkcomputer(1); Sleep(1000000); break;
        }
        if(to==0) break;
    }
    return 0;
}
