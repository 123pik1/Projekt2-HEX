#pragma once
#include <stdio.h>
#include <string.h>

enum color
{
    BLUE = 'b',
    RED= 'r',
    EMPTY = ' '
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
    
    //const variables
    int size;
    int nmbOfBlue;
    int nmbOfRed;
    color board[121];
    int nmbOfTiles = 0;

    //changing variables
    // int actualLineLength = 1;
    // int beginningOfLine = 0;
    // int endOfLine = 0;
    // int currLine = 0;

    //methods
    // bool isOppositeEdge(edge e1, edge e2);
    int findLineByIndex(int i);
    bool fromLeftCorner(int i);
    bool tileInMiddle(int i, int lineSize, int prevIndex, int prevPrevIndex);
    bool tileLefttUp(int i, int lineSize, int prevIndex, int prevPrevIndex);
    bool tileLeftDown(int i, int lineSize, int prevIndex, int prevPrevIndex);
    int getLineSize(int i);
    void copyBoard(color *brd);
public:
    Board();
    void readBoard();
    int getSize(){return size;}
    int getNmbOfBlue(){return nmbOfBlue;}
    int getNmbOfRed(){return nmbOfRed;}
    bool isBoardCorrect();
    color isGameOver();
    edge isEdge(int i);

};