
bool Board::DFS(int i, color c)
{
    // if (!visited[i])
    // printf("i: %d\n", i);
    if (board[i] != c || visited[i])
    {

        return false;
    }

    edge ed = isEdge(i);
    // if (i==10) printf("ed: %d\n", ed);
    // if (i==6) printf("ed: %d\n", ed);
    visited[i] = true;
    if (ed == RIGHT_CORNER)
    {
        return true;
    }
    if (ed == LEFT_CORNER)
    {

        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i - 1);
        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }
    }
    else if (ed == LEFT_UP)
    {
        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (ifInRange(i + actualLineLength + 1) && DFS(i + actualLineLength + 1, c))
        {
            return true;
        }
        if (ifInRange(i + actualLineLength + getLineSize(i + actualLineLength)) && DFS(i + actualLineLength + getLineSize(i + actualLineLength), c))
        {
            return true;
        }

        actualLineLength = getLineSize(i - 1);
        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }
    }
    else if (ed == LEFT_DOWN)
    {
        actualLineLength = getLineSize(i);
        // printf("actualLineLength: %d\n", actualLineLength);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i - 1);
        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }
        if (ifInRange(i - actualLineLength + 1) && DFS(i - actualLineLength + 1, c))
        {
            return true;
        }
        if (ifInRange(i - actualLineLength - getLineSize(i - actualLineLength)) && DFS(i - actualLineLength - getLineSize(i - actualLineLength), c))
        {
            return true;
        }
    }
    else if (ed == UP_CORNER)
    {
        if (c == BLUE)
            return true;
        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength + 1) && DFS(i + actualLineLength + 1, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i);
        if (ifInRange(i + 4) && DFS(i + 4, c))
        {
            return true;
        }
    }
    else if (ed == DOWN_CORNER)
    {
        if (c == RED)
            return true;
        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (ifInRange(i + actualLineLength - 1) && DFS(i + actualLineLength - 1, c))
        {
            return true;
        }
        if (ifInRange(i - 4) && DFS(i - 4, c))
        {
            return true;
        }
    }
    else if (ed == RIGHT_UP)
    {
        if (c == BLUE)
            return true;
        actualLineLength = getLineSize(i);
        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i + 1);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (ifInRange(i + actualLineLength - 1) && DFS(i + actualLineLength - 1, c))
        {
            return true;
        }
        if (ifInRange(i + actualLineLength + getLineSize(i + actualLineLength + 1)) && DFS(i + actualLineLength + getLineSize(i + actualLineLength + 1), c)) // te mogą być do poprawy
        {
            return true;
        }
    }
    else if (ed == RIGHT_DOWN)
    {
        if (c == RED)
        {
            printf("i: %d\n", i);
            return true;
        }
        actualLineLength = getLineSize(i + 1);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i - actualLineLength);
        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }
        if (ifInRange(i - actualLineLength - 1) && DFS(i - actualLineLength - 1, c))
        {
            return true;
        }
        if (ifInRange(i - actualLineLength - getLineSize(i - actualLineLength * 2)) && DFS(i - actualLineLength - getLineSize(i - actualLineLength * 2), c))
        {
            return true;
        }
    }
    else if (ed == RIGHT_CORNER)
    {
        return true;
    }
    else
    {
        int newI;
        actualLineLength = getLineSize(i);
        if (ifInRange(i + actualLineLength) && DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i);

        if (ifInRange(i - actualLineLength) && DFS(i - actualLineLength, c))
        {
            return true;
        }

        //

        if (i < leftCorner()) //góra
        {
            actualLineLength = getLineSize(i);
            if (ifInRange(i - actualLineLength + 1) && DFS(i - actualLineLength + 1, c))
            {
                return true;
            }
            actualLineLength = getLineSize(i);
            if (ifInRange(i + actualLineLength + 1) && DFS(i + actualLineLength - 1, c))
            {
                return true;
            }
        }
        else if (i > rightCorner()) //dół
        {
            actualLineLength = getLineSize(i);
            if (ifInRange(i - actualLineLength - 1) && DFS(i - actualLineLength - 1, c))
            {
                return true;
            }
            actualLineLength = getLineSize(i);
            if (ifInRange(i + actualLineLength - 1) && DFS(i + actualLineLength - 1, c))
            {
                return true;
            }
        }
        else //środek
        {
            actualLineLength = getLineSize(i);
            if (ifInRange(i - actualLineLength + 1) && DFS(i - actualLineLength + 1, c))
            {
                return true;
            }
            actualLineLength = getLineSize(i);
            if (ifInRange(i + actualLineLength - 1) && DFS(i + actualLineLength - 1, c))
            {
                return true;
            }
        }

    }
    // actualLineLength = getLineSize(i);
    // if (ifInRange(i + actualLineLength + 1) && DFS(i + actualLineLength + 1, c))
    // {
    //     return true;
    // }

    // actualLineLength = getLineSize(i);

    // if (ifInRange(i - actualLineLength + 1) && DFS(i - actualLineLength + 1, c))
    // {
    //     return true;
    // }
    // int newI = i - actualLineLength;
    // actualLineLength = getLineSize(newI);
    // if (ifInRange(newI - actualLineLength) && DFS(newI - actualLineLength, c))
    // {
    //     return true;
    // }
    // actualLineLength = getLineSize(i);
    // newI = i + actualLineLength;
    // actualLineLength = getLineSize(newI);
    // if (ifInRange(newI + actualLineLength) && DFS(newI + actualLineLength, c))
    // {
    //     return true;
    // }

