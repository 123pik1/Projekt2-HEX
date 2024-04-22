#include "Board.hpp"
#include <stack>

Board::Board()
{
    size = 0;
    nmbOfBlue = 0;
    nmbOfRed = 0;
    visitedSetFalse();
    readBoard();
    spinBoard();
}

void Board::visitedSetFalse()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            visited[i][j] = false;
        }
    }
}

bool Board::isValidPoint(point p)
{
    return p.x >= 0 && p.x < size && p.y >= 0 && p.y < size;
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
    bool found = false;
    if (spinnedBoard[p.y][p.x] != c)
    {
        // printf("color: %c x: %d y: %d\n",c, p.x, p.y);
        return false;
    }
    if (visited[p.y][p.x])
    {
        // printf("visited x: %d y: %d\n", p.x, p.y);
        return false;
    }
    // printf("y: %d x: %d\n", p.y, p.x);
    visited[p.y][p.x] = true;
    
    if (p.y == size - 1 && c == BLUE)
    {
        // printf("x: %d y: %d\n", p.x, p.y);
        return true;
    }
    if (p.x == size - 1 && c == RED)
    {
        // printf("x: %d y: %d\n", p.x, p.y);
        return true;
    }
    // for (int i = 0; i < 6; i++)
    // {
    //     point newP = point{p.x + movesArr[i].x, p.y + movesArr[i].y};
    //     if (isValidPoint(newP) && spinnedBoard[newP.x][newP.y] == c && !visited[newP.x][newP.y])
    //     {
    //         // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
    //         if (DFS(newP, c))
    //         {
    //             printf("x: %d y: %d\n", p.x, p.y);
    //             found=true;
    //        }
    //     }
    // }
    point newP = point{p.x + 1, p.y};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    newP = point{p.x - 1, p.y};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    newP = point{p.x, p.y + 1};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    newP = point{p.x, p.y - 1};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    newP = point{p.x + 1, p.y + 1};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    newP = point{p.x - 1, p.y - 1};
    if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
    {
        // printf("color: %c  x: %d y: %d\n",c, newP.x, newP.y);
        if (DFS(newP, c))
        {
            // printf("x: %d y: %d\n", p.x, p.y);
            return true;
        }
    }
    return found;
}


bool Board::iterationDFS(point p, color c)
{
    std::stack<point> stack;
    stack.push(p);
    while (!stack.empty())
    {
        point curr = stack.top();
        stack.pop();
        if (spinnedBoard[curr.y][curr.x] != c || visited[curr.y][curr.x])
        {
            continue;
        }
        visited[curr.y][curr.x] = true;
        if (curr.y == size - 1 && c == BLUE)
        {
            return true;
        }
        if (curr.x == size - 1 && c == RED)
        {
            return true;
        }
        for (int i = 0; i < 6; i++)
        {
            point newP = point{curr.x + movesArr[i].x, curr.y + movesArr[i].y};
            if (isValidPoint(newP) && spinnedBoard[newP.y][newP.x] == c && !visited[newP.y][newP.x])
            {
                stack.push(newP);
            }
        }
    }
    return false;

}

color Board::isGameOver()
{   
    bool blueWon = false;
    bool redWon = false;
    if (!isBoardCorrect())
    {
        // printf("Board is not correct\n");
        return EMPTY;
    }
    // printf("size: %d\n", size);
    for (int i = 0; i < size; i++)
    {
        
        //               y   x                              x  y
        if (spinnedBoard[0][i] == BLUE && DFS(point{i, 0}, BLUE))
        {
            return BLUE;
        }
        if (spinnedBoard[i][0] == RED && DFS(point{0, i}, RED))
        {
            return RED;
        }
    }

    return EMPTY;
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
            p.y = actualLine - midLine + endOfLine - i + 1;
            p.x = actualLine - p.y;
            return p;
        }
    }
    return p;
}


bool Board::isBoardPossible()
{
    if (!isBoardCorrect())
    {
        return false;
    }
    visitedSetFalse();
    color wonCol = isGameOver();
    if (wonCol == EMPTY)
    {
        return true;
    }
    wonCol = isGameOver();
    if (wonCol == EMPTY)
    {
        return true;
    }



    return false;
}