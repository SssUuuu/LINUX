#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define NONE  "\e[0m"
#define RED   "\e[0;31m"
#define BLUE  "\e[0;34m"

int main()
{
    int index = 0;
    char str[21];
    memset(str,'\0',sizeof(str));
    char tmp[5] = {'-','\\','|','/','\0'};
    while(index <=20)
    {   
        str[index] = '#';
        if(index <=10)
            printf(RED"%s[%d%%%c]\r"NONE,str,index*5,tmp[index%4]);
        else

            printf(BLUE"%s[%d%%%c]\r"NONE,str,index*5,tmp[index%4]);
        fflush(stdout);
        index++;
        //1*10^5 = 0.1s 
        usleep(100000);
    }   
    printf("\n");
    return 0;
}
