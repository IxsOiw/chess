#ifndef board   /* Include guard */
#define board

// variables;

extern int startBoardX;
extern int startBoardY;
extern int count;
extern int rectangle_X;

// extern int countPostion[8][8];
extern int postionX[8][8];
extern int postionY[8][8];

void createBoardCoardination(int (*postionX)[8], int (*postionY)[8],int (*countPostion)[8], int *startBoardX, int *startBoardY, int *cout, int *rectangle_X, int *rectangle_Y);
#endif // board