return false;
}

int Board::findLineByIndex(int i)
{
    int actualLineLength = 1;
    int beginningOfLine = 0;
    int endOfLine = 0;
    int currLine = 0;
    while (actualLineLength < size)
    {
        actualLineLength++;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return currLine;
        }
        currLine++;
    }
    if (actualLineLength == size)
    {
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return currLine;
        }
        currLine++;
    }
    while (actualLineLength < size * size - 1)
    {
        actualLineLength--;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return currLine;
        }
        currLine++;
    }
    return currLine;
}
edge Board::isEdge(int i)
{
    actualLineLength = 1;
    beginningOfLine = 0;
    endOfLine = 0;
    if (i == 0)
    {
        return UP_CORNER;
    }
    if (i == nmbOfTiles - 1)
    {
        return DOWN_CORNER;
    }
    if (i == leftCorner())
    {
        return LEFT_CORNER;
    }
    if (i == rightCorner())
    {
        // printf("i: %d\n", i);
        return RIGHT_CORNER;
    }
    while (actualLineLength < size)
    {
        actualLineLength++;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            if (i == beginningOfLine)
            {
                return LEFT_UP;
            }
            else if (i == endOfLine)
            {
                return RIGHT_UP;
            }
            else
            {
                return NO_EDGE;
            }
        }
    }
    // if (actualLineLength == size)
    // {
    //     beginningOfLine = endOfLine + 1;
    //     endOfLine += actualLineLength;
    //     if (i == beginningOfLine)
    //     {
    //         return LEFT_CORNER;
    //     }
    //     else if (i == endOfLine)
    //     {
    //         return RIGHT_CORNER;
    //     }
    // }
    while (actualLineLength < size * size - 1)
    {
        actualLineLength--;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            if (i == beginningOfLine)
            {
                return LEFT_DOWN;
            }
            else if (i == endOfLine)
            {
                return RIGHT_DOWN;
            }
            else
            {
                return NO_EDGE;
            }
        }
    }
    return NO_EDGE;
}

color Board::isGameOver()
{

    if (!isBoardCorrect())
    {
        return EMPTY;
    }
    for (int i = 0; i < size * size; i++)
    {
        edge ed = isEdge(i);
        // printf("ed: %d\n", ed);
        if ((ed == UP_CORNER || ed == LEFT_UP || ed == LEFT_CORNER) && board[i] == RED)
        {
            // printf("RED i: %d\n", i);

            if (DFS(i, RED))
            {
                printf("i: %d\n", i);
                return RED;
            }
        }
        if ((ed == DOWN_CORNER || ed == LEFT_DOWN || ed == LEFT_CORNER) && board[i] == BLUE)
        {
            // printf("i: %d\n", i);
            if (DFS(i, BLUE))
            {
                return BLUE;
            }
        }
    }
    return EMPTY;
}
