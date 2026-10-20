#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    int rectangle_X = 100;
    int rectangle_Y = 100;

    int startBoardX = 0;
    int startBoardY = 0;
    int cout = 1;

    int countPostion[8][8]  = { {0} };
    int postionX[8][8]      = { {0} };
    int postionY[8][8]      = { {0} };

    int PeacePosition[8][8]  = { {0} };
    int PeacePositionX[8][8] = { {0} };
    int PeacePositionY[8][8] = { {0} };

    int quen[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    createBoardCoardination(postionX, postionY, countPostion, &startBoardX, &startBoardY, &cout, &rectangle_X, &rectangle_Y);
    createPeasePosition(postionX, postionY, PeacePosition, PeacePositionX, PeacePositionY, &rectangle_X);

    InitWindow(screenWidth, screenHeight, "CHESS");
    SetTargetFPS(60);

    quenSolved(0, quen, 8, PeacePositionX, PeacePositionY, postionX, postionY, rectangle_X);

    while (!WindowShouldClose())    
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawRectangle(postionX[i][j], postionY[i][j], rectangle_X, rectangle_X, ((i + j) % 2 == 0)? BLUE : GREEN);
            }
        }

        for (int i = 0; i < 8; i++)
        {
            if (quen[i] != -1)
            {
                int col = quen[i];
                DrawCircle(PeacePositionX[i][col], PeacePositionY[i][col], 30, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
