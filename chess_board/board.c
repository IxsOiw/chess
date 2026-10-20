#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#include "raylib.h"

void createBoardCoardination(int (*postionX)[8], int (*postionY)[8], int (*countPostion)[8], int *startBoardX, int *startBoardY, int *cout, int *rectangle_X, int *rectangle_Y)
{
    int currentX = *startBoardX;
    int currentY = *startBoardY;

    for(int i = 0; i < 8; i++)
    {
        currentX = 0;
        for(int j = 0; j < 8; j++)
        {
            postionX[i][j] = currentX;
            currentX += *rectangle_X;

            postionY[i][j] = currentY;

            countPostion[i][j] = *cout;
            *cout += 1;
        }
        currentY += *rectangle_Y;
    }
}

void createPeasePosition(int (*postionX)[8], int (*postionY)[8], int (*PeacePosition)[8], int (*PeacePositionX)[8], int (*PeacePositionY)[8], int *rectangle_X)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            PeacePositionX[i][j] = (postionX[i][j] + (*rectangle_X / 2));
            PeacePositionY[i][j] = (postionY[i][j] + (*rectangle_X / 2));
        }
    }
}

int isSafe(int row, int col, int quen[])
{
    for (int i = 0; i < row; i++)
    {
        if (quen[i] == col)
        {
            return 0;
        }

        if ((row - i) == abs(col - quen[i]))
        {
            return 0;
        }
    }

    return 1;
}

int quenSolved(int row, int quen[], int n, int PeacePositionX[8][8], int PeacePositionY[8][8], int postionX[8][8], int postionY[8][8], int rectangle_X)
{
    if (row == n) return 1;

    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col, quen))
        {
            quen[row] = col; // Položíme kráľovnú

            // --- VIZUALIZÁCIA (KROK VPRED) ---
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // 1. Nakresli šachovnicu
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    DrawRectangle(postionX[i][j], postionY[i][j], rectangle_X, rectangle_X, ((i + j) % 2 == 0) ? BLUE : GREEN);
                }
            }
            // 2. Nakresli aktuálne kráľovné
            for (int i = 0; i < 8; i++) {
                if (quen[i] != -1) {
                    DrawCircle(PeacePositionX[i][quen[i]], PeacePositionY[i][quen[i]], 30, RED);
                }
            }
            EndDrawing();
            WaitTime(0.15); // Pauza pre efekt krokvoania

            // Rekurzívny posun
            if (quenSolved(row + 1, quen, n, PeacePositionX, PeacePositionY, postionX, postionY, rectangle_X) == 1)
            {
                return 1;
            }

            // --- BACKTRACKING (KROK SPÄŤ) ---
            quen[row] = -1; // Odoberieme kráľovnú

            // --- VIZUALIZÁCIA (ZMAZANIE KRÁĽOVNE PRI BACKTRACKINGU) ---
            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    DrawRectangle(postionX[i][j], postionY[i][j], rectangle_X, rectangle_X, ((i + j) % 2 == 0) ? BLUE : GREEN);
                }
            }
            for (int i = 0; i < 8; i++) {
                if (quen[i] != -1) {
                    DrawCircle(PeacePositionX[i][quen[i]], PeacePositionY[i][quen[i]], 30, RED);
                }
            }
            EndDrawing();
            WaitTime(0.15);
        }
    }

    return 0;
}
