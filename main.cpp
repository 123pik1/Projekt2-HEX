#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "Board.hpp"

using namespace std;
int main()
{
    char task[100];
    int counter = 1;
    // freopen("16.in", "r", stdin);
    Board b;
    while (scanf("%s", task) != EOF)
    {
        // scanf("%s", task);
        // printf("%s\n", task);
        if (strcmp(task, "---") == 0)
        {
            // printf("TEST %d\n", counter);

            b.newBoard();
            counter++;

        } // czyszczenie boarda
        else
        {
            if (strcmp(task, "BOARD_SIZE") == 0)
            {
                printf("%d\n", b.getSize());
            }
            if (strcmp(task, "PAWNS_NUMBER") == 0)
            {
                printf("%d\n", b.getNmbOfBlue() + b.getNmbOfRed());
            }
            if (strcmp(task, "IS_BOARD_CORRECT") == 0)
            {
                if (b.isBoardCorrect())
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            if (strcmp(task, "IS_GAME_OVER") == 0)
            {
                b.visitedSetFalse();
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
                printf("\n");
            }
            if (strcmp(task, "IS_BOARD_POSSIBLE") == 0)
            {
                if (b.isBoardPossible())
                    printf("YES\n\n");
                else
                    printf("NO\n\n");
            }
            if (strcmp(task, "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
            {
                if (b.naiveOneRed())
                    printf("YES\n");

                else
                    printf("NO\n");
            }
            if (strcmp(task, "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0)
            {
                if (b.naiveOneBlue())
                    printf("YES\n");

                else
                    printf("NO\n");
            }
            if (strcmp(task, "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
            {
                if (b.naiveTwoRed())
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            if (strcmp(task, "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") == 0)
                if (b.naiveTwoBlue())
                    printf("YES\n\n");
                else
                    printf("NO\n\n");
            if (strcmp(task, "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0)
                if (b.perfectOneRed())
                    printf("YES\n");
                else
                    printf("NO\n");
            if (strcmp(task, "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0)
                if (b.perfectOneBlue())
                    printf("YES\n");
                else
                    printf("NO\n");
            if (strcmp(task, "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0)
                if (b.perfectTwoRed())
                    printf("YES\n");
                else
                    printf("NO\n");
            if (strcmp(task, "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") == 0)
                if (b.perfectTwoBlue())
                    printf("YES\n\n");
                else
                    printf("NO\n\n");
        }
    }
    return 0;
}