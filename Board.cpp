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
    for (int i=0; i<size*size;i++)
    {
        edge ed = isEdge(i);
        if ((ed == UP_CORNER || ed==LEFT_UP || ed==RIGHT_CORNER)&&board[i]==RED)
        {
            if (DFS(i, RED))
            {
                return RED;
            }
        }
        if ((ed == DOWN_CORNER || ed==LEFT_DOWN || ed==RIGHT_CORNER)&&board[i]==BLUE)
        {
            if (DFS(i, BLUE))
            {
                return BLUE;
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

bool Board::DFS(int i, color c)
{
    if (board[i] != c || visited[i])
    {
        return false;
    }
    edge ed = isEdge(i);
    visited[i] = true;
    if (ed == RIGHT_CORNER)
    {
        return true;
    }
    if (ed == LEFT_CORNER)
    {
        actualLineLength = getLineSize(i);
        if (DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i - 1);
        if (DFS(i - actualLineLength, c))
        {
            return true;
        }
    }
    else if (ed == LEFT_UP)
    {
        actualLineLength = getLineSize(i);
        if (DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (DFS(i + actualLineLength + 1, c))
        {
            return true;
        }
        if (DFS(i + actualLineLength + getLineSize(i + actualLineLength), c))
        {
            return true;
        }

        actualLineLength = getLineSize(i - 1);
        if (DFS(i - actualLineLength, c))
        {
            return true;
        }
    }
    else if (ed == LEFT_DOWN)
    {
        actualLineLength = getLineSize(i);
        if (DFS(i + actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i - 1);
        if (DFS(i - actualLineLength, c))
        {
            return true;
        }
        if (DFS(i - actualLineLength + 1, c))
        {
            return true;
        }
        if (DFS(i - actualLineLength - getLineSize(i - actualLineLength), c))
        {
            return true;
        }
    }
    else if (ed == UP_CORNER)
    {
        if (c == BLUE)
            return true;
        actualLineLength = getLineSize(i);
        if (DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (DFS(i + actualLineLength + 1, c))
        {
            return true;
        }
    }
    else if (ed == DOWN_CORNER)
    {
        if (c == RED)
            return true;
        actualLineLength = getLineSize(i);
        if (DFS(i + actualLineLength, c))
        {
            return true;
        }
        if (DFS(i + actualLineLength - 1, c))
        {
            return true;
        }
    }
    else if (ed == RIGHT_UP)
    {
        if (c==BLUE)
            return true;
        actualLineLength = getLineSize(i);
        if (DFS(i-actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i+1);
        if (DFS(i+actualLineLength, c))
        {
            return true;
        }
        if (DFS(i+actualLineLength-1, c))
        {
            return true;
        }
        if (DFS(i+actualLineLength+getLineSize(i+actualLineLength+1), c)) //te mogą być do poprawy
        {
            return true;
        }
    }
    else if (ed == RIGHT_DOWN)
    {
        if (c==RED)
            return true;
        actualLineLength = getLineSize(i+1);
        if (DFS(i+actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i-actualLineLength);
        if (DFS(i-actualLineLength, c))
        {
            return true;
        }
        if (DFS(i-actualLineLength-1, c))
        {
            return true;
        }
        if (DFS(i-actualLineLength-getLineSize(i-actualLineLength*2), c))
        {
            return true;
        }
    }
    else if (ed==RIGHT_CORNER)
    {
        return true;
    }
    else 
    {
        actualLineLength = getLineSize(i);
        if (DFS(i+actualLineLength, c))
        {
            return true;
        }
        if (DFS(i+actualLineLength+1, c))
        {
            return true;
        }
        if (DFS(i-actualLineLength, c))
        {
            return true;
        }
        if (DFS(i-actualLineLength+1, c))
        {
            return true;
        }
        int newI = i - actualLineLength;
        actualLineLength = getLineSize(newI);
        if (DFS(newI-actualLineLength, c))
        {
            return true;
        }
        actualLineLength = getLineSize(i);
        newI = i + actualLineLength;
        actualLineLength = getLineSize(newI);
        if (DFS(newI+actualLineLength, c))
        {
            return true;
        }
    }
    return false;
}
void Board::vistedSetFalse()
{
    for (int i; i < size * size; i++)
    {
        visited[i] = false;
    }
}

