#include <cstdio>

int main()
{
    char tsk[50];
    scanf("%s", tsk);
    printf("%s\n", tsk);
}
switch (a)
{
case '<':
    board[currentSize] = getchar();
    if (board[currentSize] == 'r')
    {
        nmbOfRed++;
    }
    else if (board[currentSize] == 'b')
    {
        nmbOfBlue++;
    }

    currentSize++;

    break;
case '\n':

    if (currentSize > size)
    {

        size = currentSize;
    }
    currentSize = 0;
    break;
case 'r':
    nmbOfRed++;
    break;

case 'b':

    nmbOfBlue++;
    break;
case '-':
    if (prev == '-' && prev2 == '-')
    {
        // if (!skip)
        {
            return;
        }
        skip = false;
    }
    break;
default:
    break;
}