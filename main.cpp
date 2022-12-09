/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

// Name: Muhammad Ibrahim Awais
// Student ID: 22i-0878
// Assignment: PF Semester Project

#include <string>
#include <fstream> // For file handling
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    // Found this on the SFML docs. Stretches the window as if it's being resized.
    // Could be useful for a menu.
    window.setSize(sf::Vector2u(320*2, 480*2));
    Texture obj1, obj2, obj3;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/bg2.png");
    obj3.loadFromFile("img/frame.png");
    Sprite sprite(obj1), background(obj2), frame(obj3);

    int colorNum = 1;
    float timer = 0, delay = 0.8;
    Clock clock;

    // Main functions of Tetris and Rotation
    bool first = true; // First Piece
    int leftBound = 0; // Left most x coordinate of all 4 blocks
    int rightBound = 0; // Right most x coordinate of all 4 blocks
    int upBound = 0; // Uppermost y coordinate of all 4 blocks
    int downBound = 0; // Lowest y coordinate of all 4 blocks
    int rCount = 0; // Number of rotations to apply
    int x[4] = {4, 4, 4, 4}; // Used for Movement Left and Right

    // Shadow
    int shadowX[4] = {}; // Shadow X coordinates (Declared so fallingPiece not affected)
    int shadowY[4] = {}; // Shadow Y coordinates
    RectangleShape shadowBlock(Vector2f(18, 18)); // Shadow looks
    shadowBlock.setFillColor(Color::Transparent);
    shadowBlock.setOutlineThickness(1.5);
    shadowBlock.setOutlineColor(Color::White);

    // Pressing space to move instantly
    int teleDistance = 0;

    // Bomb
    bool isBomb = false;
    Texture bomba;
    bomba.loadFromFile("img/bomba4.png");
    Texture bombWhite;
    bombWhite.loadFromFile("img/bombWhite.png");
    // There's no sprite for the bomb because instead of making another one,
    // I turned fallingPiece into a bomb. That is not an exaggeration it _turns_ into a bomb.

    // Background Music
    Music bgMusic;
    bgMusic.openFromFile("audio/repeatedStage.ogg");
    bgMusic.setVolume(25);
    bgMusic.setLoop(true); // Loops music. I had to edit in Audacity to make sure it was a perfect loop
    bgMusic.play();

    // Shrinking Grid
    // Also used the opportunity to make a clock
    Clock globalTime; // Tracks overall time played
    float gTime = 0;  // Also tracks overall time played
    int xLimL = 0; // Limit on Left Side for X values in start
    int xLimR = 9; // Limit on Right Side for X values in start
    int yLimU = 0; // Limit for uppermost area for Y values in start
    // I'm borrowing an idea from another game: Mega Bomberman. It put unremovable blocks when the area shrinked.
    Sprite shrinkBlock; // Block to put at border
    Texture border;
    border.loadFromFile("img/border.png");
    shrinkBlock.setTexture(border);

    // Game Over
    Text gameOver;
    Font pixelFont;
    gameOver.setString("Game Over");
    pixelFont.loadFromFile("misc/VCR_OSD_MONO_1.001.ttf");
    // gameOver text looks
    gameOver.setFont(pixelFont);
    gameOver.setCharacterSize(24);
    gameOver.setFillColor(sf::Color::White);
    gameOver.setPosition(100,201);
    gameOver.setOutlineColor(sf::Color::Black);
    gameOver.setOutlineThickness(1);

    // Score
    int score = 0;
    // The next code is for outputting only. Only the int is used for calculation
    Text text1;
    text1.setString("Score: ");
    text1.setFont(pixelFont);
    text1.setCharacterSize(18);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(234,140);
    text1.setOutlineColor(sf::Color::Black);
    text1.setOutlineThickness(1);
    Text textScore;
    textScore.setFont(pixelFont);
    textScore.setCharacterSize(18);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(234,170);
    textScore.setOutlineColor(sf::Color::Black);
    textScore.setOutlineThickness(1);

    // Levels
    int level = 1;
    // Outputting Level Number to screen
    Text levelText;
    levelText.setFont(pixelFont);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(234,110);
    levelText.setOutlineColor(sf::Color::Black);
    levelText.setOutlineThickness(1);
    std::string l;

    // Next Pieces (Yes I did it later because I didn't understand it before)
    int p[7] = {};
    for(int i = 0; i < 7; i++)
        p[i] = rand() % 7;
    int pMirror[7] = {};
    // This exists solely because the bomb would mess up the queue
    // Now it's correct. And there's a 7% chance for the next piece to turn into a bomb.
    Sprite pieces;
    pieces.setTexture(obj1);

    // Outputting global time
    Text theTime;
    theTime.setFont(pixelFont);
    theTime.setCharacterSize(24);
    theTime.setFillColor(sf::Color::White);
    theTime.setPosition(240,440);
    theTime.setOutlineColor(sf::Color::Black);
    theTime.setOutlineThickness(1);
    std::string t;
    // This was done because each digit had to be handled separately. int to string is a hassle.
    int m1 = 0, m2 = 0, s1 = 0, s2 = 0;

    // Menu options and looks
    Text resume, restart, hiScore, changeBG, exit, help;
    resume.setFont(pixelFont);
    resume.setCharacterSize(24);
    resume.setFillColor(sf::Color::White);
    resume.setOutlineColor(sf::Color::Black);
    resume.setOutlineThickness(1);
    restart.setFont(pixelFont);
    restart.setCharacterSize(24);
    restart.setFillColor(sf::Color::White);
    restart.setOutlineColor(sf::Color::Black);
    restart.setOutlineThickness(1);
    hiScore.setFont(pixelFont);
    hiScore.setCharacterSize(24);
    hiScore.setFillColor(sf::Color::White);
    hiScore.setOutlineColor(sf::Color::Black);
    hiScore.setOutlineThickness(1);
    changeBG.setFont(pixelFont);
    changeBG.setCharacterSize(24);
    changeBG.setFillColor(sf::Color::White);
    changeBG.setOutlineColor(sf::Color::Black);
    changeBG.setOutlineThickness(1);
    exit.setFont(pixelFont);
    exit.setCharacterSize(24);
    exit.setFillColor(sf::Color::White);
    exit.setOutlineColor(sf::Color::Black);
    exit.setOutlineThickness(1);
    help.setFont(pixelFont);
    help.setCharacterSize(24);
    help.setFillColor(sf::Color::White);
    help.setOutlineColor(sf::Color::Black);
    help.setOutlineThickness(1);
    help.setString("Help");
    RectangleShape menuOption;
    menuOption.setFillColor(Color::Transparent);
    menuOption.setOutlineColor(Color::White);
    menuOption.setOutlineThickness(4);
    menuOption.setSize(Vector2f(260,40));
    // option2 and selection2 exist for sub-menus of Hi Scores and Change Background
    int option = 1;
    int option2 = 1;
    int selection = 0;
    int selection2 = 0;
    int bg = 2;

    // File handling for scores
    std::fstream theScores;
    int rowsInTxtFile = 0;
    std::string name[10];
    std::string enteredName;
    int highScore[10];
    theScores.open("misc/hiscores.txt"); // ios::out means we're reading from
    for(int i = 0; i < 10; i++)
    {
        theScores >> name[i];
        theScores >> highScore[i];
    }
    theScores.close();
    Text scoreList;
    scoreList.setFont(pixelFont);
    scoreList.setCharacterSize(20);
    scoreList.setFillColor(sf::Color::White);
    scoreList.setOutlineColor(sf::Color::Black);
    scoreList.setOutlineThickness(1);
    scoreList.setPosition(20,20);
    std::string dataInFile;
    for(int i = 0; i < 10; i++)
    {
        dataInFile += name[i];
        dataInFile += " ";
        dataInFile += scoreInStringFile(highScore[i]);
        dataInFile += "\n";
    }
    scoreList.setString(dataInFile);

    int clearedRows[M] = {}; // Used for Clearing Rows
    // Was originally declared globally under utils.h and now it's here.

    while (window.isOpen())
    {
        // std::cout << gTime << std::endl;
        Event ev;
        Event ev2;
        // Main Menu
        while(selection != 1)
        {
            selection2 = 0;
            window.clear(sf::Color::Black);
            resume.setPosition(40, 150);
            // restart.setPosition(50,150);
            hiScore.setPosition(40,200);
            changeBG.setPosition(40,250);
            help.setPosition(40,300);
            exit.setPosition(40, 350);
            resume.setString("Begin");
            // restart.setString("Restart");
            hiScore.setString("High Scores");
            changeBG.setString("Change Background");
            exit.setString("Exit");
            if(option == 1)
                menuOption.setPosition(30,145);
            else if(option == 2)
                menuOption.setPosition(30,195);
            else if(option == 3)
                menuOption.setPosition(30,245);
            else if(option == 4)
                menuOption.setPosition(30,295);
            else if(option == 5)
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
                if (ev.type == Event::Closed)
                {
                    return 0;
                }
                if (ev.type == Event::KeyReleased)
                {
                    if (ev.key.code == Keyboard::Up)
                    {
                        option -= 1;
                        if(option == 0)
                            option = 5;
                    }
                        
                    if(ev.key.code == Keyboard::Down)
                    {    
                        option += 1;
                        if(option == 6)
                            option = 1;
                    }

                    if(ev.key.code == Keyboard::Enter)
                    {
                        selection = option;
                        if(option == 3)
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
                                if (ev2.type == Event::Closed)
                                {
                                    return 0;
                                }
                                if (ev2.type == Event::KeyReleased)
                                {
                                    if (ev2.key.code == Keyboard::Up)
                                    {
                                        option2 -= 1;
                                        if(option2 == 0)
                                            option2 = 3;
                                    }
                                        
                                    if(ev2.key.code == Keyboard::Down)
                                    {    
                                        option2 += 1;
                                        if(option2 == 4)
                                            option2 = 1;
                                    }
                                    if(ev2.key.code == Keyboard::Enter)
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
                        else if(option == 2)
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
                                    if (ev2.type == Event::Closed)
                                    {
                                        return 0;
                                    }
                                    if (ev2.type == Event::KeyReleased)
                                    {
                                        if(ev2.key.code == Keyboard::Enter)
                                        {
                                            selection2 = 1;
                                        }
                                    }
                                }
                            }
                        }
                        else if(option == 4)
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
                                    if (ev2.type == Event::Closed)
                                    {
                                        return 0;
                                    }
                                    if (ev2.type == Event::KeyReleased)
                                    {
                                        if(ev2.key.code == Keyboard::Enter)
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
                        else if(option == 5)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        sprite.setColor(Color::White);

        gTime = globalTime.getElapsedTime().asSeconds();

        l = "Level ";
        l = l + char(level + 48);
        levelText.setString(l);

        delay = levelValues(level, score);

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                  
            if (e.type == Event::Closed)
                return 0; // I found that the window.close() command can still keep the game running
                // even when the window is closed. This however, stops the program entirely.
            if (e.type == Event::KeyPressed && isBomb == false)
            // isBomb check is there so bomb can't be edited with keyboard inputs.
            {
                if (e.key.code == Keyboard::Right && rightBound < xLimR) // If within limits and input is right, move right.
                    if(!sideCollide(x, 1)) // If there's no collision sideways
                        for(int i = 0; i < 4; i++)
                            x[i] += 1;
                if (e.key.code == Keyboard::Left && leftBound > xLimL) // If within limits and input is left, move left.
                // If the coordinate is directly on the limit, it won't even consider the IF statement.
                    if(!sideCollide(x, -1)) // This line checks for grid collisions.
                        for(int i = 0; i < 4; i++)
                            x[i] -= 1; // If none, move it.
                if (e.key.code == Keyboard::A) // Rotates piece counterclockwise by 90 degrees.
                {
                    // Counter clockwise is just clockwise 3 times
                    rCount++;
                    rotate(x, rCount, colorNum, rightBound, leftBound, upBound, downBound, xLimL, xLimR);
                    rCount++;
                    rotate(x, rCount, colorNum, rightBound, leftBound, upBound, downBound, xLimL, xLimR);
                    rCount++;
                    rotate(x, rCount, colorNum, rightBound, leftBound, upBound, downBound, xLimL, xLimR);
                }
                if (e.key.code == Keyboard::S) // Rotates piece clockwise by 90 degrees.
                {
                    rCount++;
                    rotate(x, rCount, colorNum, rightBound, leftBound, upBound, downBound, xLimL, xLimR);
                }
                if (e.key.code == Keyboard::Space) // Immediately drops piece to where it would land.
                {
                    for(int j = 0; j < 4; j++)
                    {
                        point_1[j][1] += teleDistance;
                        delay = 0.01;
                    }
                }
                if (e.key.code == Keyboard::H)
                {
                    // Pause menu
                    // There's so many arguments because of the outputs.
                    pause(ev, ev2, window, resume, hiScore, bg, 
                        changeBG, exit, menuOption, background, restart,
                        option, option2, selection, selection2, obj2,
                        score, level, time, timer, gTime, globalTime,
                        xLimL, xLimR, yLimU, first, scoreList, help);
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && isBomb == false)
            delay = 0.05; // Soft drop. Speed is very high if Down button is held.
            // Again, isBomb check there so these inputs don't affect the bomb.

        if (isBomb == true)
            delay = 0.025; // Bomb speed

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        // What the functions are, what they do, and what problem they solve, are all written in functionality.h

        if(first == true) // Only happens at the start.
        {
            shapeBreak(score, xLimL, xLimR, sprite, window, frame, background, textScore, text1, level, levelText, p, pieces, shrinkBlock, clearedRows);
            firstBlock(colorNum, rCount, x); // To remove the single block thing
            first = false;
        }
        else
        {
            fallingPiece(timer, delay, colorNum, x, rCount, isBomb, sprite, bomba, bombWhite, 
                        window, frame, background, textScore, text1,
                        xLimL, xLimR, yLimU, gTime, shrinkBlock,
                        level, score, levelText, p, pMirror, pieces);
                        // The fallingPiece turns into a bomb. And I put animations in there.
                        // That's why there's so many arguments.
                        // It straight up _turns into_ the bomb.
            outerBoundX(leftBound, rightBound, x); // left and right bounds of piece calculation
            outerBoundY(upBound, downBound, x); // up and down bounds of piece calculation
            rowClear(score, xLimL, xLimR, sprite, window, frame, background, textScore, text1, level, levelText, p, pieces, shrinkBlock, clearedRows);
            // This was again just 3 arguments. It increased because I put animations there.
            rowArrange(yLimU, clearedRows);
            // Moves rest of the grid down and also calculates score
            shadow(x, shadowX, shadowY, teleDistance);
            // Projects shadow where piece would land
            scoreInString(score, textScore);
            // Uses % calculations to turn 500 into "500" for output on screen
        }
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        sprite.setTexture(obj1); // Written to reset texture after a bomb
        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                {
                    continue; // Leave that grid empty
                }
                if (gameGrid[i][j] == 8) // Unremovable border block
                {
                    shrinkBlock.setPosition(j * 18, i * 18);
                    shrinkBlock.move(28 + 18 * 0, 31);
                    window.draw(shrinkBlock);
                }
                else // Any other block
                {
                    sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    sprite.setPosition(j * 18, i * 18);
                    sprite.move(28 + 18 * 0, 31);
                    window.draw(sprite);
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));

            if(isBomb == true) // The things to draw if the piece is a bomb
            {
                sprite.setTexture(bomba);
                sprite.setTextureRect(IntRect(0, 0, 18, 18));
                if(colorNum == 0)
                    sprite.setColor(Color::Yellow);
                else if(colorNum == 1)
                    sprite.setColor(Color::Red);
                else if(colorNum == 2)
                    sprite.setColor(Color::Green);
                else if(colorNum == 3)
                    sprite.setColor(Color::Magenta);
                else if(colorNum == 4)
                    sprite.setColor(Color{255, 103, 0});
                else if(colorNum == 5)
                    sprite.setColor(Color{140, 255, 255});
                else if(colorNum == 6)
                    sprite.setColor(Color{12, 140, 255});
            }

            sprite.setPosition(0 * 18, point_1[i][1] * 18);
            sprite.move(28 + 18 * x[i], 31);
            window.draw(sprite);
        }

        if(isBomb == false) // Draw the shadow if it's not a bomb.
        {
            for (int i = 0; i < 4; i++)
            {
                shadowBlock.setPosition(0 * 18, shadowY[i] * 18);
                shadowBlock.move(28 + 18 * shadowX[i], 31);
                window.draw(shadowBlock);
            }
        }
        m1 = int(gTime - 0.5) / 60;
        s1 = int(gTime - 0.5) % 60;
        m2 = m1 % 10;
        s2 = s1 % 10;
        m1 /= 10;
        s1 /= 10;
        // m1 m2 : s1 s2 is 12:34. It has to be separate digits for the concatenation.
        t = char(m1 + 48);
        t += char(m2 + 48);
        t += ":";
        t += char(s1 + 48);
        t += char(s2 + 48);

        theTime.setString(t);

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        window.draw(textScore);
        window.draw(text1);
        window.draw(levelText);
        window.draw(theTime);

        int k = 0;
        if(level == 1 || level == 2)
            k = 4; // I would've liked to do more, but there's no more space on the window. This is 3 next blocks.
        else if(level == 3 || level == 4)
            k = 3; // Two next blocks
        else if(level == 5 || level == 6)
            k = 2; // One next block
        else
            k = 1; // No next block (Good luck)
        
        for(int i = 1; i < k; i++) // Drawing next blocks
            for(int j = 0; j < 4; j++)
            {
                pieces.setTextureRect(sf::IntRect(p[i] * 18, 0, 18, 18));
                pieces.setPosition(250, 140 + 80 * (i + 0));
                if(p[i] == 5) // If it's a line piece, adjust position slightly so it fits
                    pieces.setPosition(250, 140 + 80 * (i + 0) - 10);
                pieces.move(18 * (BLOCKS[p[i]][j] % 2), 18 * (BLOCKS[p[i]][j] / 2));
                window.draw(pieces);
            }

        if(upBound == yLimU && !anomaly(x, xLimL, xLimR, yLimU))
        // If the upper bound of the piece hits the limit and causes an anomaly, then game over.
        {
            char tempChar = 0;
            bool isNameEntered = false;
            while(isNameEntered == false) // User input of name
            {
                window.clear();
                text1.setString("Enter Name:");
                text1.setPosition(35, 130);
                text1.setCharacterSize(24);
                // levelText is being reused then later turned back into the output for the Game Over screen
                levelText.setCharacterSize(24);
                levelText.setString(enteredName);
                levelText.setPosition(35, 170);
                while (window.pollEvent(e))
                {                  
                    if (e.type == Event::Closed)
                        return 0;
                    if (e.type == Event::TextEntered) 
                    {
                        tempChar = e.text.unicode;
                        if(int(tempChar) >= 97 && int(tempChar) <= 122)
                            tempChar -= 32;
                        if(tempChar != '\n' && (int(tempChar) >= 65 && int(tempChar <= 90)) && enteredName.length() < 9)
                        // If the number of characters is more than 9, then don't take more inputs.
                            enteredName += tempChar;
                        if(int(tempChar == 13) || enteredName.length() == 9)
                            isNameEntered = true;
                    }
                }
                window.draw(background);
                window.draw(text1);
                window.draw(levelText);
                window.display();
            }
            while(enteredName.length() != 9)
            {
                enteredName += "_";
            }
            int temp = highScore[0]; // Temp location
            std::string temp2 = name[0];
            for(int i = 0; i < 10; i++)
            {
                if (score > highScore[i])
                {
                    temp = score;
                    score = highScore[i];
                    highScore[i] = temp;
                    temp2 = enteredName;
                    enteredName = name[i];
                    name[i] = temp2;
                }
            }
            dataInFile = "\0";
            for(int i = 0; i < 10; i++)
            {
                dataInFile += name[i];
                dataInFile += " ";
                dataInFile += scoreInStringFile(highScore[i]);
                dataInFile += "\n";
            }
            scoreList.setString(dataInFile);
            theScores.open("misc/hiscores.txt", std::ios::out);
            theScores << dataInFile;
            // 'dataInFile' holds the string value of the entire text file.
            // I'm modifying that string then overriding the entire list present in the file already.
            theScores.close();
            while(true)
            {
                window.clear(sf::Color::Black);
                gameOver.setPosition(100, 101);
                text1.setString("Score:");
                text1.setPosition(75, 130);
                text1.setCharacterSize(24);
                textScore.setPosition(165,130);
                textScore.setCharacterSize(24);
                l = "Level Reached: ";
                l = l + char(level + 48);
                levelText.setPosition(50,158);
                levelText.setCharacterSize(24);
                levelText.setString(l);
                t = char(m1 + 48);              
                t += char(m2 + 48);             // All these values had to be brought back
                t += ":";                       // So that the output was correct
                t += char(s1 + 48);             // Otherwise it was looping into itself
                t += char(s2 + 48);             // And not remembering anything.
                t = "Time Played: " + t;
                theTime.setPosition(37,190);
                theTime.setCharacterSize(24);
                theTime.setString(t);
                window.draw(background);
                window.draw(gameOver);
                window.draw(text1);
                window.draw(textScore);
                window.draw(levelText);
                window.draw(theTime);
                scoreList.setCharacterSize(18);
                scoreList.setPosition(70, 225);
                window.draw(scoreList);
                window.display();
                window.pollEvent(e);
                if (e.type == Event::Closed)
                {
                    return 0;
                }
            }
        }
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        if (e.type == Event::Closed || window.isOpen() == false)
        {
            return 0; // Ends program if the window is closed at any point from anything
            // I found it to work way better than window.close() as the window would close but
            // the program would continue running.
        }
    }
    return 0;
}