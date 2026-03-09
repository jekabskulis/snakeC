
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Clears the old frame by printing empty lines.
void clearFrame()
{
    int i;
    for(i = 0; i < 50; i++)
    {
        printf("\n");
    }
}


int main()
{
    char background[10][21] = {
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    {"...................."},
    };
    int i;
    time_t t0 = time(NULL);
    while(1)
    {

        time_t t1 = time(NULL);
        if(difftime(t1, t0)>0.1)
        {
            t0=t1;
            clearFrame();
            for(i = 0; i < 10; i++)
            {
                printf("%s\n", background[i]);
            }
        }
    }

    return 0;
}
