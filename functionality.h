/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

// Name:
// Student ID:
// Assignment: PF Semester Project

//---Piece Starts to Fall When Game Starts---//
#include <iostream>

// These were included for the bomb
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

// These were included for the score
#include <cmath>
#include <string>
    
void explosion(int &colorNum, int x[], int &score, sf::Sprite &sprite, sf::RenderWindow &window,
              sf::Sprite frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1, int &level, 
              sf::Text &levelText, int p[], sf::Sprite &pieces, sf::Sprite &shrinkBlock, int &xLimL, int &xLimR); 
              // Prototyping this because it gets called in fallingPiece() for the bomb.

void gridSize(float &gTime, int &xLimL, int &xLimR, int &yLimU); 
// Prototyping this because it gets called in fallingPiece() so the grid only shrinks
// when a piece is done falling.
float levelValues(int &level, int &score);
// Prototyping this because it gets used in the start of the game, since Level 1.

int nextPieces(int p[]); // Next Pieces.
// Prototyping this because I just forgot to do it earlier so it's written later and I don't want to disturb the order.

void shapeBreak(int &score, int &xLimL, int &xLimR, sf::Sprite &sprite, sf::RenderWindow &window,
              sf::Sprite frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1, int &level, 
              sf::Text &levelText, int p[], sf::Sprite pieces, sf::Sprite shrinkBlock);
// This was already prototyped, I don't remember why, but I don't want to mess with it.

