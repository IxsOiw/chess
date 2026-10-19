#include "board.h"
#include "raylib.h"

int main(void)
{
    const int screenWidth = 350;
    const int screenHeight = 350;

    int startBoardX = 0;
    int startBoardY = 350;
    int cout = 64;

    int countPostion[8][8]  = { {}, {}, {}, {}, {}, {}, {}, {} };
    int postionX[8][8]      = { {}, {}, {}, {}, {}, {}, {}, {} };
    int postionY[8][8]      = { {}, {}, {}, {}, {}, {}, {}, {} };
    
    createBoardCoardination(postionX, postionY, countPostion, &startBoardX, &startBoardY, &cout);





    InitWindow(screenWidth, screenHeight, "CHESS");

    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        // Update for variables


        // Draw
        BeginDrawing();

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawRectangle(postionX[i][j],postionY[i][j], 50, 50, ((i + j) % 2 == 0)? WHITE : GREEN);
            }
        }

        EndDrawing();



    }

    CloseWindow();

    return 0;
}
