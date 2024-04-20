#include "Board.hpp"

Board::Board()
{
    size = 0;
    nmbOfBlue = 0;
    nmbOfRed = 0;
    readBoard();
    spinBoard();
}

void Board::printBoard()
{
    for (int i = 0; i < size * size; i++)
    {

        printf("%c ", board[i]);
    }
    printf("\n");
}

void Board::printSpinnedBoard()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            printf("%c ", spinnedBoard[i][j]);
        }
        printf("\n");
    }
}

void Board::readBoard()
{

    char a;
    char entrance[10];
    int currentSize = 0;
    while (scanf("%s", entrance), strcmp(entrance, "---") != 0)
    {
        // printf("entrance: %s\n", entrance);
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

bool Board::DFS(point p, color c)
{
    // if ( spinnedBoard[p.x][p.y] != c)
    // {
    //     return false;
    // }
    visited[p.x][p.y] = true;
    if (p.x == size - 1 && c == BLUE)
    {
        return true;
    }
    if (p.y == size - 1 && c == RED)
    {
        return true;
    }
    for (int i = 0; i < 6; i++)
    {
        point newP = point{p.x + movesArr[i].x, p.y + movesArr[i].y};
        if (newP.x >= 0 && newP.x < size && newP.y >= 0 && newP.y < size)
        {
            if (DFS(newP, c))
            {
                return true;
            }
        }
    }
    // return false;
}

color Board::isGameOver()
{
    bool blueWon = false;
    bool redWon = false;
    if (!isBoardCorrect())
    {
        return EMPTY;
    }
    for (int i; i < size; i++)
    {
        if (spinnedBoard[0][i] == BLUE && DFS(point{0, i}, BLUE))
        {
            return BLUE;
        }
        if (spinnedBoard[i][0] == RED && DFS(point{i, 0}, RED))
        {
            return RED;
        }
    }

    return EMPTY;
}
int Board::getLineSize(int i)
{

    actualLineLength = 1;
    beginningOfLine = 0;
    endOfLine = 0;
    while (actualLineLength < size)
    {
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return actualLineLength;
        }
        actualLineLength++;
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
        beginningOfLine = endOfLine + 1;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            return actualLineLength;
        }
        actualLineLength--;
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
    for (int i; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            visited[i][j] = false;
        }
    }
}

bool Board::ifInRange(int i)
{
    return i >= 0 && i < size * size;
}

int Board::rightCorner()
{
    return (int)(size * (float)(size) / 2 - (float)size / 2 + size - 1);
}
int Board::leftCorner()
{
    return (int)(size * (float)(size) / 2 - (float)size / 2);
}

void Board::spinBoard()
{
    for (int i = 0; i < size * size; i++)
    {
        point p = translateToSpinned(i);
        // printf("i: %d  y: %d x: %d\n",i , p.y, p.x);
        spinnedBoard[p.y][p.x] = board[i];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            if (spinnedBoard[i][j] != BLUE && spinnedBoard[i][j] != RED)
            {
                spinnedBoard[i][j] = EMPTY;
            }
        }
    }
}

point Board::translateToSpinned(int i)
{
    point p;
    actualLineLength = 1;
    beginningOfLine = 0;
    endOfLine = 0;
    int actualLine = 0;
    int midLine = size;
    if (i == 0)
    {
        p.y = 0;
        p.x = 0;
        return p;
    }
    // if (i == size*size - 1)
    // {
    //     p.y = size - 1;
    //     p.x = size - 1;
    //     return p;
    // }
    while (actualLineLength < size)
    {
        beginningOfLine = endOfLine + 1;
        actualLineLength++;
        actualLine++;
        endOfLine += actualLineLength;

        if (i >= beginningOfLine && i <= endOfLine)
        {
            p.y = endOfLine - i;
            p.x = actualLine - p.y;
            return p;
        }
    }
    while (actualLineLength > 1)
    {
        beginningOfLine = endOfLine + 1;
        actualLineLength--;
        actualLine++;
        endOfLine += actualLineLength;
        if (i >= beginningOfLine && i <= endOfLine)
        {
            p.y = actualLine - midLine + endOfLine - i+1;
            p.x = actualLine - p.y;
            return p;
        }
    }
    return p;
}