void fallingPiece(float &timer, float &delay, int &colorNum, int x[], int &rCount, bool &isBomb,
                  sf::Sprite &sprite, sf::Texture &bomba, sf::Texture &bombWhite, 
                  sf::RenderWindow &window, sf::Sprite &frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1,
                  int &xLimL, int &xLimR, int &yLimU, float &gTime, sf::Sprite &shrinkBlock,
                  int &level, int &score, sf::Text &levelText, int p[], int pMirror[], sf::Sprite &pieces)
{
    sf::SoundBuffer buffer;
    sf::Sound sound;

    buffer.loadFromFile("audio/bombaDrop.wav"); // Sound that plays when the bomb drops.
    sound.setBuffer(buffer);

    sf::Sprite gameGridBlocks;
    sf::Texture obj1;
    obj1.loadFromFile("img/tiles.png");
    gameGridBlocks.setTexture(obj1);

    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
            point_1[i][1] += 1;
        if (!anomaly(x, xLimL, xLimR, yLimU)) // Return 1 is if the anomaly isn't happening. Return 0 is if it's happening.
        // So this statement is checking if it's happening, and gets triggered if it's happening.
        {
            int n = nextPieces(p); // Put here so the bomb doesn't cause chaos with the Pieces queue
            if(isBomb == true) // If the piece is a bomb (from previous code) then play the detonating animation
            {
                sf::Clock clock;

                float bombTime = 0;

                sound.play();

                // All the upcoming code is for the bomb animation
                while(bombTime < 4.0) // 4 seconds
                {
                    window.clear(sf::Color::Black);

                    bombTime = clock.getElapsedTime().asSeconds();

                    // Flashing Texture
                    if(bombTime > 0 && bombTime < 1.0)
                        sprite.setTexture(bomba);
                    if(bombTime > 1.0 && bombTime < 1.1)
                        sprite.setTexture(bombWhite);
                    if(bombTime > 1.1 && bombTime < 1.5)
                        sprite.setTexture(bomba);
                    if(bombTime > 1.5 && bombTime < 1.6) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 1.6 && bombTime < 2.4)
                        sprite.setTexture(bomba);
                    if(bombTime > 2.4 && bombTime < 2.5)
                        sprite.setTexture(bombWhite);
                    if(bombTime > 2.5 && bombTime < 2.9)
                        sprite.setTexture(bomba);
                    if(bombTime > 2.9 && bombTime < 3.0) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 3.0 && bombTime < 3.3)
                        sprite.setTexture(bomba);
                    if(bombTime > 3.3 && bombTime < 3.4) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 3.4 && bombTime < 3.5)
                        sprite.setTexture(bomba);
                    if(bombTime > 3.5 && bombTime < 3.55) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 3.55 && bombTime < 3.6)
                        sprite.setTexture(bomba);
                    if(bombTime > 3.6 && bombTime < 3.65) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 3.65 && bombTime < 3.7)
                        sprite.setTexture(bomba);
                    if(bombTime > 3.7 && bombTime < 3.5) 
                        sprite.setTexture(bombWhite);
                    if(bombTime > 3.75 && bombTime < 3.8)
                        sprite.setTexture(bomba);
                    if(bombTime > 3.8) 
                        sprite.setTexture(bombWhite);

                    
                    // Color of Bomb
                    if(colorNum == 0)
                        sprite.setColor(sf::Color::Yellow);
                    else if(colorNum == 1)
                        sprite.setColor(sf::Color::Red);
                    else if(colorNum == 2)
                        sprite.setColor(sf::Color::Green);
                    else if(colorNum == 3)
                        sprite.setColor(sf::Color::Magenta);
                    else if(colorNum == 4)
                        sprite.setColor(sf::Color{255, 103, 0});
                    else if(colorNum == 5)
                        sprite.setColor(sf::Color{140, 255, 255});
                    else if(colorNum == 6)
                        sprite.setColor(sf::Color{12, 140, 255});

                    window.draw(background);
                    // shrinkBlock and gameGridBlocks were used so previous gameGrid values were remembered.
                    // gameGrid gets modified with the explosion after all.
                    
                    for (int i = 0; i < M; i++)
                    {
                        for (int j = 0; j < N; j++)
                        {
                            if (gameGrid[i][j] == 0)
                            {
                                continue;
                            }
                            if (gameGrid[i][j] == 8)
                            {
                                shrinkBlock.setPosition(j * 18, i * 18);
                                shrinkBlock.move(28 + 18 * 0, 31);
                                window.draw(shrinkBlock);
                            }
                            else
                            {
                                gameGridBlocks.setTextureRect(sf::IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                                gameGridBlocks.setPosition(j * 18, i * 18);
                                gameGridBlocks.move(28 + 18 * 0, 31);
                                window.draw(gameGridBlocks);
                            }
                        }
                    }
                    // This is here so the background isn't drawn over it.
                    // This is the flashing white 'screen' effect.
                    if((bombTime > 3.6 && bombTime < 3.65) || (bombTime > 3.7 && bombTime < 3.75) || (bombTime > 3.8))
                    {
                        sf::RectangleShape box;
                        box.setPosition(sf::Vector2f(28, 31));
                        box.setSize(sf::Vector2f(18*10, 18*20));
                        box.setFillColor(sf::Color{255, 255, 255, 127});
                        window.draw(box);
                    }

                    int k = 0;
                    if(level == 1 || level == 2)
                        k = 4;
                    else if(level == 3 || level == 4)
                        k = 3;
                    else if(level == 5 || level == 6)
                        k = 2;
                    else
                        k = 1;
                    
                    for(int i = 0; i < k - 1; i++) // It's set to i = 0 here because the change has already happened
                    // So it's not supposed to show the next piece
                    // It's also set to k - 1 because it goes back and redraws pieces in the main function.
                        for(int j = 0; j < 4; j++)
                        {
                            pieces.setTextureRect(sf::IntRect(p[i] * 18, 0, 18, 18));
                            pieces.setPosition(250, 140 + 80 * (i + 1));
                            if(p[i] == 5)
                                pieces.setPosition(250, 140 + 80 * (i + 1) - 10);
                            pieces.move(18 * (BLOCKS[p[i]][j] % 2), 18 * (BLOCKS[p[i]][j] / 2));
                            window.draw(pieces);
                        }
                    window.draw(sprite);
                    window.draw(frame);
                    window.draw(textScore);
                    window.draw(text1);
                    window.draw(levelText);
                    window.display();

                    // In a nutshell: The ENTIRE FRAME has to redraw elements of previous frames for the animation.
                } // Animation finishes

                bombTime = 0; // It was bugging out. This was added to reset it.
                explosion(colorNum, x, score, sprite, window, frame, background, textScore, text1, level,
                          levelText, p, pieces, shrinkBlock, xLimL, xLimR);
                // Damage calculation

                for(int i = 0; i < 7; i++)
                    p[i] = pMirror[i]; // Gives back next pieces values
            }
            if(isBomb == false) // If it wasn't a bomb, then declare new pieces.
            {
                for (int i = 0; i < 4; i++)
                {
                    gameGrid[point_1[i][1] - 1][x[i]] = colorNum; // - 1 is there because it was going until 20. Index location is at 19.
                    if(colorNum == 0)
                        gameGrid[point_1[i][1] - 1][x[i]] = 7; // 7 is for Yellow since 0 is for Empty
                }
            }
            dec(); // Declaring blocks in pieces.h
            gridSize(gTime, xLimL, xLimR, yLimU); // The shrink only happens once a piece has fallen.

            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
                x[i] = 4; // Spawns in column 4
                x[i] += point_1[i][0];
                point_1[i][1] += yLimU; // Spawns in row yLimU which is dynamic based on shrunk row
            }
            colorNum = n;
            rCount = 0;
            isBomb = false;
            int rtd = rand() % 100;
            // After that declaration, roll the dice for whether or not to turn it into a bomb again.

            if(rtd >= 40 && rtd < 50) // 7% chance for the bomb to trigger
            {
                for(int i = 0; i < 7; i++)
                    pMirror[i] = p[i]; // Holds next pieces values until detonation

                isBomb = true;
                int column = rand() % 10;       // So 0 to 9 are the options.
                if(yLimU == 0)                  // If grid has not shrunk
                    column = rand() % 10;       // 0 to 9. That's fine.
                else if(yLimU == 1)             // If grid has shrunk once
                {
                    column = rand() % 8;        // 0 to 7. Not fine.
                    column += 1;                // 1 to 8. Now fine.
                }
                else if(yLimU == 2)             // If grid has shrunk twice
                {
                    column = rand() % 6;        // 0 to 5. Not fine.
                    column += 2;                // 2 to 7. Now fine.
                }
                else if(yLimU == 3)             // If grid has shrunk three times (Max)
                {
                    column = rand() % 4;        // 0 to 3. Not fine.
                    column += 3;                // 3 to 6. Now fine.
                }

                for (int i = 0; i < 4; i++)
                {
                    x[i] = column;              // Random column based on code above. It's within the left and right limits
                    point_1[i][1] = yLimU;      // Top row, after accounting for shrinking
                }
            }
        }
        timer = 0;
    }
    else
    {
        delay = levelValues(level, score);
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

// The first block was falling as an individual piece because the full piece was only declared at an anomaly.
// This defines a blueprint to use for that first drop.
void firstBlock(int &colorNum, int &rCount, int x[])
{
    int n = rand() % 7;
    dec();
    for (int i = 0; i < 4; i++)
    {
        point_1[i][0] = BLOCKS[n][i] % 2;
        point_1[i][1] = BLOCKS[n][i] / 2;
        x[i] = 4;
        x[i] += point_1[i][0];
    }
    colorNum = n;
}

// Has a queue 7 pieces long for the upcoming pieces. Used for determining which piece comes next.
// Solves the problem of not knowing in advance what pieces to make.
int nextPieces(int p[])
{
    int temp = p[0];
    for(int i = 0; i < 6; i++)
    {
        temp = p[i];
        p[i] = p[i + 1];
        p[i + 1] = temp;
    }
    // Locations swapped until last. So order goes from 123456 to 234561. And the last is then replaced.
    // Rest of the code will use first location value.
    p[6] = rand() % 7;

    return p[0];
}

// Calculates left and right collision bounds.
// Used for calculating if collision occurs with borders or other grid pieces, and to not let the piece move there if it does occur.
void outerBoundX(int &leftBound, int &rightBound, int x[])
{
    leftBound = x[0];
    rightBound = x[0];
    for(int i = 0; i < 4; i++)
    {
        if(rightBound < x[i])
            rightBound = x[i];
        if(leftBound > x[i])
            leftBound = x[i];
    }
}

// Calculates upper and lower collision bounds.
// Used for calculating if bollision occurs with borders or other grid pieces, and to not let the piece move there if it does occur.
void outerBoundY(int &upBound, int &downBound, int x[])
{
    upBound = point_1[0][1];
    downBound = point_1[0][1];
    for(int i = 0; i < 4; i++)
    {
        if(upBound > point_1[i][1])
            upBound = point_1[i][1];
        if(downBound < point_1[i][1])
            downBound = point_1[i][1];
    }
}

// Used for left and right movement checking and to see whether or not that grid location is empty.
// If it's empty, move there. If not, don't move there.
bool sideCollide(int x[], int a)
{
    for(int k = 0; k < 4; k++)
        if(gameGrid[point_1[k][1]][x[k] + a] != 0) // If the place it wants to move to is not empty
            return true; // Yes, there would be a collision.
    return false;
}

// Checks each row and then the columns of each row to see if it's empty.
// If it's empty then it clears it.
// This was important because this is how points are calculated in the rules of the game.
// The extra arguments are only for the sake of the animation. This function was doable with zero arguments.
void rowClear(int &score, int &xLimL, int &xLimR, sf::Sprite &sprite, sf::RenderWindow &window,
              sf::Sprite frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1, int &level, 
              sf::Text &levelText, int p[], sf::Sprite pieces, sf::Sprite shrinkBlock, int clearedRows[])
{
    sf::Sprite gameGridBlocks;
    sf::Texture obj1;
    obj1.loadFromFile("img/tiles.png");
    gameGridBlocks.setTexture(obj1);

    sf::Clock clock;
    float boxGone = 0;
    int r = 0; // For Score Calculation
    int a = 0;
    int temp = 0;

    int gameGridMirror[M][N] = {};
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            gameGridMirror[i][j] = gameGrid[i][j];

    for (int i = 0; i < M; i++)
    {
        a = 0;
        for (int j = xLimL; j <= xLimR; j++)
            if(gameGrid[i][j] > 0 && gameGrid[i][j] != 8) // So it doesn't count the border
                a++;
        if(a == xLimR - xLimL + 1) // 9-0+1, 8-1+1, 7-2+1, 6-3+1, are 10, 8, 6, 4 columns respectively. It's the limits.
        {
            for (int j = xLimL; j <= xLimR; j++)
            {
                boxGone = 0;
                clock.restart();
                gameGrid[i][j] = 0;
                while(boxGone < 0.03)
                {
                    boxGone = clock.getElapsedTime().asSeconds();

                    window.clear(sf::Color::Black);
                    window.draw(background);
                    
                    for (int i = 0; i < M; i++)
                    {
                        for (int j = 0; j <= 9; j++)
                        {
                            if (gameGrid[i][j] == 0 && gameGridMirror[i][j] != 0)
                            {
                                sf::RectangleShape whiteFlash;
                                whiteFlash.setFillColor(sf::Color::White);
                                whiteFlash.setSize(sf::Vector2f(18.0, 18.0));
                                whiteFlash.setPosition(j * 18, i * 18);
                                whiteFlash.move(28 + 18 * 0, 31);
                                window.draw(whiteFlash);
                                continue;
                            }
                            else if (gameGrid[i][j] == 0 && gameGridMirror[i][j] == 0)
                            {
                                continue;
                            }
                            else if (gameGrid[i][j] == 8)
                            {
                                shrinkBlock.setPosition(j * 18, i * 18);
                                shrinkBlock.move(28 + 18 * 0, 31);
                                window.draw(shrinkBlock);
                            }
                            else
                            {
                                gameGridBlocks.setTextureRect(sf::IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                                gameGridBlocks.setPosition(j * 18, i * 18);
                                gameGridBlocks.move(28 + 18 * 0, 31);
                                window.draw(gameGridBlocks);
                            }
                        }
                    }
                    // This is here so the background isn't drawn over it.

                    int k = 0;
                    if(level == 1 || level == 2)
                        k = 4;
                    else if(level == 3 || level == 4)
                        k = 3;
                    else if(level == 5 || level == 6)
                        k = 2;
                    else
                        k = 1;
                    
                    for(int i = 0; i < k - 1; i++) // It's set to i = 0 here because the change has already happened
                    // So it's not supposed to show the next piece
                    // It's also set to k - 1 because it goes back and redraws pieces in the main function.
                        for(int j = 0; j < 4; j++)
                        {
                            pieces.setTextureRect(sf::IntRect(p[i] * 18, 0, 18, 18));
                            pieces.setPosition(250, 140 + 80 * (i + 1));
                            if(p[i] == 5)
                                pieces.setPosition(250, 140 + 80 * (i + 1) - 10);
                            pieces.move(18 * (BLOCKS[p[i]][j] % 2), 18 * (BLOCKS[p[i]][j] / 2));
                            window.draw(pieces);
                        }
                    window.draw(sprite);
                    window.draw(frame);
                    window.draw(textScore);
                    window.draw(text1);
                    window.draw(levelText);
                    window.display();
                }
                boxGone = 0;
            }
            clearedRows[i] = 1;
            r++;
        }
    }
    // One line: 10 = 10 points per line. Two lines:30 = 15 points per line. Three lines: 60 = 20 points per line
    // Four lines: 100 = 25 points per line
    // Following the patter, 5 lines is 30 per, 6 is 35, 7 is 40, 8 is 45, 9 is 50. 10 is 55. 20 is 105.
    // Score bases would be:
    // 10, 30, 60, 100, 150, 210, 280, 360, 450, 550, 660, 780, 910, 1050, 1200, 1360, 1530, 1710, 1900

    int asdf = 0;
    for(int i = 0; i < 20; i++)
    {
        asdf += (i * 10);
        if(r == i)
        {
            score += (asdf * level);
            break;
        }
        // std::cout << asdf << std::endl;
    }
    // Rubric says "if and only if _more_ than one line destructed". Didn't say anything about 4 being the limit.
    // Four is the max, because of the Line piece. But there's also the shrinking grid to consider.
    // If the time before the shrink is played well you can easily clear more than 15 rows.
}

// If a row is empty, it moves it up until it's no longer there.
// In simpler terms, moves the rest of the grid down.
// This solves the problem of the game never being able to make progress. It lets you continue until you can't.
void rowArrange(int &yLimU, int clearedRows[])
{
    int temp = 0;
    bool rowIsEmpty = false;
    int i = 0;
    for(i = yLimU + 1; i < M; i++)
    {
        if(clearedRows[i] == 1) 
        {
            rowIsEmpty = true;
            break;
        }
    }
    if(rowIsEmpty == true)
    {
        for(int k = i; k > yLimU; k--)
        {
            for(int j = 0; j < N; j++)
            {
                temp = gameGrid[k - 1][j];
                gameGrid[k - 1][j] = gameGrid[k][j];
                gameGrid[k][j] = temp;
            }
            clearedRows[k - 1] = 1;
            clearedRows[k] = 0;
        }
    }
}

// Rotates pieces. The line count is extremely high because the Pivot system was being a hassle to implement.
// Instead, the state of every block in every piece in every rotation state has been predefined.
// The shape rewrites itself into a new shape which happens to be the rotated version.
// Solves the problem of only moving pieces with one shape and not adjusting and solving the puzzle for more points.
void rotate(int x[], int &rCount, int n, int rightBound, int leftBound, int upBound, int downBound, int xLimL, int xLimR)
{
    int changeX[4] = {};
    int changeY[4] = {};

    //////////////////////////////////////////////
    ///////// LETTER Z ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 1) // CW 90. Aka State 2
    {
        changeY[3] -= 2;
        changeX[1] += 2;

        if(rightBound == xLimR)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
    }
    if(rCount % 4 == 2 && n == 1) // CW/CCW 180. Aka State 3
    {
        changeY[3] += 2;
        changeX[1] -= 2;
        if(rightBound < xLimR)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
    }
    if(rCount % 4 == 3 && n == 1) // CW 270 or CCW 90. Aka State 4
    {
        changeY[3] -= 2;
        changeX[1] += 2;
        if(leftBound > xLimL + 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
        changeY[0] += 1;
        changeY[1] += 1;
        changeY[2] += 1;
        changeY[3] += 1;
    }
    if(rCount % 4 == 0 && n == 1)
    {
        changeY[3] += 2;
        changeX[1] -= 2;
        changeY[0] -= 1;
        changeY[1] -= 1;
        changeY[2] -= 1;
        changeY[3] -= 1;
    }

    //////////////////////////////////////////////
    ///////// LETTER S ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 2) // CW 90. Aka State 2
    {
        changeY[0] += 2;
        changeX[3] -= 2;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
    }
    if(rCount % 4 == 2 && n == 2) // CW/CCW 180. Aka State 3
    {

        changeY[0] -= 2;
        changeX[3] += 2;
        if(leftBound > xLimL + 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
    }
    if(rCount % 4 == 3 && n == 2) // CW 270 or CCW 90. Aka State 4
    {
        changeY[0] += 2;
        changeX[3] -= 2;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
        changeY[0] -= 1;
        changeY[1] -= 1;
        changeY[2] -= 1;
        changeY[3] -= 1;
    }
    if(rCount % 4 == 0 && n == 2)
    {
        changeY[0] -= 2;
        changeX[3] += 2;
        changeY[0] += 1;
        changeY[1] += 1;
        changeY[2] += 1;
        changeY[3] += 1;
    }

    //////////////////////////////////////////////
    ///////// LETTER T ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 3) // CW 90 or CCW 270
    {
        changeY[3] -= 1;
        changeX[3] += 1;
        if(rightBound == xLimR)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
    }
    if(rCount % 4 == 2 && n == 3) // CW/CCW 180
    {
        changeY[3] += 1;
        changeX[3] -= 1;
        changeY[1] += 0;
        changeX[1] += 2;
    }
    if(rCount % 4 == 3 && n == 3) // CW 270 or CCW 90
    {
        changeY[1] -= 0;
        changeX[1] -= 2;
        changeY[0] += 1;
        changeX[0] += 1;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
    }
    if(rCount % 4 == 0 && n == 3)
    {
        changeY[0] -= 1;
        changeX[0] -= 1;
    }

    //////////////////////////////////////////////
    ///////// LETTER L ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 4) // CW 90. Aka State 2
    {
        changeY[0] += 0;
        changeX[0] += 2;
        changeY[1] += 1;
        changeX[1] += 1;
        changeY[3] -= 1;
        changeX[3] -= 1;
        if(rightBound == xLimR)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
    }
    if(rCount % 4 == 2 && n == 4) // CW/CCW 180. Aka State 3
    {
        changeY[0] -= 0;
        changeX[0] -= 2;
        changeY[1] -= 1;
        changeX[1] -= 1;
        changeY[3] += 1;
        changeX[3] += 1;
        changeY[0] += 2;
        changeX[0] += 2;

    }
    if(rCount % 4 == 3 && n == 4) // CW 270 or CCW 90. Aka State 4
    {
        changeY[0] -= 2;
        changeX[0] -= 2;
        changeY[0] += 1;
        changeX[0] += 0;
        changeY[1] += 1;
        changeX[1] += 1;
        changeY[3] += 0;
        changeX[3] -= 1;

        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
    }
    if(rCount % 4 == 0 && n == 4)
    {
        changeY[0] -= 1;
        changeX[0] -= 0;
        changeY[1] -= 1;
        changeX[1] -= 1;
        changeY[3] -= 0;
        changeX[3] += 1;
    }

    //////////////////////////////////////////////
    ///////// LETTER I ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 5) // CW 90
    {
        changeY[0] += 2;
        changeX[0] -= 1;
        changeY[1] += 1;
        changeX[1] += 1;
        changeY[3] -= 1;
        changeX[3] += 2;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
        if(rightBound == xLimR - 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
        if(rightBound == xLimR)
        {
            changeX[0] -= 2;
            changeX[1] -= 2;
            changeX[2] -= 2;
            changeX[3] -= 2;
        }
    }
    if(rCount % 4 == 2 && n == 5) // CW/CCW 180
    {
        changeY[0] -= 2;
        changeX[0] += 1;
        changeY[1] -= 1;
        changeX[1] -= 1;
        changeY[3] += 1;
        changeX[3] -= 2;
        changeX[0] += 1;
        changeX[1] += 1;
        changeX[2] += 1;
        changeX[3] += 1;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
        if(rightBound == xLimR - 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
        if(rightBound == xLimR)
        {
            changeX[0] -= 2;
            changeX[1] -= 2;
            changeX[2] -= 2;
            changeX[3] -= 2;
        }
    }
    if(rCount % 4 == 3 && n == 5) // CW 270 or CCW 90
    {

        changeX[0] -= 1;
        changeX[1] -= 1;
        changeX[2] -= 1;
        changeX[3] -= 1;
        changeY[0] += 2;
        changeX[0] -= 1;
        changeY[1] += 1;
        changeX[1] += 1;
        changeY[3] -= 1;
        changeX[3] += 2;
        changeY[0] -= 1;
        changeY[1] -= 1;
        changeY[2] -= 1;
        changeY[3] -= 1;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
        if(rightBound == xLimR - 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
        if(rightBound == xLimR)
        {
            changeX[0] -= 2;
            changeX[1] -= 2;
            changeX[2] -= 2;
            changeX[3] -= 2;
        }
    }
    if(rCount % 4 == 0 && n == 5)
    {
        changeY[0] += 1;
        changeY[1] += 1;
        changeY[2] += 1;
        changeY[3] += 1;
        changeY[0] -= 2;
        changeX[0] += 1;
        changeY[1] -= 1;
        changeX[1] -= 1;
        changeY[3] += 1;
        changeX[3] -= 2;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
        if(rightBound == xLimR - 1)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
        if(rightBound == xLimR)
        {
            changeX[0] -= 2;
            changeX[1] -= 2;
            changeX[2] -= 2;
            changeX[3] -= 2;
        }
    }

    //////////////////////////////////////////////
    ///////// LETTER J ///////////////////////////
    //////////////////////////////////////////////

    if(rCount % 4 == 1 && n == 6) // CW 90. Aka State 2
    {
        changeY[0] += 0;
        changeX[0] -= 1;
        changeY[2] -= 1;
        changeX[2] += 0;
        changeY[3] -= 1;
        changeX[3] += 1;
        if(rightBound == xLimR)
        {
            changeX[0] -= 1;
            changeX[1] -= 1;
            changeX[2] -= 1;
            changeX[3] -= 1;
        }
    }
    if(rCount % 4 == 2 && n == 6) // CW/CCW 180. Aka State 3
    {
        changeY[0] -= 0;
        changeX[0] += 1;
        changeY[2] += 1;
        changeX[2] -= 0;
        changeY[3] += 1;
        changeX[3] -= 1;
        changeY[2] -= 2;
        changeX[2] += 2;

    }
    if(rCount % 4 == 3 && n == 6) // CW 270 or CCW 90. Aka State 4
    {
        changeY[2] += 2;
        changeX[2] -= 2;
        changeY[0] += 1;
        changeX[0] -= 1;
        changeY[2] -= 1;
        changeX[2] += 2;
        changeY[3] += 0;
        changeX[3] += 1;
        if(leftBound == xLimL)
        {
            changeX[0] += 1;
            changeX[1] += 1;
            changeX[2] += 1;
            changeX[3] += 1;
        }
    }
    if(rCount % 4 == 0 && n == 6)
    {
        changeY[0] -= 1;
        changeX[0] += 1;
        changeY[2] += 1;
        changeX[2] -= 2;
        changeY[3] -= 0;
        changeX[3] -= 1;
    }
    bool allowRotation = true;
    for(int i = 0; i < 4; i++)
    {
        if(gameGrid[point_1[i][1] + changeY[i]][x[i] + changeX[i]] != 0 || x[i] + changeX[i] < xLimL || x[i] + changeX[i] > xLimR)
        {
            allowRotation = false;
            break;
        }
    }
    if(allowRotation == true)
    {
        for(int i = 0; i < 4; i++)
        {
            x[i] += changeX[i];
            point_1[i][1] += changeY[i];
        }
    }
}

// Projects a Shadow to where the block would land.
// Also used to find distance to move the piece if a Hard Drop (Space Press) is done.
// Solves the problem of not knowing where a piece might land because of the large distance between it and the place where it might land.
void shadow(int x[], int shadowX[], int shadowY[], int &teleDistance)
{
    int temp = 0;
    int distance[4] = {};
    for(int i = 0; i < 4; i++)
    {
        for(distance[i] = 0; distance[i] < M; distance[i]++)
        {
            temp = point_1[i][1] + distance[i] + 1;
            if(gameGrid[temp][x[i]] > 0 || point_1[i][1] + distance[i] == 19) // If the grid location isn't empty then break
                break;
            // Otherwise, increase distance.
        } // Repeat for all 4 blocks
    }
    int lowestDistance = distance[0];
    for(int i = 0; i < 4; i++)
        if (lowestDistance > distance[i])
            lowestDistance = distance[i];

    for(int i = 0; i < 4; i++)
    {
        shadowX[i] = x[i];
        shadowY[i] = point_1[i][1];
        shadowY[i] += lowestDistance;
    }

    teleDistance = lowestDistance;
}

// Detonation of Bomb and which pieces to clear.
// The extra arguments are for the sake of animation.
// Solves the problem of the falling bomb not clearing pieces.
void explosion(int &colorNum, int x[], int &score, sf::Sprite &sprite, sf::RenderWindow &window,
              sf::Sprite frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1, int &level, 
              sf::Text &levelText, int p[], sf::Sprite &pieces, sf::Sprite &shrinkBlock, int &xLimL, int &xLimR)
{
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("audio/kaboom.ogg");
    sound.setBuffer(buffer);
    sf::Clock clock;
    float bombTime = 0;
    sound.play();
    while(bombTime < 2)
        bombTime = clock.getElapsedTime().asSeconds();
    bombTime = 0;

    sf::Sprite gameGridBlocks;
    sf::Texture obj1;
    obj1.loadFromFile("img/tiles.png");
    gameGridBlocks.setTexture(obj1);

    float boxGone = 0;
    int gameGridMirror[M][N] = {};
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            gameGridMirror[i][j] = gameGrid[i][j];

    if(point_1[0][1] != 20) // This check is done first to make sure an index isn't referenced that doesn't exist.
    {
        if(gameGrid[point_1[0][1] + 0][x[0]] == colorNum || (gameGrid[point_1[0][1] + 0][x[0]] == 7 && colorNum == 0)) 
        // If the bomb color matches the block it falls on
        {
            for(int i = 0; i < M; i++)
                for(int j = 0; j < N; j++)
                    gameGrid[i][j] = 0;
            
            score += 100; // 100 points added to score if colors match
        }
    }
    
    if(gameGrid[point_1[0][1] + 0][x[0]] != colorNum && gameGrid[point_1[0][1] + 0][x[0]] != 0)
    {
        if(x[0] >= 5 && point_1[0][1] <= 18) // So between 5 and 9
        {
            gameGrid[point_1[0][1] + 0][x[0] - 0] = 0; // The block it lands on
            gameGrid[point_1[0][1] + 0][x[0] - 1] = 0; // Left of the block it lands on
            gameGrid[point_1[0][1] + 1][x[0] - 0] = 0; // The block below the one it lands on
            gameGrid[point_1[0][1] + 1][x[0] - 1] = 0; // Left of the block below the one it lands on
        }
        else if(x[0] < 5 && point_1[0][1] <= 18)
        {
            gameGrid[point_1[0][1] + 0][x[0] + 0] = 0; // The block it lands on
            gameGrid[point_1[0][1] + 0][x[0] + 1] = 0; // Right of the block it lands on
            gameGrid[point_1[0][1] + 1][x[0] + 0] = 0; // The block below the one it lands on
            gameGrid[point_1[0][1] + 1][x[0] + 1] = 0; // Right of the block below the one it lands on
        }
        else if(x[0] >= 5 && point_1[0][1] == 19)
        {
            gameGrid[point_1[0][1] + 0][x[0] - 0] = 0; // The block it lands on
            gameGrid[point_1[0][1] + 0][x[0] - 1] = 0; // Left of the block it lands on
        }
        else if(x[0] < 5 && point_1[0][1] == 19)
        {
            gameGrid[point_1[0][1] + 0][x[0] + 0] = 0; // The block it lands on
            gameGrid[point_1[0][1] + 0][x[0] + 1] = 0; // Right of the block it lands on
        }
        // If it's 20 then it's just the last row. Nothing happens.
    }

    for(int i = 0; i < M; i++)
        for (int j = xLimL; j <= xLimR; j++)
            if(gameGrid[i][j] == 0 && gameGridMirror [i][j] != 0)
            {
                boxGone = 0;
                clock.restart();
                gameGrid[i][j] = 0;
                while(boxGone < 0.06)
                {
                    boxGone = clock.getElapsedTime().asSeconds();
            
                    window.clear(sf::Color::Black);
                    window.draw(background);
                    
                    for (int i = 0; i < M; i++)
                    {
                        for (int j = 0; j <= 9; j++)
                        {
                            if (gameGrid[i][j] == 0 && gameGridMirror[i][j] != 0)
                            {
                                sf::RectangleShape whiteFlash;
                                whiteFlash.setFillColor(sf::Color::White);
                                whiteFlash.setSize(sf::Vector2f(18.0, 18.0));
                                whiteFlash.setPosition(j * 18, i * 18);
                                whiteFlash.move(28 + 18 * 0, 31);
                                window.draw(whiteFlash);
                                continue;
                            }
                            else if (gameGrid[i][j] == 0 && gameGridMirror[i][j] == 0)
                            {
                                continue;
                            }
                            else if (gameGrid[i][j] == 8)
                            {
                                shrinkBlock.setPosition(j * 18, i * 18);
                                shrinkBlock.move(28 + 18 * 0, 31);
                                window.draw(shrinkBlock);
                            }
                            else
                            {
                                gameGridBlocks.setTextureRect(sf::IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                                gameGridBlocks.setPosition(j * 18, i * 18);
                                gameGridBlocks.move(28 + 18 * 0, 31);
                                window.draw(gameGridBlocks);
                            }
                        }
                    }
                    // This is here so the background isn't drawn over it.
                    int k = 0;
                    if(level == 1 || level == 2)
                        k = 4;
                    else if(level == 3 || level == 4)
                        k = 3;
                    else if(level == 5 || level == 6)
                        k = 2;
                    else
                        k = 1;
                    
                    for(int i = 0; i < k - 1; i++) // It's set to i = 0 here because the change has already happened
                    // So it's not supposed to show the next piece
                    // It's also set to k - 1 because it goes back and redraws pieces in the main function.
                        for(int j = 0; j < 4; j++)
                        {
                            pieces.setTextureRect(sf::IntRect(p[i] * 18, 0, 18, 18));
                            pieces.setPosition(250, 140 + 80 * (i + 1));
                            if(p[i] == 5)
                                pieces.setPosition(250, 140 + 80 * (i + 1) - 10);
                            pieces.move(18 * (BLOCKS[p[i]][j] % 2), 18 * (BLOCKS[p[i]][j] / 2));
                            window.draw(pieces);
                        }
                    window.draw(sprite);
                    window.draw(frame);
                    window.draw(textScore);
                    window.draw(text1);
                    window.draw(levelText);
                    window.display();

                }
                boxGone = 0;
            }
}

// Shrinks grid depending on time. Changing the first line lets the entire preset be changed. By default: 60.
// Solves the problem of the grid size not shrinking and hence making the game feel too easy.
void gridSize(float &gTime, int &xLimL, int &xLimR, int &yLimU)
{
    int a = 60;
    if(gTime > a && gTime < a * 2) // One shrink. Happens at 1 Minutes.
    {
        xLimL = 1; // From 0
        xLimR = 8; // From 9
        yLimU = 1; // From 0
        for(int i = 0; i < M; i++)
        {
            gameGrid[i][0] = 8;
            gameGrid[i][9] = 8;
        }
        for(int j = 0; j < N; j++)
        {
            gameGrid[0][j] = 8;
        }
    }
    if(gTime > a * 2 && gTime < a * 3) // Two shrinks. Happens at 2 Minutes.
    {
        xLimL = 2; // From 1
        xLimR = 7; // From 8
        yLimU = 2; // From 1
        for(int i = 0; i < M; i++)
        {
            gameGrid[i][0] = 8;
            gameGrid[i][9] = 8;
            gameGrid[i][1] = 8;
            gameGrid[i][8] = 8;
        }
        for(int j = 0; j < N; j++)
        {
            gameGrid[0][j] = 8;
            gameGrid[1][j] = 8;
        }
    }
    if(gTime > a * 3) // Three shrinks. Last one. Happens at 3 minutes.
    {
        xLimL = 3; // From 2
        xLimR = 6; // From 7
        yLimU = 3; // From 2
        for(int i = 0; i < M; i++)
        {
            gameGrid[i][0] = 8;
            gameGrid[i][9] = 8;
            gameGrid[i][1] = 8;
            gameGrid[i][8] = 8;
            gameGrid[i][2] = 8;
            gameGrid[i][7] = 8;
        }
        for(int j = 0; j < N; j++)
        {
            gameGrid[0][j] = 8;
            gameGrid[1][j] = 8;
            gameGrid[2][j] = 8;
        }
    }
}

// Used to convert the score from integer to string so it can be output via SFML, as SFML text outputs require strings.
// In simpler terms: Turns 500 into "500" so it can be shown on the screen.
// Solves the problem of the score not being in a data type that can be shown on screen via SFML.
void scoreInString(int &score, sf::Text &textScore)
{
    char a[10] = {};
    int digit = 0;
    for(int i = 5; i >= 0; i--) // Max value of an int is billion, so 10 positions.
    {
        digit = 0;
        digit = score / pow(10, (5 - i));
        digit = digit % 10;
        digit += 48;
        a[i] = char(digit);
    }
    std::string b = a;
    textScore.setString(b);
}

// Same functionality as scoreInString except with an std::string return data type.
// scoreInString was not edited so the already existing code was not affected.
std::string scoreInStringFile(int score) // This was declared later for the file handling strings.
{
    char a[10] = {};
    int digit = 0;
    for(int i = 5; i >= 0; i--) // Max value of an int is billion, so 10 positions.
    {
        digit = 0;
        digit = score / pow(10, (5 - i));
        digit = digit % 10;
        digit += 48;
        a[i] = char(digit);
    }
    return a;
}

// Adjusts game difficulty based on level. Level is based on score.
// Min level is 1, Max is 8. A new level is achieved every 200 points.
// Set to float return type so it can be used in fallingPiece for the falling speed.
// Solves the problem of the game feeling the same and not making you try harder over time.
float levelValues(int &level, int &score)
{
    int a = score / 200;
    // 8 Levels. Goes down to delay = 0.1, and can't go down further than that.
    float delay = 0;

    if(a == 0)          // Level 1
        delay = 0.8;    
    else if(a == 1)     // Level 2
        delay = 0.7;
    else if(a == 2)     // Level 3
        delay = 0.6;
    else if(a == 3)     // Level 4
        delay = 0.5;
    else if(a == 4)     // Level 5
        delay = 0.4;
    else if(a == 5)     // Level 6
        delay = 0.3;
    else if(a == 6)     // Level 7
        delay = 0.2;

    level = a + 1;
    if(a >= 7)     // Level 8
    {
        delay = 0.1;
        level = 8;
    }
    return delay;
}

// Animation when new game starts where the blocks are all there then become empty.
// Unfortunately there was no simple way to make sure the spawned blocks were actual Tetris shapes.
// Solves the problem of....extra appeal and style?
// If I find out how to do that in the future, I'll edit it.
void shapeBreak(int &score, int &xLimL, int &xLimR, sf::Sprite &sprite, sf::RenderWindow &window,
              sf::Sprite frame, sf::Sprite &background, sf::Text &textScore, sf::Text &text1, int &level, 
              sf::Text &levelText, int p[], sf::Sprite pieces, sf::Sprite shrinkBlock, int clearedRows[])
{
    int b = 0;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            b = rand() % 7;
            if(b == 0)
                b = 7;
            gameGrid[i][j] = b;
        }
    }
    sf::Sprite gameGridBlocks;
    sf::Texture obj1;
    obj1.loadFromFile("img/tiles.png");
    gameGridBlocks.setTexture(obj1);

    sf::Clock clock;
    float boxGone = 0;
    int r = 0; // For Score Calculation
    int a = 0;
    int temp = 0;

    int gameGridMirror[M][N] = {};
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            gameGridMirror[i][j] = gameGrid[i][j];

    for (int i = 0; i < M; i++)
    {
        a = 0;
        for (int j = xLimL; j <= xLimR; j++)
            if(gameGrid[i][j] > 0 && gameGrid[i][j] != 8) // So it doesn't count the border
                a++;
        if(a == xLimR - xLimL + 1) // 9-0+1, 8-1+1, 7-2+1, 6-3+1, are 10, 8, 6, 4 columns respectively. It's the limits.
        {
            for (int j = xLimL; j <= xLimR; j++)
            {
                boxGone = 0;
                clock.restart();
                gameGrid[i][j] = 0;
                while(boxGone < 0.01)
                {
                    boxGone = clock.getElapsedTime().asSeconds();

                    window.clear(sf::Color::Black);
                    window.draw(background);
                    
                    for (int i = 0; i < M; i++)
                    {
                        for (int j = 0; j <= 9; j++)
                        {
                            if (gameGrid[i][j] == 0 && gameGridMirror[i][j] != 0)
                            {
                                sf::RectangleShape whiteFlash;
                                whiteFlash.setFillColor(sf::Color::White);
                                whiteFlash.setSize(sf::Vector2f(18.0, 18.0));
                                whiteFlash.setPosition(j * 18, i * 18);
                                whiteFlash.move(28 + 18 * 0, 31);
                                window.draw(whiteFlash);
                                continue;
                            }
                            else if (gameGrid[i][j] == 0 && gameGridMirror[i][j] == 0)
                            {
                                continue;
                            }
                            else
                            {
                                gameGridBlocks.setTextureRect(sf::IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                                gameGridBlocks.setPosition(j * 18, i * 18);
                                gameGridBlocks.move(28 + 18 * 0, 31);
                                window.draw(gameGridBlocks);
                            }
                        }
                    }

                    window.draw(frame);
                    window.draw(textScore);
                    window.draw(text1);
                    window.draw(levelText);
                    window.display();
                }
                boxGone = 0;
            }
            clearedRows[i] = 1;
            r++;
        }
    }
}

// Pause menu. Triggered when 'H' is pressed on the keyboard.
// Has the most arguments because practically every GUI element had to be passed through from main() so it could be redrawn.
// Solves the problem of being unable to pause the game or do other things during gameplay.
void pause(sf::Event &ev, sf::Event &ev2, sf::RenderWindow &window, sf::Text &resume, sf::Text &hiScore, int &bg, sf::Text &changeBG, 
      sf::Text &exit, sf::RectangleShape &menuOption, sf::Sprite &background, sf::Text &restart,
      int &option, int &option2, int &selection, int &selection2, sf::Texture &obj2,
      int &score, int &level, float &time, float &timer, float &gTime, sf::Clock &globalTime,
      int &xLimL, int &xLimR, int &yLimU, bool &first, sf::Text &scoreList, sf::Text &help)
{
    selection = 0;
    while(selection != 1)
    {
        selection2 = 0;
        window.clear(sf::Color::Black);
        resume.setPosition(40, 100);
        restart.setPosition(40,150);
        hiScore.setPosition(40,200);
        changeBG.setPosition(40,250);
        help.setPosition(40, 300);
        exit.setPosition(40, 350);
        resume.setString("Resume");
        restart.setString("Restart");
        hiScore.setString("High Scores");
        changeBG.setString("Change Background");
        exit.setString("Exit");
        if(option == 1)
            menuOption.setPosition(30,95);
        else if(option == 2)
            menuOption.setPosition(30,145);
        else if(option == 3)
            menuOption.setPosition(30,195);
        else if(option == 4)
            menuOption.setPosition(30,245);
        else if(option == 5)
            menuOption.setPosition(30,295);
        else if(option == 6)
            menuOption.setPosition(30,345);
        window.draw(background);
        window.draw(resume);
        window.draw(restart);
        window.draw(hiScore);
        window.draw(changeBG);
        window.draw(help);
        window.draw(exit);
        window.draw(menuOption);
        window.display();
        while(window.pollEvent(ev))
        {    
            if (ev.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            if (ev.type == sf::Event::KeyReleased)
            {
                if (ev.key.code == sf::Keyboard::Up)
                {
                    option -= 1;
                    if(option == 0)
                        option = 6;
                }
                    
                if(ev.key.code == sf::Keyboard::Down)
                {    
                    option += 1;
                    if(option == 7)
                        option = 1;
                }

                if(ev.key.code == sf::Keyboard::Enter)
                {
                    selection = option;
                    if(option == 4)
                    while(selection2 != 3)
                    {
                        selection2 = 0;
                        window.clear();
                        changeBG.setPosition(40,150);
                        // Reusing the previous sf::Text stuff
                        resume.setString("Previous");
                        resume.setPosition(40,200);
                        hiScore.setString("Next");
                        hiScore.setPosition(40,250);
                        exit.setString("Main Menu");
                        exit.setPosition(40,300);
                        if(option2 == 1)
                            menuOption.setPosition(30,195);
                        else if(option2 == 2)
                            menuOption.setPosition(30,245);
                        else if(option2 == 3)
                            menuOption.setPosition(30,295);
                        while(window.pollEvent(ev2))
                        {    
                            if (ev2.type == sf::Event::Closed)
                            {
                                window.close();
                                return;
                            }
                            if (ev2.type == sf::Event::KeyReleased)
                            {
                                if (ev2.key.code == sf::Keyboard::Up)
                                {
                                    option2 -= 1;
                                    if(option2 == 0)
                                        option2 = 3;
                                }
                                    
                                if(ev2.key.code == sf::Keyboard::Down)
                                {    
                                    option2 += 1;
                                    if(option2 == 4)
                                        option2 = 1;
                                }
                                if(ev2.key.code == sf::Keyboard::Enter)
                                {
                                    selection2 = option2;
                                    if(selection2 == 1)
                                    {
                                        bg--;
                                        if(bg == 0)
                                            bg = 5;
                                    }
                                    if(selection2 == 2)
                                    {
                                        bg++;
                                        if(bg == 6)
                                            bg = 1;
                                    }
                                }
                            }
                        }
                        if(bg == 1)
                            obj2.loadFromFile("img/bg1.png");
                        if(bg == 2)
                            obj2.loadFromFile("img/bg2.png");
                        if(bg == 3)
                            obj2.loadFromFile("img/bg3.png");
                        if(bg == 4)
                            obj2.loadFromFile("img/bg4.png");
                        if(bg == 5)
                            obj2.loadFromFile("img/bg5.png");
                        background.setTexture(obj2);
                        window.draw(background);
                        window.draw(resume);
                        window.draw(exit);
                        window.draw(hiScore);
                        window.draw(changeBG);
                        window.draw(menuOption);
                        window.display();
                    }
                    else if(option == 3)
                    {
                        while(selection2 != 1)
                        {
                            selection2 = 0;
                            window.clear();
                            exit.setString("Main Menu");
                            exit.setPosition(30, 340);
                            menuOption.setPosition(20, 335);
                            window.draw(background);
                            window.draw(exit);
                            window.draw(menuOption);
                            window.draw(scoreList);
                            window.display();
                            while(window.pollEvent(ev2))
                            {    
                                if (ev2.type == sf::Event::Closed)
                                {
                                    return;
                                }
                                if (ev2.type == sf::Event::KeyReleased)
                                {
                                    if(ev2.key.code == sf::Keyboard::Enter)
                                    {
                                        selection2 = 1;
                                    }
                                }
                            }
                        }
                    }
                    else if(option == 5)
                    {
                        obj2.loadFromFile("img/help.png");
                        background.setTexture(obj2);
                        while(selection2 != 1)
                        {
                            selection2 = 0;
                            window.clear();
                            window.draw(background);
                            window.display();
                            while(window.pollEvent(ev2))
                            {    
                                if (ev2.type == sf::Event::Closed)
                                {
                                    return;
                                }
                                if (ev2.type == sf::Event::KeyReleased)
                                {
                                    if(ev2.key.code == sf::Keyboard::Enter)
                                    {
                                        selection2 = 1;
                                    }
                                }
                            }
                        }
                        if(bg == 1)
                            obj2.loadFromFile("img/bg1.png");
                        if(bg == 2)
                            obj2.loadFromFile("img/bg2.png");
                        if(bg == 3)
                            obj2.loadFromFile("img/bg3.png");
                        if(bg == 4)
                            obj2.loadFromFile("img/bg4.png");
                        if(bg == 5)
                            obj2.loadFromFile("img/bg5.png");
                    }
                    else if(option == 6)
                    {
                        window.close();
                        return;
                    }
                    else if(option == 2)
                    {
                        for(int i = 0; i < M; i++)
                        {
                            for(int j = 0; j < N; j++)
                            {
                                gameGrid[i][j] = 0;
                            }
                        }
                        level = 1;
                        score = 0;
                        time = 0;
                        timer = 0;
                        gTime = 0;
                        selection = 1;
                        globalTime.restart();
                        xLimL = 0;
                        xLimR = 9;
                        yLimU = 0;
                        first = false;
                        return;
                    }
                }
            }
        }
    }
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
