#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "Board.hpp"
using namespace std;
int main()
{
    char task[50];

    while (scanf("%s", task) != EOF)
    {
        // scanf("%s", task);
        // printf("%s\n", task);

        Board b;
        scanf("%s", task);
        if (strcmp(task, "BOARD_SIZE") == 0)
        {
            printf("%d\n", b.getSize());
        }
        if (strcmp(task, "PAWNS_NUMBER") == 0)
        {
            printf("%d\n", b.getNmbOfBlue() + b.getNmbOfRed());
        }
        if (strcmp(task, "IS_BOARD_CORRECT")==0)
        {
            if (b.isBoardCorrect())
                printf("YES\n");
            else
                printf("NO\n");
        }
        if (strcmp(task, "IS_GAME_OVER")==0)
        {
            color wonCol = b.isGameOver();
            if (wonCol == BLUE)
            {
                printf("YES BLUE\n");
            }
            else if (wonCol == RED)
            {
                printf("YES RED\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
    return 0;
}