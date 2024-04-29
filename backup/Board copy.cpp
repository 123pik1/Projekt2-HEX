#include "Board.hpp"
#include <stack>

Board::Board()
{
    // newBoard();
    // printSpinnedBoard();
}
void Board::newBoard()
{
    eraseBoard();

    readBoard();
    // printBoard();
    visitedSetFalse();
    spinBoard();
    // printSpinnedBoard();
}

void Board::eraseBoard()
{
    size = 0;
    nmbOfBlue = 0;
    nmbOfRed = 0;
    nmbOfTiles = 0;
    for (int i = 0; i < 121; i++)
    {
        board[i] = EMPTY;
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            spinnedBoard[i][j] = EMPTY;
            visited[i][j] = false;
        }
    }
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
    // printf("x: %d y: %d\n size: %d\n", p.x, p.y, size);
    // printf("color: %c\n on board: %c\n", c, spinnedBoard[p.y][p.x]);
    // printf("visited: %d\n", visited[p.y][p.x]);
    // bool found = false;
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
    return false;
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
    visitedSetFalse();
    printSpinnedBoard();
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
    if (blueWon && redWon)
    {
        return BOTH;
    }
    if (blueWon)
    {
        return BLUE;
    }
    if (redWon)
    {
        return RED;
    }
    return EMPTY;
}

color Board::isGameOverSkip()
{
    
}

void Board::copyBoard(color *brd)
{
    for (int i = 0; i < size * size; i++)
    {
        brd[i] = board[i];
    }
}

void Board::vistedSetFalse()
{
    for (int i = 0; i < size; i++)
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
    nmbOfBlue = 0;
    nmbOfRed = 0;
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
            if (spinnedBoard[i][j] == BLUE)
            {
                nmbOfBlue++;
            }
            if (spinnedBoard[i][j] == RED)
            {
                nmbOfRed++;
            }
        }
    }
}

point Board::translateToSpinned(int i)
{
    point p = point{0, 0};
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
    // printf("red: %d\n blue: %d\n", nmbOfRed, nmbOfBlue);
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
    if (wonCol == BOTH)
    {
        return false;
    }
    bool ifDb = ifDoubleLine();
    // printf("%d\n", ifDb);
    // printf("%c\n", wonCol);
    // printf("red: %d\n blue: %d\n", nmbOfRed, nmbOfBlue);
    if (ifDb)
        return false;
    if (wonCol == RED && nmbOfRed - 1 != nmbOfBlue)
        return false;

    if (wonCol == BLUE && nmbOfBlue != nmbOfRed)
        return false;

    // if (isGameOver() == EMPTY)
    // {
    //     if (wonCol == BLUE && nmbOfRed == nmbOfBlue)
    //         return true;
    //     if (wonCol == RED && nmbOfRed > nmbOfBlue)
    //         return true;
    // }

    return true;
}

bool Board::ifDoubleLine()
{
    color col;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            point p;
            p.x = j;
            p.y = i;
            if (isValidPoint(p))
            {
                col = spinnedBoard[i][j];
                spinnedBoard[i][j] = EMPTY;
                if (isGameOver() == EMPTY)
                {
                    spinnedBoard[i][j] = col;
                    return false;
                }
                spinnedBoard[i][j] = col;
            }
        }
    }
    return true;
}

bool Board::naiveOneRed()
{
    // printSpinnedBoard();
    if (size - nmbOfRed > 1)
        return false;
    return naiveCheckOne(RED);
}
bool Board::naiveOneBlue()
{
    if (size - nmbOfBlue > 1)
        return false;
    return naiveCheckOne(BLUE);
}



bool Board::naiveTwoRed()
{
    if (size - nmbOfRed > 2)
        return false;
    return naiveCheckTwo(RED);
}
bool Board::naiveTwoBlue()
{
    if (size - nmbOfBlue > 2)
        return false;
    return naiveCheckTwo(BLUE);
}

void Board::addPawn(color col, point p) // coś z tym nie tak? WTF?
{
    // printf("y: %d x: %d\n", p.y,p.x);
    spinnedBoard[p.y][p.x] = col;
    if (col == RED)
        nmbOfRed++;
    if (col == BLUE)
        nmbOfBlue++;
    // printSpinnedBoard();
    // printf("\n");
}

void Board::removePawn(point p)
{
    // printf("y: %d x: %d \n", p.y, p.x);
    // printSpinnedBoard();
    // printf("\n\n\n");
    if (spinnedBoard[p.y][p.x] == RED)
        nmbOfRed--;
    if (spinnedBoard[p.y][p.x] == BLUE)
        nmbOfBlue--;
    spinnedBoard[p.y][p.x] = EMPTY;
    // printSpinnedBoard();
    // printf("\n\n\n");
}

