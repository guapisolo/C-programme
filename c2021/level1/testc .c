


#include <stdio.h>
#include <string.h>

const char s[]={'\0','\1','\2','\3','\4','\5','\6','\7','\8','\9','\10'};
int main()
{
    // freopen("a.out","w",stdout);
    printf("\128 \129 \130 \131");
    // for(int i=0;i<=10;i++) printf("%c",s[i]);
    int i;
    // for(i=1;i<255;i++)  printf("%d:%c\n",i,(unsigned char)i);
    // for(char i=1;i<255;i++)  printf("%c\n",i);
    return 0;
}
