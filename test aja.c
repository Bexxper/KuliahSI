#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

void fruits()
{
    gameover = 0;

    x = height / 2;
    y = width / 2;

    fruitx = rand() % 20;
    if (fruitx == 0)
        fruits();

    fruity = rand() % 20;
    if (fruity == 0)
        fruits();

    score = 0;
}

void draw()
{
    system("cls");

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                    printf("O"); // snake head
                else if (i == fruitx && j == fruity)
                    printf("*"); // fruit
                else
                {
                    int ch = 0;
                    if (i > x && j == y)
                        ch = 1;
                    else if (i < x && j == y)
                        ch = 2;
                    else if (i == x && j > y)
                        ch = 3;
                    else if (i == x && j < y)
                        ch = 4;

                    if (ch == 1)
                        printf("^"); // up
                    else if (ch == 2)
                        printf("v"); // down
                    else if (ch == 3)
                        printf(">"); // right
                    else if (ch == 4)
                        printf("<"); // left
                    else
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'f':
            flag = 1;
            break;
        case 'd':
            flag = 2;
            break;
        case 'j':
            flag = 3;
            break;
        case 'k':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic()
{
    sleep(1);

    int prevX = x;
    int prevY = y;

    switch (flag)
    {
    case 1:
        x++;
        break;
    case 2:
        y--;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x > height || y < 0 || y > width)
        gameover = 1;

    if (x == fruitx && y == fruity)
    {
        fruitx = rand() % 20;
        if (fruitx == 0)
            fruitx = 1;

        fruity = rand() % 20;
        if (fruity == 0)
            fruity = 1;

        score += 5;
    }
    else
    {
        int tailX = 0, tailY = 0;
        if (prevX < x && prevY == y)
            tailX = x - 1, tailY = y;
        else if (prevX > x && prevY == y)
            tailX = x + 1, tailY = y;
        else if (prevX == x && prevY < y)
            tailX = x, tailY = y - 1;
        else if (prevX```
``` code> == x && prevY > y)
            tailX = x, tailY = y + 1;

        if (tailX == fruitx && tailY == fruity)
        {
            fruitx = rand() % 20;
            if (fruitx == 0)
                fruitx = 1;

            fruity = rand() % 20;
            if (fruity == 0)
                fruity = 1;
        }
        else
        {
            gotoxy(tailX, tailY);
            printf(" ");
        }
    }

    gotoxy(prevX, prevY);
    printf("o");
    gotoxy(x, y);
    printf("O");
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x, y);
}

int main()
{
    char c;

    while (1)
    {
        fruits();

        while (!gameover)
        {
            draw();
            input();
            logic();
        }

        printf("\npress y to continue again : ");
        scanf("%c", &c);
        if (c == 'y' || c == 'Y')
        {
            gameover = 0;
            score = 0;
        }
        else
            break;
    }

    return 0;
}