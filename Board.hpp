#pragma once
#include <stdio.h>
#include <string.h>

enum color
{
    BLUE = 'b',
    RED = 'r',
    EMPTY = '_',
    BOTH = 'x'
};

struct point
{
    int x;
    int y;
};

struct moves
{
    int x;
    int y;
};

enum edge
{
    LEFT_UP = 0,
    LEFT_DOWN = 1,
    RIGHT_UP = 2,
    RIGHT_DOWN = 3,
    UP_CORNER = 4,
    DOWN_CORNER = 5,
    LEFT_CORNER = 6,
    RIGHT_CORNER = 7,
    NO_EDGE = 8
};

class Board
{
private:
    // const variables
    int size;
    int nmbOfBlue;
    int nmbOfRed;
    color board[121];
    color spinnedBoard[11][11];
    int nmbOfTiles = 0;
    moves movesArr[6] = {
        {0, 1}, // down
        {1, 0},  // right
        {-1, 0}, // left
        {0, -1}, // up
        {1, 1},  // right-down
        {-1, -1} // left-up};
    };
    // changing variables
    int actualLineLength = 1;
    int beginningOfLine = 0;
    int endOfLine = 0;
    int currLine = 0;
    bool visited[11][11];

    // methods
    //  bool isOppositeEdge(edge e1, edge e2);
    bool DFS(point p, color c);
    bool iterationDFS(point p, color c);
    bool ifInRange(int i);
    int rightCorner();
    int leftCorner();
    void copyBoard(color *brd);
    void vistedSetFalse();
    void spinBoard();
    point translateToSpinned(int i);
    int getLineInSpinned(int i);
    bool isValidPoint(point p);
    bool ifDoubleLine();
    bool naiveCheckOne(color col);
    bool naiveCheckTwo(color col);
    void addPawn(color col,point p);
    void removePawn( point p);
    void removePawn(color col,point p);
    color beginCol();
    color isGameOverSkip();
    bool naiveCheckOneSkip(color col);
public:
    Board();
    void eraseBoard();
    void newBoard();
    void visitedSetFalse();
    bool naiveOneRed();
    bool naiveOneBlue();
    bool naiveTwoRed();
    bool naiveTwoBlue();
    void printBoard();
    void printSpinnedBoard();
    void readBoard();
    bool isBoardPossible();
    int getSize() { return size; }
    int getNmbOfBlue() { return nmbOfBlue; }
    int getNmbOfRed() { return nmbOfRed; }
    bool isBoardCorrect();
    color isGameOver();
    edge isEdge(int i);
};