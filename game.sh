#!/bin/bash  
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
