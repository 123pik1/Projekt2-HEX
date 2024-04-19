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

bool Board::tileInMiddle(int i)
{
    visited[i]=true;
    actualLineLength = getLineSize(i);
    edge e = isEdge(i);
    if (board[i] == EMPTY)
    {
        return false;
    }
    if (e == RIGHT_CORNER)
    {
        return true;
    }
    else if (e == RIGHT_UP || e == UP_CORNER)
    {
        if (board[i] == RED)
            return true;
    }
    else if (e == RIGHT_DOWN || e == DOWN_CORNER)
    {
        if (board[i] == BLUE)
            return true;
        if (board[i] == board[i + actualLineLength - 1] && !visited[i + actualLineLength - 1] ) //odwołanie na boola sprawdzającego prawy dół
        {
            
        }
    }
    else 
    {
        
    }
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

bool Board::fromLeftCorner(int i)
{
    return tileInMiddle(i + 1, size, i, i);
}

bool Board::tileInMiddle(int i, int lineSize, int prevIndex, int prevPrevIndex)
{
    edge e = isEdge(i);
    if (e == RIGHT_CORNER)
    {
        return true;
    }
    else if (board[i] == RED && (e == RIGHT_UP || e == UP_CORNER))
    {
        return true;
    }
    else if (board[i] == BLUE && (e == RIGHT_DOWN || e == DOWN_CORNER))
    {
        return true;
    }
    else if (board[i] == EMPTY || board[i] != board[prevIndex] || i == prevIndex || i == prevPrevIndex)
    {
        return false;
    }
    else
    {
        // wszystkie możliwe kierunki - 6 kierunków
        return tileInMiddle(i + lineSize, getLineSize(i + lineSize), i, prevIndex) || tileInMiddle(i + lineSize + 1, getLineSize(i + lineSize + 1), i, prevIndex) || tileInMiddle(i + lineSize * 2 - 2, getLineSize(lineSize * 2 - 2), i, prevIndex) || tileInMiddle(i - lineSize, getLineSize(i - lineSize), i, prevIndex) || tileInMiddle(i - lineSize + 1, getLineSize(i - lineSize + 1), i, prevIndex) || tileInMiddle(i - lineSize * 2 + 2, getLineSize(i - lineSize * 2 + 2), i, prevIndex);
    }
}

bool Board::tileLefttUp(int i, int lineSize, int prevIndex, int prevPrevIndex)
{
    edge e = LEFT_UP;
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