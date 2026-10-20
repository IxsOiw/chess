#ifndef BOARD_H   /* Include guard */
#define BOARD_H

#include "raylib.h"
#include <stdlib.h>

extern int startBoardX;
extern int startBoardY;
extern int count;
extern int rectangle_X;
extern int rectangle_Y;

extern int grid[8][8];
extern int postionX[8][8];
extern int postionY[8][8];
extern int PeacePositionX[8][8];
extern int PeacePositionY[8][8];
extern int quen_P;

void createBoardCoardination(int (*postionX)[8], int (*postionY)[8], int (*countPostion)[8], int *startBoardX, int *startBoardY, int *cout, int *rectangle_X, int *rectangle_Y);

void createPeasePosition(int (*postionX)[8], int (*postionY)[8], int (*PeacePosition)[8], int (*PeacePositionX)[8], int (*PeacePositionY)[8], int *rectangle_X);

int quenSolved(int row, int quen[], int n, int PeacePositionX[8][8], int PeacePositionY[8][8], int postionX[8][8], int postionY[8][8], int rectangle_X);

int isSafe(int row, int col, int quen[]);

#endif // BOARD_H
