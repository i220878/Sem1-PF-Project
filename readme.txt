Install GNU G++ Compiler:
sudo apt-get install g++

Install SFML:
sudo apt-get install libsfml-dev

Compile the game by doing
./game.sh
in the terminal

It's a batch file. If it fails or something, then the commands are
g++ -c main.cpp
for compiling.
g++ main.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
for linking the compiled thing to the sfml library.

Then launch the game by doing
./sfml-app
in the terminal.
