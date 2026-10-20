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
extern int board[8][8];
extern int quen_P;


void createBoardCoardination(int (*postionX)[8], int (*postionY)[8], int (*countPostion)[8], int *startBoardX, int *startBoardY, int *cout, int *rectangle_X, int *rectangle_Y);

void createPeasePosition(int (*postionX)[8], int (*postionY)[8], int (*PeacePosition)[8], int (*PeacePositionX)[8], int (*PeacePositionY)[8], int *rectangle_X);

void drawBoardPieces( int board[8][8],
    Texture2D pawn_b, Texture2D rook_b, Texture2D knight_b, Texture2D bishop_b, Texture2D queen_b, Texture2D king_b,
    Texture2D pawn_w, Texture2D rook_w, Texture2D knight_w, Texture2D bishop_w, Texture2D queen_w, Texture2D king_w,
    int PeacePositionX[8][8], int PeacePositionY[8][8]
);

int isValidMove(int board[8][8], int startR, int startC, int targetR, int targetC);

int quenSolved(int row, int quen[], int n, int PeacePositionX[8][8], int PeacePositionY[8][8], int postionX[8][8], int postionY[8][8], int rectangle_X);

int isSafe(int row, int col, int quen[]);
int isCheck(int board[8][8], int turn);
void find_king(int board[8][8], int turn, int kingPos[2]);
#endif // BOARD_H
