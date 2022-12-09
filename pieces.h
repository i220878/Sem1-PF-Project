/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * Shape of each piece is represented by rows in the array.
 * TIP: Name the array what is already been coded to avoid any unwanted errors.
 */

// Name:
// Student ID:
// Assignment: PF Semester Project

// point_1 is x and y coordinates.
// It's not the diagram you were looking at.
// it's just. Some goddamn. X. And. Y. Coordinates.
// And I figured this out through two hours of headbanging and after just looking at the already existing statements.
// It's just the goddamn x and y coordinates.

// 0 and 7 are Yellow (O shape).
// 1 is Red. (Z shape)
// 2 is Green. (S shape)
// 3 is Magenta. (T shape)
// 4 is Orange. (L shape)
// 5 is Light Blue. (I shape)
// 6 is Dark Blue. (J shape)

// So % 2 should give x starting points and / 2 should give y starting points.

int BLOCKS[7][4];

void dec()
{
    // Z (Red):
    //  D (1, 0)
    // DD (0, 1) (1, 1)
    // D  (0, 2)
    BLOCKS[1][0] = 1;
    BLOCKS[1][1] = 2;
    BLOCKS[1][2] = 3;
    BLOCKS[1][3] = 4;

    // S (Green):
    // D  (0, 0)
    // DD (0, 1) (1, 1)
    //  D (1, 2)
    BLOCKS[2][0] = 0;
    BLOCKS[2][1] = 2;
    BLOCKS[2][2] = 3;
    BLOCKS[2][3] = 5;

    // T (Magenta)
    //  D (1, 0)
    // DD (0, 1) (1, 1)
    //  D (1, 2)
    BLOCKS[3][0] = 1;
    BLOCKS[3][1] = 2;
    BLOCKS[3][2] = 3;
    BLOCKS[3][3] = 5;

    // L (Orange)
    // DD (0, 0) (1, 0)
    //  D (1, 1)
    //  D (1, 2)
    BLOCKS[4][0] = 0;
    BLOCKS[4][1] = 1;
    BLOCKS[4][2] = 3;
    BLOCKS[4][3] = 5;

    // I (Light Blue)
    // D (0, 0)
    // D (0, 1)
    // D (0, 2)
    // D (0, 3)
    BLOCKS[5][0] = 0;
    BLOCKS[5][1] = 2;
    BLOCKS[5][2] = 4;
    BLOCKS[5][3] = 6;

    // J (Dark Blue)
    //  D (1, 0)
    //  D (1, 1)
    // DD (0, 2) (1, 2)
    BLOCKS[6][0] = 1;
    BLOCKS[6][1] = 3;
    BLOCKS[6][2] = 4;
    BLOCKS[6][3] = 5;

    // O (Yellow)
    //
    // DD (0, 1) (1, 1)
    // DD (0, 2) (1, 2)
    BLOCKS[0][0] = 2;
    BLOCKS[0][1] = 3;
    BLOCKS[0][2] = 4;
    BLOCKS[0][3] = 5;
}

// I thought it was done.
// At the time of writing, rotation and row clearing is the only thing left.
// But I can't use SFML's rotations since that's the image only, and the gameGrid 2D array needs values.
// So they must be predefined. Such that their coordinates make their pieces.
