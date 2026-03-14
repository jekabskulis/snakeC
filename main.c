
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>//Windows only

//Clears the old frame by printing empty lines.
void clearFrame()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

//Checks for keyboard input until finds a valid key, ignores all other keys.
char keyboardInput()
{
    char key;
    if(kbhit())
    {
        key = getch();
    }
    else
    {
        return '0';
    }
    if(key!='w' && key !='s' && key!='d' && key!='a')
    {
        keyboardInput();
    }
    return key;
}

int main()
{
    char screen[20][41] = {
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"}
    };
    int headPosX = 5;
    int headPosY = 5;
    int i;
    char key;
    char pressedValidKey;
    char head = 'O';
    clock_t c0 = clock() / (CLOCKS_PER_SEC / 1000);
    while(1)
    {
        clock_t c1 = clock() / (CLOCKS_PER_SEC / 1000);
        //New frame every 400 milliseconds.
        if(c1 - c0 > 400)
        {
            c0=c1;
            clearFrame();

            key = keyboardInput();
            //Saves the valid key into a different variable so the snake keeps moving.
            if(key=='w' || key=='s' || key=='d' || key=='a')
                pressedValidKey = key;

            if(pressedValidKey=='w')
                headPosY--;
            else if(pressedValidKey=='s')
                headPosY++;
            else if(pressedValidKey=='d')
                headPosX++;
            else if(pressedValidKey=='a')
                headPosX--;

            //Resets the position of the head if it goes outside of the screen.
            if(headPosX == 40)
                headPosX = 0;
            else if(headPosX == -1)
                headPosX = 39;
            if(headPosY == 20)
                headPosY = 0;
            else if(headPosY == -1)
                headPosY = 19;

            screen[headPosY][headPosX] = head;
            for(i = 0; i < 20; i++)
            {
                printf("%s\n", screen[i]);
            }
        }
    }

    return 0;
}
