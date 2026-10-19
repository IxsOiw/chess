#include <stdio.h>

#include "board.h"


void createBoardCoardination(int (*postionX)[8], int (*postionY)[8],int (*countPostion)[8], int *startBoardX, int *startBoardY, int *cout)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            postionX[i][j] = *startBoardX;
            *startBoardX += 50;

            postionY[i][j] = *startBoardY;

            countPostion[i][j] =  *cout;
            cout++;
            
        }
        *startBoardX = 0;
        *startBoardY -= 50;
    }

}

/*
int main(void)
{

    createBoardCoardination(postionX, postionY, countPostion, &startBoardX, &startBoardY, &cout);

    for(int i = 0; i < 8; i++)
    {
        printf("--------------------------");
        for(int j = 0; j < 8; j++)
        {
            printf("| %d -> (%d, %d)", countPostion[i][j] ,postionX[i][j], postionY[i][j]);
        }
        printf("--------------------------");
        printf("\n");
    }

    return 0;
}
*/

