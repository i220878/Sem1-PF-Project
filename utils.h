/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * TIP: After completing your project, you can make changes for aesthetics.
 * */

// Name: Muhammad Ibrahim Awais
// Student ID: 22i-0878
// Assignment: PF Semester Project

//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "PF-Project, Fall-2022";

//---Height and Width of the Actual Interactive Game---//
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2];
// I did not understand point_2, and thus I did not use point_2.

//---Check Uncertain Conditions---//
bool anomaly(int x[], int &xLimL, int &xLimR, int &yLimU)
{
    // Anomaly only checks for when the piece is deployed. It doesn't check for collision during that time.
    // No wonder the pieces are passing through.
    for (int i = 0; i < 4; i++)
    {
        if (point_1[i][1] >= M)
        // This is kept at point_1 instead of x[i] because then it considers a boundary an anomaly.
            return 0;
        else if (gameGrid[point_1[i][1] - 0][x[i]]) // The - 0 is there because I want a reminder of my trial and error attempts.
            return 0;
    }
    return 1;
}