void Board::removePawn(color col, point p)
{
    if (col == RED /*&& nmbOfRed > 0*/)
        nmbOfRed--;
    if (col == BLUE /*&& nmbOfBlue > 0*/)
        nmbOfBlue--;
    spinnedBoard[p.y][p.x] = EMPTY;
}
color Board::beginCol()
{
    if (nmbOfBlue == nmbOfRed)
        return RED;
    return BLUE;
}

bool Board::naiveCheckTwo(color col)
{
    // printSpinnedBoard();
    // printf("red: %d blue %d\n", nmbOfRed, nmbOfBlue);
    // addPawn(col, {0, 1});
    // printSpinnedBoard();
    // printf("red: %d blue %d\n", nmbOfRed, nmbOfBlue);

    // removePawn({0, 1});
    // printSpinnedBoard();
    // printf("red: %d blue %d\n", nmbOfRed, nmbOfBlue);

    // spinBoard();

    if (!isBoardCorrect())
        return false;
    if (isGameOver() != EMPTY)
        return false;
    if (nmbOfBlue+nmbOfRed + 3  /* liczba ruchów * 3/2 */ + (beginCol() == col ? 0 :1)> size * size)
        return false;
    // printf("\n");
    // printSpinnedBoard();
    color begins = beginCol();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (spinnedBoard[i][j] == EMPTY)
            {
                addPawn(col, {j, i});
                if (naiveCheckOne(col))
                {
                    removePawn(col, {j, i});
                    return true;
                }
                
                // for (int k = 0; k < size; k++)
                //     for (int l = 0; l < size; l++)
                //         if (spinnedBoard[k][l] == EMPTY)
                //         {
                //             addPawn(col, {l, k});
                //             if (isGameOver() == col)
                //             {
                //                 removePawn({l, k});
                //                 removePawn({j, i});

                //                 return true;
                //             }
                //             removePawn({l, k});
                //         }
                removePawn({j, i});

                // printf("\n");
                // printSpinnedBoard();
                // if (begins == col)
                // {
                //     // if (begins == RED)
                //     // nmbOfRed++;
                //     // if (begins == BLUE)
                //     // nmbOfBlue++;
                //     if (naiveCheckOne(col))
                //     {
                //         removePawn(begins,{j, i});
                //         return true;
                //     }
                // }
                // else
                // {
                  
                    // for (int k = 0; k < size; k++)
                    //     for (int l = 0; l < size; l++)
                    //         if (spinnedBoard[k][l] == EMPTY)
                    //         {
                    // //             printf("%c\n", spinnedBoard[k][l]);
                    // //             printf("k: %d l: %d\n", k, l);
                    // // //             // spinnedBoard[k][l] = col;
                    //             addPawn(col, {l, k});
                    // // //             // printf("\n");
                    // // //             // printSpinnedBoard();
                    // // //             //             // printSpinnedBoard();
                    // // //             // printf("\n");
                    //             if (isGameOver()==col)
                    //             {
                    //                 removePawn(begins,{j, i});
                    //                 removePawn(col,{l, k});
                    //                 return true;
                    //             }
                    // // // //             // printf("tu\n");
                    // // //             // spinnedBoard[k][l] = EMPTY;
                    //             removePawn({l, k});

                    //         }
                // }
                // spinBoard();

            }
        }
    }
    // printSpinnedBoard();
    // printf("red: %d blue %d\n", nmbOfRed, nmbOfBlue);
    return false;
}

bool Board::naiveCheckOne(color col)
{

    if (!isBoardCorrect())
        return false;

    if (isGameOver() != EMPTY)
        return false;
    color begins = beginCol();
    if (nmbOfBlue + nmbOfRed + 1 /*liczba ruchów *3/2 */ + (beginCol() == col ? 0 : 1) > size * size)
        return false;
    // if (nmbOfBlue == nmbOfRed)
    //     begins = RED;
    // else
    //     begins = BLUE;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (spinnedBoard[i][j] == EMPTY)
            {
                addPawn(col, {j, i});
                // printSpinnedBoard();
                // printf("\n");
                if (isGameOver() != EMPTY)
                {
                    removePawn({j, i});
                    return true;
                }
                removePawn({j, i});



                // addPawn(begins,{j,i});
                // spinnedBoard[i][j] = begins;

                // if (begins == col)
                // {
                //     if (isGameOver() == col)
                //     {
                //         spinnedBoard[i][j] = EMPTY;
                //         return true;
                //     }
                // }
                // else
                // {
                //     for (int k = 0; k < size; k++)
                //         for (int l = 0; l < size; l++)
                //         {
                //             if (spinnedBoard[k][l] == EMPTY)
                //             {
                //                 spinnedBoard[k][l] = col;
                //                 if (isGameOver() == col)
                //                 {
                //                     spinnedBoard[k][l] = EMPTY;
                //                     spinnedBoard[i][j] = EMPTY;
                //                     return true;
                //                 }

                //                 spinnedBoard[k][l] = EMPTY;
                //             }
                //         }
                // }
                // spinnedBoard[i][j] = EMPTY;
            }
        }
    }
  
    return false;
}