#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "raylib.h"

int main(void)
{
    int board[8][8] = {
        {-2, -3, -4, -5, -6, -4, -3, -2}, 
        {-1, -1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1,  1}, 
        { 2,  3,  4,  5,  6,  4,  3,  2}  
    };

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


    int selectedCol = -1;
    int selectedRow = -1;

    int turn = 1;
    int kingPos[2] = {0};
 

    int quen[8] = {-1, -1, -1, -1, -1, -1, -1, -1};



    createBoardCoardination(postionX, postionY, countPostion, &startBoardX, &startBoardY, &cout, &rectangle_X, &rectangle_Y);
    createPeasePosition(postionX, postionY, PeacePosition, PeacePositionX, PeacePositionY, &rectangle_X);

    InitWindow(screenWidth, screenHeight, "CHESS");


    Texture2D pawn_white  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/pawn_white.png");
    Texture2D pawn_black  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/pawn_black.png");

    // rock
    Texture2D rook_white  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/rock_white.png");
    Texture2D rook_black  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/rock_black.png");

    // Knight
    Texture2D knight_white = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/knight_white.png");
    Texture2D knight_black = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/knight_black.png");

    // Bishop
    Texture2D bishop_white = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/biship_white.png");
    Texture2D bishop_black = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/bishop_black.png");

    //Quean
    Texture2D queen_white  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/quean_white.png");
    Texture2D queen_black  = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/quean_black.png");

    // king
    Texture2D king_white   = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/king_white.png");
    Texture2D king_black   = LoadTexture("/Users/ixsaiw/ukf/C/projects/chess/pieces/king_black.png");


    Texture2D textrues[100];

    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            int clickedCol = GetMouseX() / rectangle_X;
            int clickedRow = GetMouseY() / rectangle_X;

            if (selectedRow == -1)
            {

                if (board[clickedRow][clickedCol] != 0 && (board[clickedRow][clickedCol] * turn > 0))
                        {
                            selectedRow = clickedRow;
                            selectedCol = clickedCol;
                        }
            }
            else
            {
                if(selectedRow == clickedRow && selectedCol == clickedCol)
                {
                    selectedCol = -1;
                    selectedRow = -1;
                }
                else if(
                        (board[selectedRow][selectedCol] > 0 && board[clickedRow][clickedCol] > 0) ||
                        (board[selectedRow][selectedCol] < 0 && board[clickedRow][clickedCol] < 0)
                        )
                {
                    selectedRow = clickedRow;
                    selectedCol = clickedCol;
                }
                else
                {
                    if (isValidMove(board, selectedRow, selectedCol, clickedRow, clickedCol))
                    {

                        int tempBoard[8][8];

                        for (int r = 0; r < 8; r++)
                        {
                            for (int c = 0; c < 8; c++)
                            {
                                tempBoard[r][c] = board[r][c];
                            }
                        }

                            tempBoard[clickedRow][clickedCol] = tempBoard[selectedRow][selectedCol];
                            tempBoard[selectedRow][selectedCol] = 0;

                        if(!isCheck(tempBoard,turn))
                        {
                            board[clickedRow][clickedCol] = board[selectedRow][selectedCol];
                            board[selectedRow][selectedCol] = 0;

                            selectedRow = -1;
                            selectedCol = -1;

                            turn = -turn;
                        }
                        else
                        {
                            selectedCol = -1;
                            selectedRow = -1;
                        }

                    }
                    else
                    {
                        selectedCol = -1;
                        selectedRow = -1;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);


        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                DrawRectangle(postionX[i][j], postionY[i][j], rectangle_X, rectangle_X, ((i + j) % 2 == 0)? BLUE : GREEN);
            }
        }

        if (selectedRow != -1 && selectedCol != -1)
        {
            DrawRectangle(postionX[selectedRow][selectedCol], postionY[selectedRow][selectedCol], rectangle_X, rectangle_X, YELLOW);
        }

        if (isCheck(board, turn))
        {
            find_king(board, turn, kingPos);
            
            DrawRectangle(postionX[kingPos[0]][kingPos[1]], postionY[kingPos[0]][kingPos[1]], rectangle_X, rectangle_X, RED);
        }

        drawBoardPieces(board,
            pawn_black, rook_black, knight_black, bishop_black, queen_black, king_black,
            pawn_white, rook_white, knight_white, bishop_white, queen_white, king_white,
            PeacePositionX, PeacePositionY
        );
        

        EndDrawing();
    }

    UnloadTexture(pawn_black);
    UnloadTexture(rook_black);
    UnloadTexture(knight_black);
    UnloadTexture(bishop_black);
    UnloadTexture(queen_black);
    UnloadTexture(king_black);

    UnloadTexture(pawn_white);
    UnloadTexture(rook_white);
    UnloadTexture(knight_white);
    UnloadTexture(bishop_white);
    UnloadTexture(queen_white);
    UnloadTexture(king_white);


    CloseWindow();
    return 0;
}
