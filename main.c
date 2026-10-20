#include "raylib.h"

#include "chess_board/board.h"

int main(void)
{
    const int screenWidth = 680;
    const int screenHeight = 680;

    int rectangle_X = 85;
    int rectangle_Y = 85;

    int startBoardX = 0;
    int startBoardY = 600;
    int cout = 64;

    int countPostion[8][8]  = { {}, {}, {}, {}, {}, {}, {}, {} };
    int postionX[8][8]      = { {}, {}, {}, {}, {}, {}, {}, {} };
    int postionY[8][8]      = { {}, {}, {}, {}, {}, {}, {}, {} };
    
    createBoardCoardination(postionX, postionY, countPostion, &startBoardX, &startBoardY, &cout, &rectangle_X, &rectangle_Y);

    InitWindow(screenWidth, screenHeight, "CHESS");

    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        // Update for variables


        // Draw
        BeginDrawing();

        // main board
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawRectangle(postionX[i][j],postionY[i][j], rectangle_X, rectangle_X, ((i + j) % 2 == 0)? BLUE : GREEN);
            }
        }

        // white peace 
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawCircle((postionX[i][j] + (rectangle_X / 2)), postionY[i][j] + 25, 15, WHITE);
            }
        }

        // black peace
        for(int i = 7; i > 5; i--)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawCircle((postionX[i][j] + (rectangle_X / 2)), postionY[i][j] + 25, 15, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
