#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#include "raylib.h"

int board[8][8] = {
    {-2, -3, -4, -5, -6, -4, -3, -2}, // 0: Čierne ťažké figúrky
    {-1, -1, -1, -1, -1, -1, -1, -1}, // 1: Čierni pešiaci
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 1,  1,  1,  1,  1,  1,  1,  1}, // 6: Bieli pešiaci
    { 2,  3,  4,  5,  6,  4,  3,  2}  // 7: Biele ťažké figúrky
};

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

void drawBoardPieces(int board[8][8],
    Texture2D pawn_b, Texture2D rook_b, Texture2D knight_b, Texture2D bishop_b, Texture2D queen_b, Texture2D king_b,
    Texture2D pawn_w, Texture2D rook_w, Texture2D knight_w, Texture2D bishop_w, Texture2D queen_w, Texture2D king_w,
    int PeacePositionX[8][8], int PeacePositionY[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int piece = board[i][j];
            if (piece == 0) continue; 
            Texture2D tex;
            
            switch(piece) {
                case -1: tex = pawn_b; break;
                case -2: tex = rook_b; break;
                case -3: tex = knight_b; break;
                case -4: tex = bishop_b; break;
                case -5: tex = queen_b; break;
                case -6: tex = king_b; break;
                
                case 1: tex = pawn_w; break;
                case 2: tex = rook_w; break;
                case 3: tex = knight_w; break;
                case 4: tex = bishop_w; break;
                case 5: tex = queen_w; break;
                case 6: tex = king_w; break;
            }

            int drawX = PeacePositionX[i][j] - (tex.width / 2);
            int drawY = PeacePositionY[i][j] - (tex.height / 2);

            DrawTexture(tex, drawX, drawY, WHITE);
        }
    }
}

int isValidMove(int board[8][8], int startR, int startC, int targetR, int targetC)
{
    
    int piece = board[startR][startC];

    int stepR = (targetR > startR) ? 1 : ((targetR < startR) ? -1 : 0);
    int stepC = (targetC > startC) ? 1 : ((targetC < startC) ? -1 : 0);

    int pieceType = abs(piece); 

    switch (pieceType)
    {
        case 1:
        {

            int startRowPawn = (piece > 0) ? 6 : 1; 
            int direction = (piece > 0) ? -1 : 1; 

            if (startC == targetC && targetR == startR + direction && board[targetR][targetC] == 0)
            {
                return 1;
            }

            if (startC == targetC && startR == startRowPawn && targetR == startR + (2 * direction) &&
                board[startR + direction][startC] == 0 && board[targetR][targetC] == 0)
            {
                return 1;
            }

            if (abs(startC - targetC) == 1 && targetR == startR + direction && board[targetR][targetC] != 0)
            {
                return 1;
            }

            break;
        }

        case 2:
            if (startR == targetR || startC == targetC) 
            {
                int r = startR + stepR;
                int c = startC + stepC;
                while(r != targetR || c != targetC)
                    if(board[r][c] != 0)
                    {
                      return 0;
                    }
                    else
                    {
                        r += stepR;
                        c += stepC;
                    }
                return 1;
            }
            break;

        case 3:             
            if (abs(targetR - startR) * abs(targetC - startC) == 2)
            {
                return 1;

            };
            break;

        case 4:
            if (abs(targetR - startR) == abs(targetC - startC))
            {

                int r = startR + stepR;
                int c = startC + stepC;

                while(r != targetR || c != targetC)
                {
                    if(board[r][c] != 0)
                    {
                        return 0;
                    }
                    r += stepR;
                    c += stepC;
                }
                return 1;
            }
            break;

        case 5:
            if ((startR == targetR || startC == targetC) || 
                (abs(targetR - startR) == abs(targetC - startC)))
            {
                int r = startR + stepR;
                int c = startC + stepC;

                while(r != targetR || c != targetC)
                {
                    if(board[r][c] != 0)
                    {
                        return 0;
                    }
                    r += stepR;
                    c += stepC;
                }
                return 1;
            }
            break;

        case 6: 
            if (abs(targetR - startR) <= 1 && abs(targetC - startC) <= 1) return 1;
            break;
    }
    return 0;
}
   
void find_king(int board[8][8], int turn, int kingPos[2])
{
    int king = (turn > 0) ? 6 : -6;
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(board[r][c] == king)
            {
                kingPos[0] = r;
                kingPos[1] = c;
                return;
            }
        }
    }
}

int isCheck(int board[8][8], int turn)
{
    int kingPos[2];
    find_king(board, turn, kingPos);

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            if(board[r][c] * turn < 0)
            {
                if (isValidMove(board, r, c, kingPos[0],kingPos[1]))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
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
int evaluateBoard(int board[8][8])
{
    int board_value = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            int piece = board[i][j];
            
            switch(piece) {
                case -1: board_value -= 1; break;
                case -2: board_value -= 5; break;
                case -3: board_value -= 3;break;
                case -4: board_value -= 3; break;
                case -5: board_value -= 9; break;
                case -6: board_value -= 90000; break;
                
                case 1: board_value += 1; break;
                case 2: board_value += 5; break;
                case 3: board_value += 3; break;
                case 4: board_value += 3; break;
                case 5: board_value += 9; break;
                case 6: board_value += 90000; break;
            }
            
            }
        }
    return board_value;
}


int quenSolved(int row, int quen[], int n, int PeacePositionX[8][8], int PeacePositionY[8][8], int postionX[8][8], int postionY[8][8], int rectangle_X)
{
    if (row == n) return 1;

    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col, quen))
        {
            quen[row] = col;

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

            if (quenSolved(row + 1, quen, n, PeacePositionX, PeacePositionY, postionX, postionY, rectangle_X) == 1)
            {
                return 1;
            }

            quen[row] = -1; 

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

