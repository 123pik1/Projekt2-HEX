#include "Board.hpp"

Board::Board()
{
    size = 0;
    nmbOfBlue = 0;
    nmbOfRed = 0;
    readBoard();
}

void Board::readBoard()
{
    char a;
    char entrance[10];
    int currentSize = 0;
    while (scanf("%s", entrance), strcmp(entrance, "---") != 0)
    {
        if (entrance[0] == '<' || strcmp(entrance, "--<") == 0 || strcmp(entrance, ">-<") == 0)
        {
            scanf("%c", &a);
            scanf("%c", &a);

            currentSize++;
            if (a == 'r')
            {
                nmbOfRed++;
                board[nmbOfTiles] = RED;
            }
            else if (a == 'b')
            {
                nmbOfBlue++;
                board[nmbOfTiles] = BLUE;
            }
            else
            {
                board[nmbOfTiles] = EMPTY;
            }
            nmbOfTiles++;
        }
        else if (strcmp(entrance, ">--") == 0 || strcmp(entrance, ">") == 0)
        {
            if (currentSize > size)
            {
                size = currentSize;
            }
            currentSize = 0;
        }
    }
}

bool Board::isBoardCorrect()
{
    return (nmbOfBlue == nmbOfRed || nmbOfRed - nmbOfBlue == 1);
}

edge Board::isEdge(int i)
{
    int actualLineLength = 1;
    int beginningOfLine = 0;
    int endOfLine = 0;
    if (i == 0)
    {
        return UP_CORNER;
    }
    if (i == nmbOfTiles - 1)
    {
        return DOWN_CORNER;
    }
    if (i == size * (size - 1))
    {
        return LEFT_CORNER;
    }
    if (i == size * size - 1)
    {
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
    if (actualLineLength == size)
    {
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i == beginningOfLine)
        {
            return LEFT_CORNER;
        }
        else if (i == endOfLine)
        {
            return RIGHT_CORNER;
        }
    }
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
    actualLineLength = 1;
    beginningOfLine = 0;
    endOfLine = 0;

    if (!isBoardCorrect())
        return EMPTY;
    for (int i = 0; i < nmbOfTiles; i++)
    {
        if (i > endOfLine)
        {
            if (i < size * size / 2)
            {
                actualLineLength++;
                beginningOfLine = endOfLine + 1;
                endOfLine += actualLineLength;
            }
            else
            {
                actualLineLength--;
                beginningOfLine = endOfLine + 1;
                endOfLine += actualLineLength;
            }
        }
        if (board[i] != EMPTY)
        {
            edge ed = isEdge(i);
            if (ed == LEFT_CORNER)
            {
                if (fromLeftCorner(i))
                {
                    return board[i];
                }
            }
            else if (ed == LEFT_UP && board[i] == RED)
            {
            }
            else if (ed == LEFT_DOWN && board[i] == BLUE)
            {
            }
        }
    }

    return EMPTY;
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


int Board::getLineSize(int i)
{
    actualLineLength = 1;
    beginningOfLine = 0;
    endOfLine = 0;
    while (actualLineLength < size)
    {
        actualLineLength++;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return actualLineLength;
        }
    }
    if (actualLineLength == size)
    {
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return actualLineLength;
        }
    }
    while (actualLineLength < size * size - 1)
    {
        actualLineLength--;
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return actualLineLength;
        }
    }
    return actualLineLength;
}

void Board::copyBoard(color *brd)
{
    for (int i; i < size * size; i++)
    {
        brd[i] = board[i];
    }
}

void Board::vistedSetFalse()
{
    for (int i; i < size * size; i++)
    {
        visited[i] = false;
    }
}