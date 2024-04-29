// printf("red: %d blue: %d\n",nmbOfRed,nmbOfBlue);
spinBoard();
if (!isBoardCorrect())
    return false;
// printf("%c\n",col);
// printSpinnedBoard();
if (isGameOver() != EMPTY)
    return false;
// printf("%c\n",col);

color begins;
if (nmbOfBlue == nmbOfRed)
    begins = RED;
else
    begins = BLUE;
for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
    {
        if (spinnedBoard[i][j] == EMPTY)
        {
            // printf("1. red: %d blue: %d\n", nmbOfRed, nmbOfBlue);

            addPawn(begins, {j, i});

            // printf("2. red: %d blue: %d\n", nmbOfRed, nmbOfBlue);

            // printSpinnedBoard();

            if (begins == col)
            {
                // printf("3. red: %d blue: %d\n", nmbOfRed, nmbOfBlue);

                if (naiveCheckOne(col))
                {
                    // spinnedBoard[i][j] = EMPTY;
                    removePawn({j, i});
                    return true;
                }
                // printf("4. red: %d blue: %d\n", nmbOfRed, nmbOfBlue);
            }
            else
            {
                // printf("i: %d j: %d\n", i, j);

                for (int k = 0; k < size; k++)
                    for (int l = 0; l < size; l++)
                        if (spinnedBoard[k][l] == EMPTY)
                        {
                            // spinnedBoard[k][l] = col;
                            addPawn(col, {j, k});
                            // printSpinnedBoard();
                            // printf("\n");
                            if (naiveCheckOne(col))
                            {
                                removePawn({j, i});
                                removePawn({l, k});
                                return true;
                            }
                            // printf("tu\n");
                            removePawn(col, {l, k});
                        }
            }
            removePawn(begins, {j, i});
        }
        // printSpinnedBoard();
        // printf("\n\n\n");

        // printf("5. red: %d blue: %d\n", nmbOfRed, nmbOfBlue);

        // printf("red: %d blue: %d\n", nmbOfRed, nmbOfBlue);
        // printSpinnedBoard();
        // printf("\n\n\n");
    }