
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  //Windows only

#define SCREENLENX 20
#define SCREENLENY 41   //Including the null terminator.



typedef struct
{
  int age;
  int x;
  int y;
} SnakeBodyElem;

typedef struct
{
    SnakeBodyElem *items;
    int count;
    int capacity;
} SnakeBodyArray;

SnakeBodyArray allocateItem(SnakeBodyArray snakeBody, int x, int y, int length)
{
    SnakeBodyArray snakeBodyNew = snakeBody;
    SnakeBodyElem bodyElem = {0};
    int i;
    for(i = 0; i < length; i++)
    {
        if(snakeBodyNew.count >= snakeBodyNew.capacity)
        {
            if(snakeBodyNew.capacity == 0)
                snakeBodyNew.capacity = 16;
            else
                snakeBodyNew.capacity *= 2;
            snakeBodyNew.items = realloc(snakeBodyNew.items, snakeBodyNew.capacity*sizeof(*snakeBodyNew.items));
        }

        if(i == length-1)
        {
            bodyElem.x = x;
            bodyElem.y = y;
            bodyElem.age = length;
        }
        else
        {
            bodyElem = snakeBody.items[i];
            bodyElem.age--;
        }

        snakeBodyNew.items[snakeBodyNew.count++] = bodyElem;
    }
    return snakeBodyNew;
}


//Clears the old frame by printing empty lines.
void clearFrame()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

//Prints the screen
void printScreenGameOver(char screen[SCREENLENX][SCREENLENY])
{

    int i;
    for(i = 0; i < 20; i++)
    {
        printf("%s\n", screen[i]);
    }
}

void printScreen(char screen[SCREENLENX][SCREENLENY], char apple, char body, char head, int headPosX, int headPosY, SnakeBodyArray snakeBody)
{

    int i;

    for(i = 0; i < snakeBody.count; i++)
    {
        screen[snakeBody.items[i].y][snakeBody.items[i].x] = body;
    }
    screen[headPosY][headPosX] = head;

    for(i = 0; i < 20; i++)
    {
        printf("%s\n", screen[i]);
    }
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
    char screen[SCREENLENX][SCREENLENY] = {
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
    int length = 0;

    char key;
    char pressedValidKey;
    char head = 'O';
    char body = '#';
    char apple = '$';

    SnakeBodyArray snakeBody = {0};

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
            {
                pressedValidKey = key;
            }

            if(pressedValidKey=='w')
            {
                headPosY--;
                length++;
            }
            else if(pressedValidKey=='s')\
            {
                headPosY++;
                length++;
            }
            else if(pressedValidKey=='d')
            {
                headPosX++;
                length++;
            }
            else if(pressedValidKey=='a')
            {
                headPosX--;
                length++;
            }

            //Resets the position of the head if it goes outside of the screen.
            if(headPosX == 40)
                headPosX = 0;
            else if(headPosX == -1)
                headPosX = 39;
            if(headPosY == 20)
                headPosY = 0;
            else if(headPosY == -1)
                headPosY = 19;


            if((screen[headPosY][headPosX] == 'O' || screen[headPosY][headPosX] == '#') && (length >= 1))
            {
                printScreenGameOver(screen);
                printf("Game Over\n");
                exit(0);
            }

            snakeBody = allocateItem(snakeBody, headPosX, headPosY, length);
            printScreen(screen, apple, body, head, headPosX, headPosY, snakeBody);

        }

    }

    return 0;
}
